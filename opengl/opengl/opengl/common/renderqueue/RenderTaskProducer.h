#ifndef UNTITLED_RENDER_RENDERTASKPRODUCER_H
#define UNTITLED_RENDER_RENDERTASKPRODUCER_H

#include "rendertask/rendertask_head.h";
#include "RenderTaskQueue.h"
#include <string.h>
#include "../render/mesh/Mesh.h"
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
	static void ProduceRenderTaskCreateVAO(unsigned int shader_program_handle, unsigned int vao_handle, unsigned int vbo_handle, unsigned int vertex_data_size, unsigned int vertex_data_stride, void* vertex_data, unsigned int vertex_index_data_size, void* vertex_index_data);
	/// <summary>
	/// 创建vbo
	/// </summary>
	static void ProduceRenderTaskUpdateVBOSubData(unsigned int vbo_handle, unsigned int vertex_data_size, void* vertex_data);
	/// 发出任务：设置状态,开启或关闭
	static void ProduceRenderTaskSetEnableState(unsigned int state, bool enable);

	/// 发出任务：设置混合函数
	/// \param source_blending_factor 源混合因子
	/// \param destination_blending_factor 目标混合因子
	static void ProduceRenderTaskSetBlenderFunc(unsigned int source_blending_factor, unsigned int destination_blending_factor);
	/// 发出任务：设置4x4矩阵
	 /// \param shader_program_handle
	 /// \param uniform_name
	 /// \param transpose
	 /// \param value
	 /// \param value_data_size
	static void ProduceRenderTaskSetUniformMatrix4fv(unsigned int shader_program_handle, const char* uniform_name, bool transpose, glm::mat4& matrix);

	/// 激活并绑定纹理
	/// \param texture_uint
	/// \param texture_handle
	static void ProduceRenderTaskActiveAndBindTexture(unsigned int texture_uint, unsigned int texture_handle);

	/// 上传1个int值
	/// \param shader_program_handle
	/// \param uniform_name
	/// \param value
	static void ProduceRenderTaskSetUniform1i(unsigned int shader_program_handle, const char* uniform_name, int value);

	/// 绑定VAO并绘制
	/// \param vao_handle
	/// \param inex_count
	static void ProduceRenderTaskBindVAOAndDrawElements(unsigned int vao_handle, unsigned int vertex_index_num);

	/// <summary>
	/// 设置clear_flag并且清除颜色缓冲
	/// </summary>
	static void ProduceRenderTaskSetClearFlagAndClearColorBuffer(unsigned int clear_flag, float clear_color_r, float clear_color_g, float clear_color_b, float clear_color_a);
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
