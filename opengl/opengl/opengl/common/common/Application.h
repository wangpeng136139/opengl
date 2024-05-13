#pragma once
#include <string>
#include <glad/glad.h>
#define GLM_ENABLE_EXPERIMENTAL
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

class Application
{
public:
	static void Init();
    static void Run();
	static void Render();
	static void Update();
	static void UpdateScreenSize();
	static void set_data_path(std::string data_path) { app_data_ = data_path; }
public:
	static  std::string app_data_;
	static  std::string streammingAssetPath;
	static GLFWwindow* glfw_window_;
};

