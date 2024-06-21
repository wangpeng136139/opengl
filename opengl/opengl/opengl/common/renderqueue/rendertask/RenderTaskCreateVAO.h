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
	unsigned int shader_program_handle_ = 0;//着色器程序句柄
	unsigned int vao_handle_ = 0;//VAO句柄
	unsigned int vbo_handle_ = 0;//VBO句柄
	unsigned int vertex_data_size_;//顶点数据大小
	unsigned int vertex_data_stride_;
	void* vertex_data_;//顶点数据
	unsigned int vertex_index_data_size_;//顶点索引数据大小
	void* vertex_index_data_;//顶点索引数据
};
#endif

