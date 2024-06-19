#ifndef UNTITLED_RENDER_TASK_QUEUE_H
#define UNTITLED_RENDER_TASK_QUEUE_H

#include <spscqueue/include/rigtorp/SPSCQueue.h>
class RenderTaskBase;

class RenderTaskQueue
{
public:
    /// ������񵽶���
    /// \param render_task
    static void Push(RenderTaskBase* render_task) {
        render_task_queue_.push(render_task);
    }

    /// �������Ƿ�û��������
    /// \return
    static bool Empty() {
        return render_task_queue_.empty();
    }

    /// ��ȡ�����е�һ������
    /// \return
    static RenderTaskBase* Front() {
        return *(render_task_queue_.front());
    }

    /// ���������е�һ������
    static void Pop() {
        render_task_queue_.pop();
    }

    /// ��ȡ�����е���������
    static size_t Size() {
        return render_task_queue_.size();
    }
private:
	static rigtorp::SPSCQueue<RenderTaskBase*> render_task_queue_;//��Ⱦ�������
};


#endif
