#ifndef UNTITLED_RENDERTASKDELETETEXTURES_H
#define UNTITLED_RENDERTASKDELETETEXTURES_H
#include "RenderTaskBase.h"
/// ɾ��Texture����
class RenderTaskDeleteTextures : public RenderTaskBase {
public:
    RenderTaskDeleteTextures() {
        render_command_ = RenderCommand::DELETE_TEXTURES;
    }
    ~RenderTaskDeleteTextures() {
        free(texture_handle_array_);
    }
public:
    unsigned int* texture_handle_array_ = nullptr;//�洢������������
    int texture_count_ = 0;//��������
};


#endif

