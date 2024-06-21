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
	/// 更新游戏画面尺寸
	/// </summary>
	static void UpdateScreenSize(RenderTaskBase* task_base);
	/// <summary>
	/// 编译Shader
	/// </summary>
	static void CompileShader(RenderTaskBase* task_base);
	/// <summary>
	/// 使用gpu程序
	/// </summary>
	static void UseShaderProgram(RenderTaskBase* task_base);
	/// <summary>
	/// 创建压缩贴图
	/// </summary>
	/// <param name="task_base"></param>
	static void CreateCompressedTexImage2D(RenderTaskBase* task_base);

private:
	static GLFWwindow* window_;
	static std::thread render_thread_;//渲染线程
};

#endif

