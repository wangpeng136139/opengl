#ifndef UNTITLED_RENDERTASKSETENABLESTATE_H
#define UNTITLED_RENDERTASKSETENABLESTATE_H
#include "RenderTaskBase.h"
/// ����״̬��������ر�
class RenderTaskSetEnableState : public RenderTaskBase {
public:
    RenderTaskSetEnableState() {
        render_command_ = RenderCommand::SET_ENABLE_STATE;
    }
    ~RenderTaskSetEnableState() {}
public:
    unsigned int state_;//OpenGL״̬
    bool enable_;//OpenGL״ֵ̬
};

#endif