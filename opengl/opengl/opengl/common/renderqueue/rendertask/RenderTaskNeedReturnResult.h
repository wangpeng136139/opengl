#ifndef UNTITLED_RENDERTASKNEEDRETURNRESULT_H
#define UNTITLED_RENDERTASKNEEDRETURNRESULT_H

#include "RenderTaskBase.h"
/// ��Ҫ�ش����������������
class RenderTaskNeedReturnResult : public RenderTaskBase {
public:
    RenderTaskNeedReturnResult() {
        render_command_ = RenderCommand::NONE;
        need_return_result_ = true;
    }
    ~RenderTaskNeedReturnResult() {}
    /// �ȴ���������Ⱦ�߳�ִ����ϣ������ûش���������߳��õ���������ִ����һ�����롣
    virtual void Wait() {
        while (return_result_set_ == false) {}
    }
};

#endif