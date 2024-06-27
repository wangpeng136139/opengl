#include "RenderTaskProducer.h"


void RenderTaskProducer::ProduceRenderTaskUpdateScreenSize()
{
    RenderTaskUpdateScreenSize* task = new RenderTaskUpdateScreenSize();
    RenderTaskQueue::Push(task);
}

void RenderTaskProducer::ProduceRenderTaskSetClearFlagAndClearColorBuffer(unsigned int clear_flag, float clear_color_r, float clear_color_g, float clear_color_b, float clear_color_a) {
    RenderTaskClear* task = new RenderTaskClear();
    task->clear_flag_ = clear_flag;
    task->clear_color_r_ = clear_color_r;
    task->clear_color_g_ = clear_color_g;
    task->clear_color_b_ = clear_color_b;
    task->clear_color_a_ = clear_color_a;
    RenderTaskQueue::Push(task);
}

