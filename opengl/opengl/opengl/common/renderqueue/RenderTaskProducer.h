#ifndef UNTITLED_RENDER_RENDERTASKPRODUCER_H
#define UNTITLED_RENDER_RENDERTASKPRODUCER_H

#include "rendertask/rendertask_head.h";
#include "RenderTaskQueue.h"

class RenderTaskProducer
{
public:
	/// <summary>
	/// 更新游戏窗口尺寸
	/// </summary>
	static void ProduceRenderTaskUpdateScreenSize();
	/// <summary>
	/// 编译shader
	/// </summary>
	static void ProduceRenderTaskCompileShader();
	/// <summary>
	/// 压缩贴图
	/// </summary>
	static void ProduceRenderTaskCreateCompressedTexImage2D();
	/// <summary>
	/// 创建纹理
	/// </summary>
	static void ProduceRenderTaskCreateTexImage2D();
	/// <summary>
	/// 删除贴图
	/// </summary>
	static void ProduceRenderTaskDeleteTextures();
	/// <summary>
	/// 更新贴图
	/// </summary>
	static void ProduceRenderTaskUpdateTextureSubImage2D();
	/// <summary>
	/// 创建vao
	/// </summary>
	static void ProduceRenderTaskCreateVAO();
	/// <summary>
	/// 创建vbo
	/// </summary>
	static void ProduceRenderTaskUpdateVBOSubData();
	/// <summary>
	/// 设置状态,开启或关闭
	/// </summary>
	static void ProduceRenderTaskSetEnableState();
	/// <summary>
	/// 设置混合函数
	/// </summary>
	static void ProduceRenderTaskSetBlenderFunc();
	/// <summary>
	/// 设置4x4矩阵
	/// </summary>
	static void ProduceRenderTaskSetUniformMatrix4fv();
	/// <summary>
	/// 激活并绑定纹理
	/// </summary>
	static void ProduceRenderTaskActiveAndBindTexture();
	/// <summary>
	/// 上传1个int值
	/// </summary>
	static void ProduceRenderTaskSetUniform1i();
	/// <summary>
	/// 绑定VAO并绘制
	/// </summary>
	static void ProduceRenderTaskBindVAOAndDrawElements();
	/// <summary>
	/// 设置clear_flag并且清除颜色缓冲
	/// </summary>
	static void ProduceRenderTaskSetClearFlagAndClearColorBuffer();
	/// <summary>
	/// 设置模板测试函数
	/// </summary>
	static void ProduceRenderTaskSetStencilFunc();
	/// <summary>
	/// 设置模板操作
	/// </summary>
	static void ProduceRenderTaskSetStencilOp();
	/// <summary>
	/// 设置清除模板缓冲值
	/// </summary>
	static void ProduceRenderTaskSetStencilBufferClearValue();
	/// <summary>
	/// 渲染结束
	/// </summary>
	static void ProduceRenderTaskEndFrame();
};
#endif
