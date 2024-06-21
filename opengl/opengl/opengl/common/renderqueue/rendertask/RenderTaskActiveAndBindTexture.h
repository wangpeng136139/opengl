/// 激活并绑定纹理
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
    unsigned int texture_uint_;//纹理单元
    unsigned int texture_handle_;//纹理句柄
};

#endif