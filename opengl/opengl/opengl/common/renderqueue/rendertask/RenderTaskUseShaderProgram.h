#ifndef UNTITLED_RENDERTASKUSESHADERPROGRAM_H
#define UNTITLED_RENDERTASKUSESHADERPROGRAM_H
#include "RenderTaskBase.h"
class RenderTaskUseShaderProgram:public RenderTaskBase
{
public:
	RenderTaskUseShaderProgram()
	{
		render_command_ = RenderCommand::USE_SHADER_PROGRAM;
	}

	~RenderTaskUseShaderProgram() {
	};
public:
	unsigned int shader_program_handle_ = 0;
};

#endif
