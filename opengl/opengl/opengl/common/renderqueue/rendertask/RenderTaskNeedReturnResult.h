#ifndef UNTITLED_RENDERTASKNEEDRETURNRESULT_H
#define UNTITLED_RENDERTASKNEEDRETURNRESULT_H

#include "RenderTaskBase.h"
/// 需要回传结果的阻塞性任务
class RenderTaskNeedReturnResult : public RenderTaskBase {
public:
    RenderTaskNeedReturnResult() {
        render_command_ = RenderCommand::NONE;
        need_return_result_ = true;
    }
    ~RenderTaskNeedReturnResult() {}
    /// 等待任务在渲染线程执行完毕，并设置回传结果。主线程拿到结果后才能执行下一步代码。
    virtual void Wait() {
        while (return_result_set_ == false) {}
    }
};

#endif