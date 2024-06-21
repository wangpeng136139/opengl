#ifndef UNTITLED_RENDERTASKSETSTENCILOP_H
#define UNTITLED_RENDERTASKSETSTENCILOP_H

#include "RenderTaskBase.h"

/// ÉèÖÃÄ£°å²Ù×÷
class RenderTaskSetStencilOp :public RenderTaskBase {
public:
    RenderTaskSetStencilOp() {
        render_command_ = RenderCommand::SET_STENCIL_OP;
    }
    ~RenderTaskSetStencilOp() {}
public:
    unsigned int fail_op_;
    unsigned int z_test_fail_op_;
    unsigned int z_test_pass_op_;
};
#endif