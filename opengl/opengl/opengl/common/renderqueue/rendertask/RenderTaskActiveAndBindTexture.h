/// ���������
#ifndef UNTITLED_RENDERTASKACTIVEANDBINDTEXTURE_H
#define UNTITLED_RENDERTASKACTIVEANDBINDTEXTURE_H
#include "RenderTaskBase.h"
class RenderTaskActiveAndBindTexture :public RenderTaskBase {
public:
    RenderTaskActiveAndBindTexture() {
        render_command_ = RenderCommand::ACTIVE_AND_BIND_TEXTURE;
    }
    ~RenderTaskActiveAndBindTexture() {}
public:
    unsigned int texture_uint_;//����Ԫ
    unsigned int texture_handle_;//������
};

#endif