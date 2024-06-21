#ifndef UNTITLED_RENDERTASKCONSUMER_H
#define UNTITLED_RENDERTASKCONSUMER_H

#include <thread>
#include "rendertask/rendertask_head.h"
class GLFWwindow;

class RenderTaskConsumer
{
public:
	static void Init(GLFWwindow* window);

	static void Exit();
public:
	static void ProcessTask();
	/// <summary>
	/// ������Ϸ����ߴ�
	/// </summary>
	static void UpdateScreenSize(RenderTaskBase* task_base);
	/// <summary>
	/// ����Shader
	/// </summary>
	static void CompileShader(RenderTaskBase* task_base);
	/// <summary>
	/// ʹ��gpu����
	/// </summary>
	static void UseShaderProgram(RenderTaskBase* task_base);
	/// <summary>
	/// ����ѹ����ͼ
	/// </summary>
	/// <param name="task_base"></param>
	static void CreateCompressedTexImage2D(RenderTaskBase* task_base);

private:
	static GLFWwindow* window_;
	static std::thread render_thread_;//��Ⱦ�߳�
};

#endif

