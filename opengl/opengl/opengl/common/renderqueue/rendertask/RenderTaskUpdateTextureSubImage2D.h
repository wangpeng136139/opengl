#ifndef UNTITLED_RENDERTASKUPDATETEXTURESUBIMAGE2D_H
#define UNTITLED_RENDERTASKUPDATETEXTURESUBIMAGE2D_H

#include "RenderTaskBase.h"
/// 局部更新Texture任务
class RenderTaskUpdateTextureSubImage2D :public RenderTaskBase {
public:
    RenderTaskUpdateTextureSubImage2D() {
        render_command_ = RenderCommand::UPDATE_TEXTURE_SUB_IMAGE2D;
    }
    ~RenderTaskUpdateTextureSubImage2D() {
        free(data_);
    }

public:
    unsigned int texture_handle_;//纹理句柄
    int x_, y_, width_, height_;
    unsigned int client_format_;
    unsigned int data_type_;
    unsigned char* data_;
    unsigned int data_size_;
};

#endif

