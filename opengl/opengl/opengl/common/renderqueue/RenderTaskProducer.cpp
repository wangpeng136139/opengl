#include "RenderTaskProducer.h"


void RenderTaskProducer::ProduceRenderTaskUpdateScreenSize()
{
    RenderTaskUpdateScreenSize* task = new RenderTaskUpdateScreenSize();
    RenderTaskQueue::Push(task);
}