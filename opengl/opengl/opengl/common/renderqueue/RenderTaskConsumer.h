#ifndef UNTITLED_RENDERTASKCONSUMER_H
#define UNTITLED_RENDERTASKCONSUMER_H

#include <thread>
#include "rendertask/rendertask_head.h"
class GLFWwindow;

class RenderTaskConsumer
{
public:
	static void Init(GLFWwindow* window);

	static void Exit();
public:
	static void ProcessTask();
private:
	static GLFWwindow* window_;
	static std::thread render_thread_;//‰÷»æœﬂ≥Ã
};

#endif

