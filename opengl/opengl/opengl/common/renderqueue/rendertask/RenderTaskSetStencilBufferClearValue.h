
#ifndef UNTITLED_RENDERTASKSETSTENCILBUFFERCLEARVALUE_H
#define UNTITLED_RENDERTASKSETSTENCILBUFFERCLEARVALUE_H

#include "RenderTaskBase.h"
/// �������ģ�建��ֵ
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