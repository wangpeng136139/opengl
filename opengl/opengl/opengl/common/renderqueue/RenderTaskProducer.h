#ifndef UNTITLED_RENDER_RENDERTASKPRODUCER_H
#define UNTITLED_RENDER_RENDERTASKPRODUCER_H

#include "rendertask/rendertask_head.h";
#include "RenderTaskQueue.h"

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
	static void ProduceRenderTaskCreateVAO();
	/// <summary>
	/// ����vbo
	/// </summary>
	static void ProduceRenderTaskUpdateVBOSubData();
	/// <summary>
	/// ����״̬,������ر�
	/// </summary>
	static void ProduceRenderTaskSetEnableState();
	/// <summary>
	/// ���û�Ϻ���
	/// </summary>
	static void ProduceRenderTaskSetBlenderFunc();
	/// <summary>
	/// ����4x4����
	/// </summary>
	static void ProduceRenderTaskSetUniformMatrix4fv();
	/// <summary>
	/// ���������
	/// </summary>
	static void ProduceRenderTaskActiveAndBindTexture();
	/// <summary>
	/// �ϴ�1��intֵ
	/// </summary>
	static void ProduceRenderTaskSetUniform1i();
	/// <summary>
	/// ��VAO������
	/// </summary>
	static void ProduceRenderTaskBindVAOAndDrawElements();
	/// <summary>
	/// ����clear_flag���������ɫ����
	/// </summary>
	static void ProduceRenderTaskSetClearFlagAndClearColorBuffer();
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
