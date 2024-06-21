#ifndef UNTITLED_RENDERTASKCOMPILESHADER_H
#define UNTITLED_RENDERTASKCOMPILESHADER_H

#include "RenderTaskBase.h"
class RenderTaskCompileShader :public RenderTaskBase
{
public:
	RenderTaskCompileShader()
	{
		render_command_ = RenderCommand::COMPILE_SHADER;
	}

	~RenderTaskCompileShader() {
		free(vertex_shader_source_);
		free(fragment_shader_source_);
		vertex_shader_source_ = nullptr;
		fragment_shader_source_ = nullptr;
		shader_program_handle_ = 0;
	};
public:
	char* vertex_shader_source_ = nullptr;
	char* fragment_shader_source_ = nullptr;
	unsigned int shader_program_handle_ = 0;
};

#endif