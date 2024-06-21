#ifndef UNTITLED_RENDERTASKSETSTENCILFUNC_H
#define UNTITLED_RENDERTASKSETSTENCILFUNC_H
#include "RenderTaskBase.h"


/// ����ģ����Ժ���
class RenderTaskSetStencilFunc :public RenderTaskBase {
public:
    RenderTaskSetStencilFunc() {
        render_command_ = RenderCommand::SET_STENCIL_FUNC;
    }
    ~RenderTaskSetStencilFunc() {}
public:
    unsigned int stencil_func_;
    int stencil_ref_;
    unsigned int stencil_mask_;
};
#endif
