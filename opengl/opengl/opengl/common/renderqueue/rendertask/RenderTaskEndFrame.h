#ifndef UNTITLED_RENDERTASKENDFRAME_H
#define UNTITLED_RENDERTASKENDFRAME_H

#include "RenderTaskNeedReturnResult.h"

/// ��������֡������־����Ⱦ�߳��յ���������ˢ�»�����������֡������
class RenderTaskEndFrame : public RenderTaskNeedReturnResult {
public:
    RenderTaskEndFrame() {
        render_command_ = RenderCommand::END_FRAME;
    }
    ~RenderTaskEndFrame() {}
};

#endif