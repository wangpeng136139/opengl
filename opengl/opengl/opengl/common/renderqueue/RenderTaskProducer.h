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
	/// ������Ϸ���ڳߴ�
	/// </summary>
	static void ProduceRenderTaskUpdateScreenSize();
	/// <summary>
	/// ����shader
	/// </summary>
	static void ProduceRenderTaskCompileShader();
	/// <summary>
	/// ѹ����ͼ
	/// </summary>
	static void ProduceRenderTaskCreateCompressedTexImage2D();
	/// <summary>
	/// ��������
	/// </summary>
	static void ProduceRenderTaskCreateTexImage2D();
	/// <summary>
	/// ɾ����ͼ
	/// </summary>
	static void ProduceRenderTaskDeleteTextures();
	/// <summary>
	/// ������ͼ
	/// </summary>
	static void ProduceRenderTaskUpdateTextureSubImage2D();
	/// <summary>
	/// ����vao
	/// </summary>
	static void ProduceRenderTaskCreateVAO(unsigned int shader_program_handle, unsigned int vao_handle, unsigned int vbo_handle, unsigned int vertex_data_size, unsigned int vertex_data_stride, void* vertex_data, unsigned int vertex_index_data_size, void* vertex_index_data);
	/// <summary>
	/// ����vbo
	/// </summary>
	static void ProduceRenderTaskUpdateVBOSubData(unsigned int vbo_handle, unsigned int vertex_data_size, void* vertex_data);
	/// ������������״̬,������ر�
	static void ProduceRenderTaskSetEnableState(unsigned int state, bool enable);

	/// �����������û�Ϻ���
	/// \param source_blending_factor Դ�������
	/// \param destination_blending_factor Ŀ��������
	static void ProduceRenderTaskSetBlenderFunc(unsigned int source_blending_factor, unsigned int destination_blending_factor);
	/// ������������4x4����
	 /// \param shader_program_handle
	 /// \param uniform_name
	 /// \param transpose
	 /// \param value
	 /// \param value_data_size
	static void ProduceRenderTaskSetUniformMatrix4fv(unsigned int shader_program_handle, const char* uniform_name, bool transpose, glm::mat4& matrix);

	/// ���������
	/// \param texture_uint
	/// \param texture_handle
	static void ProduceRenderTaskActiveAndBindTexture(unsigned int texture_uint, unsigned int texture_handle);

	/// �ϴ�1��intֵ
	/// \param shader_program_handle
	/// \param uniform_name
	/// \param value
	static void ProduceRenderTaskSetUniform1i(unsigned int shader_program_handle, const char* uniform_name, int value);

	/// ��VAO������
	/// \param vao_handle
	/// \param inex_count
	static void ProduceRenderTaskBindVAOAndDrawElements(unsigned int vao_handle, unsigned int vertex_index_num);

	/// <summary>
	/// ����clear_flag���������ɫ����
	/// </summary>
	static void ProduceRenderTaskSetClearFlagAndClearColorBuffer(unsigned int clear_flag, float clear_color_r, float clear_color_g, float clear_color_b, float clear_color_a);
	/// <summary>
	/// ����ģ����Ժ���
	/// </summary>
	static void ProduceRenderTaskSetStencilFunc();
	/// <summary>
	/// ����ģ�����
	/// </summary>
	static void ProduceRenderTaskSetStencilOp();
	/// <summary>
	/// �������ģ�建��ֵ
	/// </summary>
	static void ProduceRenderTaskSetStencilBufferClearValue();
	/// <summary>
	/// ��Ⱦ����
	/// </summary>
	static void ProduceRenderTaskEndFrame();
};
#endif
