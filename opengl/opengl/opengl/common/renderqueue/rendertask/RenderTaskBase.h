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
    RenderCommand render_command_;//��Ⱦ����
    bool need_return_result_ = false;//�Ƿ���Ҫ�ش����
    bool return_result_set_ = false;//�Ƿ����ú��˻ش����
};

#endif
