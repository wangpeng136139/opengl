
#ifndef UNTITLED_APPLICATION_H
#define UNTITLED_APPLICATION_H


#include "../engine_head.h"

class Application
{
public:
	static void Init();
    static void Run();
	static void Render();
	static void Update();
	static void FixedUpdate();
	static void UpdateScreenSize();
	static void set_data_path(std::string data_path) { app_data_ = data_path; }
public:
	static  std::string app_data_;
	static  std::string streammingAssetPath;
	static GLFWwindow* glfw_window_;
};

#endif