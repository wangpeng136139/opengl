
#ifndef UNTITLED_RENDERTASKSETSTENCILBUFFERCLEARVALUE_H
#define UNTITLED_RENDERTASKSETSTENCILBUFFERCLEARVALUE_H

#include "RenderTaskBase.h"
/// 设置清除模板缓冲值
class RenderTaskSetStencilBufferClearValue :public RenderTaskBase {
public:
    RenderTaskSetStencilBufferClearValue() {
        render_command_ = RenderCommand::SET_STENCIL_BUFFER_CLEAR_VALUE;
    }
    ~RenderTaskSetStencilBufferClearValue() {}
public:
    int clear_value_;
};

#endif