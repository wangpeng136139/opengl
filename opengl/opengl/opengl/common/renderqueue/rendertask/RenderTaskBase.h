#ifndef UNTITLED_RENDERTASKBASE_H
#define UNTITLED_RENDERTASKBASE_H
#include "RenderCommand.h"
class RenderTaskBase
{
public:
    RenderTaskBase() {
        render_command_ = RenderCommand::NONE;
    }
    virtual ~RenderTaskBase() {}
public:
    RenderCommand render_command_;//渲染命令
    bool need_return_result_ = false;//是否需要回传结果
    bool return_result_set_ = false;//是否设置好了回传结果
};

#endif
