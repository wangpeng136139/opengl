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


/// ɾ��Textures
/// \param task_base
void RenderTaskConsumer::DeleteTextures(RenderTaskBase* task_base) {
	RenderTaskDeleteTextures* task = dynamic_cast<RenderTaskDeleteTextures*>(task_base);
	//�Ӿ��ת�����������
	GLuint* texture_id_array = new GLuint[task->texture_count_];
	for (int i = 0; i < task->texture_count_; ++i) {
		texture_id_array[i] = GPUResourceMapper::GetTexture(task->texture_handle_array_[i]);
	}
	glDeleteTextures(task->texture_count_, texture_id_array); __CHECK_GL_ERROR__
		delete[] texture_id_array;
}


void RenderTaskConsumer::CreateTexImage2D(RenderTaskBase* task_base) {
	RenderTaskCreateTexImage2D* task = dynamic_cast<RenderTaskCreateTexImage2D*>(task_base);

	GLuint texture_id;

	//1. ֪ͨ�Կ�����������󣬷��ؾ��;
	glGenTextures(1, &texture_id); __CHECK_GL_ERROR__

		//2. ������󶨵��ض�����Ŀ��;
		glBindTexture(GL_TEXTURE_2D, texture_id); __CHECK_GL_ERROR__

		//3. ��ͼƬrgb�����ϴ���GPU;
		glTexImage2D(GL_TEXTURE_2D, 0, task->gl_texture_format_, task->width_, task->height_, 0, task->client_format_, task->data_type_, task->data_); __CHECK_GL_ERROR__

		//4. ָ���Ŵ���С�˲���ʽ�������˲������Ŵ���С�Ĳ�ֵ��ʽ;
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); __CHECK_GL_ERROR__
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); __CHECK_GL_ERROR__

		//�����߳��в����������� ӳ�䵽 ����
		GPUResourceMapper::MapTexture(task->texture_handle_, texture_id);
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

/// �ֲ���������
/// \param task_base
void RenderTaskConsumer::UpdateTextureSubImage2D(RenderTaskBase* task_base) {
	RenderTaskUpdateTextureSubImage2D* task = dynamic_cast<RenderTaskUpdateTextureSubImage2D*>(task_base);
	GLuint texture = GPUResourceMapper::GetTexture(task->texture_handle_);
	glBindTexture(GL_TEXTURE_2D, texture); __CHECK_GL_ERROR__
		glPixelStorei(GL_UNPACK_ALIGNMENT, 1); __CHECK_GL_ERROR__
		glTexSubImage2D(GL_TEXTURE_2D, 0, task->x_, task->y_, task->width_, task->height_, task->client_format_, task->data_type_, task->data_); __CHECK_GL_ERROR__
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

void RenderTaskConsumer::SetEnableState(RenderTaskBase* task_base) {
	RenderTaskSetEnableState* task = dynamic_cast<RenderTaskSetEnableState*>(task_base);
	if (task->enable_) {
		glEnable(task->state_); __CHECK_GL_ERROR__
	}
	else {
		glDisable(task->state_); __CHECK_GL_ERROR__
	}
}
void RenderTaskConsumer::SetBlendFunc(RenderTaskBase* task_base) {
	RenderTaskSetBlenderFunc* task = dynamic_cast<RenderTaskSetBlenderFunc*>(task_base);
	glBlendFunc(task->source_blending_factor_, task->destination_blending_factor_); __CHECK_GL_ERROR__
}

void RenderTaskConsumer::SetUniformMatrix4fv(RenderTaskBase* task_base) {
	RenderTaskSetUniformMatrix4fv* task = dynamic_cast<RenderTaskSetUniformMatrix4fv*>(task_base);
	//�ϴ�mvp����
	GLuint shader_program = GPUResourceMapper::GetShaderProgram(task->shader_program_handle_);
	GLint uniform_location = glGetUniformLocation(shader_program, task->uniform_name_); __CHECK_GL_ERROR__
		glUniformMatrix4fv(uniform_location, 1, task->transpose_ ? GL_TRUE : GL_FALSE, &task->matrix_[0][0]); __CHECK_GL_ERROR__
}


void RenderTaskConsumer::ActiveAndBindTexture(RenderTaskBase* task_base) {
	RenderTaskActiveAndBindTexture* task = dynamic_cast<RenderTaskActiveAndBindTexture*>(task_base);
	//��������Ԫ
	glActiveTexture(task->texture_uint_); __CHECK_GL_ERROR__
		//�����ص�ͼƬ���������󶨵�����Ԫ0��Texture2D�ϡ�
		GLuint texture = GPUResourceMapper::GetTexture(task->texture_handle_);
	glBindTexture(GL_TEXTURE_2D, texture); __CHECK_GL_ERROR__
}

/// ���
/// \param task_base
void RenderTaskConsumer::SetClearFlagAndClearColorBuffer(RenderTaskBase* task_base) {
	RenderTaskClear* task = dynamic_cast<RenderTaskClear*>(task_base);
	glClear(task->clear_flag_); __CHECK_GL_ERROR__
		glClearColor(task->clear_color_r_, task->clear_color_g_, task->clear_color_b_, task->clear_color_a_); __CHECK_GL_ERROR__
}


void RenderTaskConsumer::BindVAOAndDrawElements(RenderTaskBase* task_base) {
	RenderTaskBindVAOAndDrawElements* task = dynamic_cast<RenderTaskBindVAOAndDrawElements*>(task_base);
	GLuint vao = GPUResourceMapper::GetVAO(task->vao_handle_);
	glBindVertexArray(vao); __CHECK_GL_ERROR__
	{
		glDrawElements(GL_TRIANGLES,task->vertex_index_num_,GL_UNSIGNED_SHORT,0); __CHECK_GL_ERROR__//ʹ�ö����������л��ƣ�����0��ʾ����ƫ������
	}
	glBindVertexArray(0); __CHECK_GL_ERROR__
}



void RenderTaskConsumer::SetUniform1i(RenderTaskBase* task_base) {
	RenderTaskSetUniform1i* task = dynamic_cast<RenderTaskSetUniform1i*>(task_base);
	//����Shader���������Ԫ��ȡ��ɫ����
	GLuint shader_program = GPUResourceMapper::GetShaderProgram(task->shader_program_handle_);
	GLint uniform_location = glGetUniformLocation(shader_program, task->uniform_name_); __CHECK_GL_ERROR__
	glUniform1i(uniform_location, task->value_); __CHECK_GL_ERROR__
}


/// ����ģ����Ժ���
void RenderTaskConsumer::SetStencilFunc(RenderTaskBase* task_base) {
	RenderTaskSetStencilFunc* task = dynamic_cast<RenderTaskSetStencilFunc*>(task_base);
	glStencilFunc(task->stencil_func_, task->stencil_ref_, task->stencil_mask_); __CHECK_GL_ERROR__
}

/// ����ģ�����
void RenderTaskConsumer::SetStencilOp(RenderTaskBase* task_base) {
	RenderTaskSetStencilOp* task = dynamic_cast<RenderTaskSetStencilOp*>(task_base);
	glStencilOp(task->fail_op_, task->z_test_fail_op_, task->z_test_pass_op_); __CHECK_GL_ERROR__
}

void RenderTaskConsumer::SetStencilBufferClearValue(RenderTaskBase* task_base) {
	RenderTaskSetStencilBufferClearValue* task = dynamic_cast<RenderTaskSetStencilBufferClearValue*>(task_base);
	glClearStencil(task->clear_value_); __CHECK_GL_ERROR__
}


/// ����һ֡
/// \param task_base
void RenderTaskConsumer::EndFrame(RenderTaskBase* task_base) {
	RenderTaskEndFrame* task = dynamic_cast<RenderTaskEndFrame*>(task_base);
	glfwSwapBuffers(window_);
	task->return_result_set_ = true;
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
				UpdateVBOSubData(render_task);
				break;
			case CREATE_COMPRESSED_TEX_IMAGE2D:
				CreateCompressedTexImage2D(render_task);
				break;
			case CREATE_TEX_IMAGE2D:
				CreateTexImage2D(render_task);
				break;
			case DELETE_TEXTURES:
				DeleteTextures(render_task);
				break;
			case UPDATE_TEXTURE_SUB_IMAGE2D:
				UpdateTextureSubImage2D(render_task);
				break;
			case SET_ENABLE_STATE:
				SetEnableState(render_task);
				break;
			case SET_BLENDER_FUNC:
				SetBlendFunc(render_task);
				break;
			case SET_UNIFORM_MATRIX_4FV:
				SetUniformMatrix4fv(render_task);
				break;
			case ACTIVE_AND_BIND_TEXTURE:
				ActiveAndBindTexture(render_task);
				break;
			case SET_UNIFORM_1I:
				SetUniform1i(render_task);
				break;
			case BIND_VAO_AND_DRAW_ELEMENTS:
				BindVAOAndDrawElements(render_task);
				break;
			case SET_CLEAR_FLAG_AND_CLEAR_COLOR_BUFFER:
				SetClearFlagAndClearColorBuffer(render_task);
				break;
			case SET_STENCIL_FUNC:
				SetStencilFunc(render_task);
				break;
			case SET_STENCIL_OP:
				SetStencilOp(render_task);
				break;
			case SET_STENCIL_BUFFER_CLEAR_VALUE:
				SetStencilBufferClearValue(render_task);
				break;
			case END_FRAME:
				EndFrame(render_task);
				break;
			default:
				break;
			}

			RenderTaskQueue::Pop();

			//������������Ҫ���ز�������ô�����ɾ����
			if (need_return_result == false) {
				delete render_task;
			}
			//�����֡�������񣬾ͽ�����������
			if (render_command == RenderCommand::END_FRAME) {
				break;
			}
		}
	}
}