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
	/// <summary>
	/// 创建VAO
	/// </summary>
	/// <param name="task_base"></param>
	/// <returns></returns>
	static void CreateVAO(RenderTaskBase* task_base);
	/// <summary>
	/// 更新vbo
	/// </summary>
	static void UpdateVBOSubData(RenderTaskBase* task_base);
	/// <summary>
	/// 创建纹理
	/// </summary>
	static void CreateTexImage2D(RenderTaskBase* task_base);
	/// <summary>
	/// 删除纹理
	/// </summary>
	static void DeleteTextures(RenderTaskBase* task_base);
	/// <summary>
	/// 局部更新纹理
	/// </summary>
	/// <param name="task_base"></param>
	static void UpdateTextureSubImage2D(RenderTaskBase* task_base);
	/// <summary>
	/// 设置状态，开启或关闭
	/// </summary>
	/// <param name="task_base"></param>
	static void SetEnableState(RenderTaskBase* task_base);
	/// <summary>
	/// 设置混合因子
	/// </summary>
	/// <param name="task_base"></param>
	static void SetBlendFunc(RenderTaskBase* task_base);
	/// <summary>
	/// 设置矩阵
	/// </summary>
	/// <param name="task_base"></param>
	static void SetUniformMatrix4fv(RenderTaskBase* task_base);
	/// <summary>
	/// 激活并且绑定纹理单元
	/// </summary>
	/// <param name="task_base"></param>
	static void ActiveAndBindTexture(RenderTaskBase* task_base);
	/// <summary>
	/// 上传int
	/// </summary>
	/// <param name="task_base"></param>
	static void SetUniform1i(RenderTaskBase* task_base);
	/// <summary>
	/// 设置clear_flag并且清除颜色缓冲
	/// </summary>
	/// <param name="task_base"></param>
	static void SetClearFlagAndClearColorBuffer(RenderTaskBase* task_base);
	/// <summary>
	/// 绑定VAO并绘制
	/// </summary>
	/// <param name="task_base"></param>
	static void BindVAOAndDrawElements(RenderTaskBase* task_base);
	/// <summary>
	/// 绑定设置模板测试函数并绘制
	/// </summary>
	/// <param name="task_base"></param>
	static void SetStencilFunc(RenderTaskBase* task_base);
	/// <summary>
	/// 设置模板操作
	/// </summary>
	/// <param name="task_base"></param>
	static void SetStencilOp(RenderTaskBase* task_base);
	/// <summary>
	/// 设置清除模板缓冲值
	/// </summary>
	/// <param name="task_base"></param>
	static void SetStencilBufferClearValue(RenderTaskBase* task_base);
	/// <summary>
	/// 帧结束标志，渲染线程收到这个任务后，刷新缓冲区，设置帧结束。
	/// </summary>
	/// <param name="task_base"></param>
	static void EndFrame(RenderTaskBase* task_base);
private:
	static GLFWwindow* window_;
	static std::thread render_thread_;//渲染线程
};

#endif

