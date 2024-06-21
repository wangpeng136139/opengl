#ifndef UNTITLED_RENDERTASKENDFRAME_H
#define UNTITLED_RENDERTASKENDFRAME_H

#include "RenderTaskNeedReturnResult.h"

/// 特殊任务：帧结束标志，渲染线程收到这个任务后，刷新缓冲区，设置帧结束。
class RenderTaskEndFrame : public RenderTaskNeedReturnResult {
public:
    RenderTaskEndFrame() {
        render_command_ = RenderCommand::END_FRAME;
    }
    ~RenderTaskEndFrame() {}
};

#endif