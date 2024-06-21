#ifndef UNTITLED_RENDERTASKDELETETEXTURES_H
#define UNTITLED_RENDERTASKDELETETEXTURES_H
#include "RenderTaskBase.h"
/// 删除Texture任务
class RenderTaskDeleteTextures : public RenderTaskBase {
public:
    RenderTaskDeleteTextures() {
        render_command_ = RenderCommand::DELETE_TEXTURES;
    }
    ~RenderTaskDeleteTextures() {
        free(texture_handle_array_);
    }
public:
    unsigned int* texture_handle_array_ = nullptr;//存储纹理句柄的数组
    int texture_count_ = 0;//纹理数量
};


#endif

