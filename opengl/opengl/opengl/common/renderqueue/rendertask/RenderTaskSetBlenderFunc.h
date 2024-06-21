#ifndef UNTITLED_RENDERTASKSETBLENDERFUNC_H
#define UNTITLED_RENDERTASKSETBLENDERFUNC_H
#include "RenderTaskBase.h"
/// 设置混合函数
class RenderTaskSetBlenderFunc : public RenderTaskBase {
public:
    RenderTaskSetBlenderFunc() {
        render_command_ = RenderCommand::SET_BLENDER_FUNC;
    }
    ~RenderTaskSetBlenderFunc() {}
public:
    unsigned int source_blending_factor_;//源混合因子
    unsigned int destination_blending_factor_;//目标混合因子
};
#endif 
