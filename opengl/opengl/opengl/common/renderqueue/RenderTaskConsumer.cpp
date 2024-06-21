#include "RenderTaskConsumer.h"
#include "../render_head.h";
#include "RenderTaskQueue.h";
#include "../common/Screen.h"
#include "GPUResourceMapper.h"

GLFWwindow* RenderTaskConsumer::window_;
std::thread RenderTaskConsumer::render_thread_;

void RenderTaskConsumer::Init(GLFWwindow* window)
{
	window_ = window;
	render_thread_ = std::thread(&RenderTaskConsumer::ProcessTask);
	render_thread_.detach();
}

void RenderTaskConsumer::Exit() {
	if (render_thread_.joinable()) {
		render_thread_.join();//�ȴ���Ⱦ�߳̽���
	}
}

/// ������Ϸ����ߴ�
void RenderTaskConsumer::UpdateScreenSize(RenderTaskBase* task_base) {
	RenderTaskUpdateScreenSize* task = dynamic_cast<RenderTaskUpdateScreenSize*>(task_base);
	int width, height;
	glfwGetFramebufferSize(window_, &width, &height);
	glViewport(0, 0, width, height);
	Screen::set_width_height(width, height);
}

/// ���롢����Shader
/// \param task_base
void RenderTaskConsumer::CompileShader(RenderTaskBase* task_base) {
	RenderTaskCompileShader* task = dynamic_cast<RenderTaskCompileShader*>(task_base);
	const char* vertex_shader_text = task->vertex_shader_source_;
	const char* fragment_shader_text = task->fragment_shader_source_;

	//��������Shader
	unsigned int vertex_shader = glCreateShader(GL_VERTEX_SHADER); __CHECK_GL_ERROR__
	//ָ��ShaderԴ��
	glShaderSource(vertex_shader, 1, &vertex_shader_text, NULL); __CHECK_GL_ERROR__
	//����Shader
	glCompileShader(vertex_shader); __CHECK_GL_ERROR__
	//��ȡ������
	GLint compile_status = GL_FALSE;
	glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &compile_status);
	if (compile_status == GL_FALSE)
	{
		GLchar message[256];
		glGetShaderInfoLog(vertex_shader, sizeof(message), 0, message);
		DEBUG_LOG_ERROR("compile vertex shader error:{}", message);
		return;
	}

	//����Ƭ��Shader
	unsigned int fragment_shader = glCreateShader(GL_FRAGMENT_SHADER); __CHECK_GL_ERROR__
		//ָ��ShaderԴ��
		glShaderSource(fragment_shader, 1, &fragment_shader_text, NULL); __CHECK_GL_ERROR__
		//����Shader
		glCompileShader(fragment_shader); __CHECK_GL_ERROR__
		//��ȡ������
		compile_status = GL_FALSE;
	glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &compile_status);
	if (compile_status == GL_FALSE)
	{
		GLchar message[256];
		glGetShaderInfoLog(fragment_shader, sizeof(message), 0, message);
		DEBUG_LOG_ERROR("compile fragment shader error:{}", message);
		return;
	}

	//����Shader����
	GLuint shader_program = glCreateProgram(); __CHECK_GL_ERROR__
		//����Shader
		glAttachShader(shader_program, vertex_shader); __CHECK_GL_ERROR__
		glAttachShader(shader_program, fragment_shader); __CHECK_GL_ERROR__
		//Link
		glLinkProgram(shader_program); __CHECK_GL_ERROR__
		//��ȡ������
		GLint link_status = GL_FALSE;
	glGetProgramiv(shader_program, GL_LINK_STATUS, &link_status);
	if (link_status == GL_FALSE)
	{
		GLchar message[256];
		glGetProgramInfoLog(shader_program, sizeof(message), 0, message);
		DEBUG_LOG_ERROR("link shader error:{}", message);
		return;
	}
	//�����߳��в�����Shader������ ӳ�䵽 Shader����
	GPUResourceMapper::MapShaderProgram(task->shader_program_handle_, shader_program);
}


void RenderTaskConsumer::UseShaderProgram(RenderTaskBase* task_base) {
	RenderTaskUseShaderProgram* task = dynamic_cast<RenderTaskUseShaderProgram*>(task_base);
	GLuint shader_program = GPUResourceMapper::GetShaderProgram(task->shader_program_handle_);
	glUseProgram(shader_program); __CHECK_GL_ERROR__
}


void RenderTaskConsumer::CreateCompressedTexImage2D(RenderTaskBase* task_base) {
	RenderTaskCreateCompressedTexImage2D* task = dynamic_cast<RenderTaskCreateCompressedTexImage2D*>(task_base);

	GLuint texture_id;

	//1. ֪ͨ�Կ�����������󣬷��ؾ��;
	glGenTextures(1, &texture_id); __CHECK_GL_ERROR__

	//2. ������󶨵��ض�����Ŀ��;
	glBindTexture(GL_TEXTURE_2D, texture_id); __CHECK_GL_ERROR__
	
	//3. ��ѹ�����������ϴ���GPU;
	glCompressedTexImage2D(GL_TEXTURE_2D, 0, task->texture_format_, task->width_, task->height_, 0, task->compress_size_, task->data_);
__CHECK_GL_ERROR__

	//4. ָ���Ŵ���С�˲���ʽ�������˲������Ŵ���С�Ĳ�ֵ��ʽ;
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); __CHECK_GL_ERROR__
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); __CHECK_GL_ERROR__

	//�����߳��в�����ѹ�������� ӳ�䵽 ����
	GPUResourceMapper::MapTexture(task->texture_handle_, texture_id);
}


void RenderTaskConsumer::CreateVAO(RenderTaskBase* task_base) {
	RenderTaskCreateVAO* task = dynamic_cast<RenderTaskCreateVAO*>(task_base);
	GLuint shader_program = GPUResourceMapper::GetShaderProgram(task->shader_program_handle_);
	GLint attribute_pos_location = glGetAttribLocation(shader_program, "a_pos"); __CHECK_GL_ERROR__
		GLint attribute_color_location = glGetAttribLocation(shader_program, "a_color"); __CHECK_GL_ERROR__
		GLint attribute_uv_location = glGetAttribLocation(shader_program, "a_uv"); __CHECK_GL_ERROR__

		GLuint vertex_buffer_object, element_buffer_object, vertex_array_object;
	//��GPU�ϴ�������������
	glGenBuffers(1, &vertex_buffer_object); __CHECK_GL_ERROR__
		//������������ָ��Ϊ���㻺��������
		glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_object); __CHECK_GL_ERROR__
		//�ϴ��������ݵ�����������
		glBufferData(GL_ARRAY_BUFFER, task->vertex_data_size_, task->vertex_data_, GL_DYNAMIC_DRAW); __CHECK_GL_ERROR__
		//�����߳��в�����VBO��� ӳ�䵽 VBO
		GPUResourceMapper::MapVBO(task->vbo_handle_, vertex_buffer_object);

	//��GPU�ϴ�������������
	glGenBuffers(1, &element_buffer_object); __CHECK_GL_ERROR__
		//������������ָ��Ϊ������������������
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, element_buffer_object); __CHECK_GL_ERROR__
		//�ϴ������������ݵ�����������
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, task->vertex_index_data_size_, task->vertex_index_data_, GL_STATIC_DRAW); __CHECK_GL_ERROR__

		glGenVertexArrays(1, &vertex_array_object); __CHECK_GL_ERROR__

		//����VAO
		glBindVertexArray(vertex_array_object); __CHECK_GL_ERROR__
	{
		//ָ����ǰʹ�õ�VBO
		glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_object); __CHECK_GL_ERROR__
		//��Shader����(a_pos)�Ͷ�������VBO������й���������0��ʾ����ƫ������
		glVertexAttribPointer(attribute_pos_location, 3, GL_FLOAT, false, task->vertex_data_stride_, 0); __CHECK_GL_ERROR__
		//���ö���Shader����(a_color)��ָ���붥����ɫ���ݽ��й���
		glVertexAttribPointer(attribute_color_location, 4, GL_FLOAT, false, task->vertex_data_stride_, (void*)(sizeof(float) * 3)); __CHECK_GL_ERROR__
		//��Shader����(a_uv)�Ͷ���UV����VBO������й���������0��ʾ����ƫ������
		glVertexAttribPointer(attribute_uv_location, 2, GL_FLOAT, false, task->vertex_data_stride_, (void*)(sizeof(float) * (3 + 4))); __CHECK_GL_ERROR__

		glEnableVertexAttribArray(attribute_pos_location); __CHECK_GL_ERROR__
		glEnableVertexAttribArray(attribute_color_location); __CHECK_GL_ERROR__
		glEnableVertexAttribArray(attribute_uv_location); __CHECK_GL_ERROR__

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, element_buffer_object); __CHECK_GL_ERROR__
	}
	glBindBuffer(GL_ARRAY_BUFFER, 0); __CHECK_GL_ERROR__
		//�����߳��в�����VAO��� ӳ�䵽 VAO
		GPUResourceMapper::MapVAO(task->vao_handle_, vertex_array_object);
}

void RenderTaskConsumer::UpdateVBOSubData(RenderTaskBase* task_base) {
	RenderTaskUpdateVBOSubData* task = dynamic_cast<RenderTaskUpdateVBOSubData*>(task_base);
	GLuint vbo = GPUResourceMapper::GetVBO(task->vbo_handle_);
	glBindBuffer(GL_ARRAY_BUFFER, vbo); __CHECK_GL_ERROR__
		timetool::StopWatch stopwatch;
	stopwatch.start();
	//����Buffer����
	glBufferSubData(GL_ARRAY_BUFFER, 0, task->vertex_data_size_, task->vertex_data_); __CHECK_GL_ERROR__
		stopwatch.stop();
	DEBUG_LOG_INFO("glBufferSubData cost {}", stopwatch.microseconds());
}



void RenderTaskConsumer::ProcessTask()
{
	//��Ⱦ��ص�API������Ҫ�ŵ���Ⱦ�߳��С�
	glfwMakeContextCurrent(window_);
	gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
	glfwSwapInterval(1);
	while (!glfwWindowShouldClose(window_))
	{
		float ratio;
		int width, height;
		glm::mat4 model, view, projection, mvp;

		//��ȡ������
		glfwGetFramebufferSize(window_, &width, &height);
		ratio = width / (float)height;
		glViewport(0, 0, width, height); __CHECK_GL_ERROR__

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); __CHECK_GL_ERROR__
		glClearColor(49.f / 255, 77.f / 255, 121.f / 255, 1.f); __CHECK_GL_ERROR__

		view = glm::lookAt(glm::vec3(0, 0, 10), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));

		projection = glm::perspective(glm::radians(60.f), ratio, 1.f, 1000.f);
		while (true)
		{
			if (RenderTaskQueue::Empty()) {//��Ⱦ�߳�һֱ�ȴ����̷߳�������
				continue;
			}

			RenderTaskBase* render_task = RenderTaskQueue::Front();
			RenderCommand render_command = render_task->render_command_;
			bool need_return_result = render_task->need_return_result_;
			switch (render_command)
			{
			case NONE:
				break;
			case UPDATE_SCREEN_SIZE:
				UpdateScreenSize(render_task);
				break;
			case COMPILE_SHADER:
				CompileShader(render_task);
				break;
			case USE_SHADER_PROGRAM:
				UseShaderProgram(render_task);
				break;
			case CREATE_VAO:	
				CreateVAO(render_task);
				break;
			case UPDATE_VBO_SUB_DATA:
				
				break;
			case CREATE_COMPRESSED_TEX_IMAGE2D:
				break;
			case CREATE_TEX_IMAGE2D:
				break;
			case DELETE_TEXTURES:
				break;
			case UPDATE_TEXTURE_SUB_IMAGE2D:
				break;
			case SET_ENABLE_STATE:
				break;
			case SET_BLENDER_FUNC:
				break;
			case SET_UNIFORM_MATRIX_4FV:
				break;
			case ACTIVE_AND_BIND_TEXTURE:
				break;
			case SET_UNIFORM_1I:
				break;
			case BIND_VAO_AND_DRAW_ELEMENTS:
				break;
			case SET_CLEAR_FLAG_AND_CLEAR_COLOR_BUFFER:
				break;
			case SET_STENCIL_FUNC:
				break;
			case SET_STENCIL_OP:
				break;
			case SET_STENCIL_BUFFER_CLEAR_VALUE:
				break;
			case END_FRAME:
				break;
			default:
				break;
			}
		}
	}
}