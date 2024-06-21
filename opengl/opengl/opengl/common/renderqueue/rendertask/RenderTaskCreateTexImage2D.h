#ifndef UNTITLED_RENDERTASKCREATETEXIMAGE2D_H
#define UNTITLED_RENDERTASKCREATETEXIMAGE2D_H
#include "RenderTaskBase.h"

class RenderTaskCreateTexImage2D : public RenderTaskBase {
public:
    RenderTaskCreateTexImage2D() {
        render_command_ = RenderCommand::CREATE_TEX_IMAGE2D;
    }
    ~RenderTaskCreateTexImage2D() {
        free(data_);
    }
public:
    unsigned int texture_handle_ = 0;
    int width_;
    int height_;
    unsigned int gl_texture_format_;//GL�ڲ������ʽ
    unsigned int client_format_;//�ͻ��������ʽ
    unsigned int data_type_;
    unsigned char* data_;
};

#endif

