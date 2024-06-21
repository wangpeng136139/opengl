#ifndef UNTITLED_RENDERTASKCLEAR_H
#define UNTITLED_RENDERTASKCLEAR_H

#include "RenderTaskBase.h"


class RenderTaskClear :public RenderTaskBase {
public:
    RenderTaskClear() {
        render_command_ = RenderCommand::SET_CLEAR_FLAG_AND_CLEAR_COLOR_BUFFER;
    }
    ~RenderTaskClear() {}
public:
    unsigned int clear_flag_;
    float clear_color_r_;
    float clear_color_g_;
    float clear_color_b_;
    float clear_color_a_;
};
#endif
