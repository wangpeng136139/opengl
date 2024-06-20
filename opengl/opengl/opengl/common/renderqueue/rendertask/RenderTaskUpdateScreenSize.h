#ifndef UNTITLED_RENDERTASKUPDATESCREENSIZE_H
#define UNTITLED_RENDERTASKUPDATESCREENSIZE_H

#include "RenderTaskBase.h"
class RenderTaskUpdateScreenSize:public RenderTaskBase
{
public:
	RenderTaskUpdateScreenSize()
	{
		render_command_ = RenderCommand::UPDATE_SCREEN_SIZE;
	}

	~RenderTaskUpdateScreenSize(){};
};
#endif

