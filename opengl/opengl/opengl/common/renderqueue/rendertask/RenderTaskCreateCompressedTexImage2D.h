#ifndef UNTITLED_RENDERTASKCREATECOMPRESSEDTEXIMAGE2D_H
#define UNTITLED_RENDERTASKCREATECOMPRESSEDTEXIMAGE2D_H

#include "RenderTaskBase.h"
class RenderTaskCreateCompressedTexImage2D:public RenderTaskBase
{
public:
	RenderTaskCreateCompressedTexImage2D()
	{
		render_command_ = RenderCommand::CREATE_COMPRESSED_TEX_IMAGE2D;
	}

	~RenderTaskCreateCompressedTexImage2D() {
		free(data_);
	};
public:
	unsigned int texture_handle_ = 0;
	int width_;
	int height_;
	unsigned int texture_format_;
	int compress_size_;
	unsigned char* data_;
};

#endif
