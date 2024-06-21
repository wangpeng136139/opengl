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
	/// <summary>
	/// ����VAO
	/// </summary>
	/// <param name="task_base"></param>
	/// <returns></returns>
	static void CreateVAO(RenderTaskBase* task_base);
	/// <summary>
	/// ����vbo
	/// </summary>
	static void UpdateVBOSubData(RenderTaskBase* task_base);
	/// <summary>
	/// ��������
	/// </summary>
	static void CreateTexImage2D(RenderTaskBase* task_base);
	/// <summary>
	/// ɾ������
	/// </summary>
	static void DeleteTextures(RenderTaskBase* task_base);
	/// <summary>
	/// �ֲ���������
	/// </summary>
	/// <param name="task_base"></param>
	static void UpdateTextureSubImage2D(RenderTaskBase* task_base);
	/// <summary>
	/// ����״̬��������ر�
	/// </summary>
	/// <param name="task_base"></param>
	static void SetEnableState(RenderTaskBase* task_base);
	/// <summary>
	/// ���û������
	/// </summary>
	/// <param name="task_base"></param>
	static void SetBlendFunc(RenderTaskBase* task_base);
	/// <summary>
	/// ���þ���
	/// </summary>
	/// <param name="task_base"></param>
	static void SetUniformMatrix4fv(RenderTaskBase* task_base);
	/// <summary>
	/// ����Ұ�����Ԫ
	/// </summary>
	/// <param name="task_base"></param>
	static void ActiveAndBindTexture(RenderTaskBase* task_base);
	/// <summary>
	/// �ϴ�int
	/// </summary>
	/// <param name="task_base"></param>
	static void SetUniform1i(RenderTaskBase* task_base);
	/// <summary>
	/// ����clear_flag���������ɫ����
	/// </summary>
	/// <param name="task_base"></param>
	static void SetClearFlagAndClearColorBuffer(RenderTaskBase* task_base);
	/// <summary>
	/// ��VAO������
	/// </summary>
	/// <param name="task_base"></param>
	static void BindVAOAndDrawElements(RenderTaskBase* task_base);
	/// <summary>
	/// ������ģ����Ժ���������
	/// </summary>
	/// <param name="task_base"></param>
	static void SetStencilFunc(RenderTaskBase* task_base);
	/// <summary>
	/// ����ģ�����
	/// </summary>
	/// <param name="task_base"></param>
	static void SetStencilOp(RenderTaskBase* task_base);
	/// <summary>
	/// �������ģ�建��ֵ
	/// </summary>
	/// <param name="task_base"></param>
	static void SetStencilBufferClearValue(RenderTaskBase* task_base);
	/// <summary>
	/// ֡������־����Ⱦ�߳��յ���������ˢ�»�����������֡������
	/// </summary>
	/// <param name="task_base"></param>
	static void EndFrame(RenderTaskBase* task_base);
private:
	static GLFWwindow* window_;
	static std::thread render_thread_;//��Ⱦ�߳�
};

#endif

