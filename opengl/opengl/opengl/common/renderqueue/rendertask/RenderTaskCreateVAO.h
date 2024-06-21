#ifndef UNTITLED_RENDERTASKCREATEVAO_H
#define UNTITLED_RENDERTASKCREATEVAO_H
#include "RenderTaskBase.h"

class RenderTaskCreateVAO :public RenderTaskBase
{
public:
	RenderTaskCreateVAO()
	{
		render_command_ = RenderCommand::CREATE_VAO;
	}

	~RenderTaskCreateVAO() {
		free(vertex_data_);
		free(vertex_index_data_);
		vertex_data_ = nullptr;
		vertex_index_data_ = nullptr;
	};
public:
	unsigned int shader_program_handle_ = 0;//��ɫ��������
	unsigned int vao_handle_ = 0;//VAO���
	unsigned int vbo_handle_ = 0;//VBO���
	unsigned int vertex_data_size_;//�������ݴ�С
	unsigned int vertex_data_stride_;
	void* vertex_data_;//��������
	unsigned int vertex_index_data_size_;//�����������ݴ�С
	void* vertex_index_data_;//������������
};
#endif

