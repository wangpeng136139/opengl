#ifndef UNTITLED_RENDERTASKSETENABLESTATE_H
#define UNTITLED_RENDERTASKSETENABLESTATE_H
#include "RenderTaskBase.h"
/// ÉèÖÃ×´Ì¬£¬¿ªÆô»ò¹Ø±Õ
class RenderTaskSetEnableState : public RenderTaskBase {
public:
    RenderTaskSetEnableState() {
        render_command_ = RenderCommand::SET_ENABLE_STATE;
    }
    ~RenderTaskSetEnableState() {}
public:
    unsigned int state_;//OpenGL×´Ì¬
    bool enable_;//OpenGL×´Ì¬Öµ
};

#endif