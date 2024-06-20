#include "RenderTaskConsumer.h"
#include "../render_head.h";
#include "RenderTaskQueue.h";

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
		render_thread_.join();//等待渲染线程结束
	}
}

void RenderTaskConsumer::ProcessTask()
{
	//渲染相关的API调用需要放到渲染线程中。
	glfwMakeContextCurrent(window_);
	gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
	glfwSwapInterval(1);
	while (!glfwWindowShouldClose(window_))
	{
		float ratio;
		int width, height;
		glm::mat4 model, view, projection, mvp;

		//获取画面宽高
		glfwGetFramebufferSize(window_, &width, &height);
		ratio = width / (float)height;
		glViewport(0, 0, width, height); __CHECK_GL_ERROR__

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); __CHECK_GL_ERROR__
		glClearColor(49.f / 255, 77.f / 255, 121.f / 255, 1.f); __CHECK_GL_ERROR__

		view = glm::lookAt(glm::vec3(0, 0, 10), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));

		projection = glm::perspective(glm::radians(60.f), ratio, 1.f, 1000.f);
		while (true)
		{
			if (RenderTaskQueue::Empty()) {//渲染线程一直等待主线程发出任务。
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
				break;
			case COMPILE_SHADER:
				break;
			case USE_SHADER_PROGRAM:
				break;
			case CREATE_VAO:
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