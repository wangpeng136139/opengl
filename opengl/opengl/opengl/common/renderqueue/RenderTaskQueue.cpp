#include "RenderTaskQueue.h"
rigtorp::SPSCQueue<RenderTaskBase*> RenderTaskQueue::render_task_queue_(50);
