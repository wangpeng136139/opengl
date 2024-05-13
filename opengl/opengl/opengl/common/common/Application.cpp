#include "Application.h"
#include "../eventstytem/Input.h";
#include "../component/GameObject.h";
#include "../render/camera/Camera.h"
#include "../render/mesh/MeshRenderer.h"


#include <glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtx/transform2.hpp>
#include<glm/gtx/euler_angles.hpp>
#include "../common/Debug.h"
#include "../common/Screen.h"
#include "../renderdevice/RenderDevice.h"
#include "../renderdevice/RenderDeviceOpenGL.h"

std::string Application::app_data_;
std::string Application::streammingAssetPath;
GLFWwindow* Application::glfw_window_;

/// 键盘回调
/// \param window
/// \param key
/// \param scancode
/// \param action
/// \param mods
static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    Input::RecordKey(key, action);
}
/// 鼠标按键回调
/// \param window
/// \param button
/// \param action
/// \param mods
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
    Input::RecordKey(button, action);
    std::cout << "mouse_button_callback:" << button << "," << action << std::endl;
}
/// 鼠标移动回调
/// \param window
/// \param x
/// \param y
void mouse_move_callback(GLFWwindow* window, double x, double y)
{
    Input::set_mousePosition(x, y);
    std::cout << "mouse_move_callback:" << x << "," << y << std::endl;
}
/// 鼠标滚轮回调
/// \param window
/// \param x
/// \param y
void mouse_scroll_callback(GLFWwindow* window, double x, double y)
{
    Input::RecordScroll(y);
    std::cout << "mouse_scroll_callback:" << x << "," << y << std::endl;
}

static void error_callback(int error, const char* description)
{
    fprintf(stderr, "Error: %s\n", description);
}

void Application::Init()
{
    glfwSetErrorCallback(error_callback);
    if (!glfwInit())
    {
        DEBUG_LOG_ERROR("glfw init failed!");
        exit(EXIT_FAILURE);
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    glfw_window_ = glfwCreateWindow(960, 640, "Simple example", NULL, NULL);
    if (!glfw_window_)
    {
        DEBUG_LOG_ERROR("glfwCreateWindow error!");
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glfwMakeContextCurrent(glfw_window_);
    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

    UpdateScreenSize();
    glfwSwapInterval(1);

    glfwSetKeyCallback(glfw_window_, key_callback);
    glfwSetMouseButtonCallback(glfw_window_, mouse_button_callback);
    glfwSetScrollCallback(glfw_window_, mouse_scroll_callback);
    glfwSetCursorPosCallback(glfw_window_, mouse_move_callback);
}

void Application::UpdateScreenSize() {
    int width, height;
    glfwGetFramebufferSize(glfw_window_, &width, &height);
    glViewport(0, 0, width, height);
    Screen::set_width_height(width, height);
}


void Application::Run()
{
    RenderDevice::Init(new RenderDeviceOpenGL());
    while (!glfwWindowShouldClose(glfw_window_))
    {
        Update();
        Render();

        glfwSwapBuffers(glfw_window_);

        glfwPollEvents();
    }

    glfwDestroyWindow(glfw_window_);

    glfwTerminate();
    exit(EXIT_SUCCESS);
}

void Application::Render()
{
    //遍历所有相机，每个相机的View Projection，都用来做一次渲染。
    Camera::Foreach([&]() {
        GameObject::Foreach([](GameObject* game_object) {
            auto component = game_object->GetComponent("MeshRenderer");
            if (!component) {
                return;
            }
            auto mesh_renderer = dynamic_cast<MeshRenderer*>(component);
            if (!mesh_renderer) {
                return;
            }
            mesh_renderer->Render();
            });
        });
}


void Application::Update()
{
    UpdateScreenSize();

    GameObject::Foreach([](GameObject* game_object) {
        game_object->ForeachComponent([](Component* component) {
            component->Update();
            });
        });

    Input::Update();
}

	