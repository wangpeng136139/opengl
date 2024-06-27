#include "Application.h"
#include "../render_head.h"
#include "../eventstytem/Input.h";
#include "../common/Debug.h"
#include "../common/Screen.h"
#include "../common/Time.h"
#include "../renderdevice/RenderDevice.h"
#include "../renderdevice/RenderDeviceOpenGL.h"
#include "../sound/Audio.h"
#include "../renderqueue/RenderTaskConsumer.h"
#include "../renderqueue/RenderTaskProducer.h"

class RenderTaskConsumer;
std::string Application::app_data_;
std::string Application::streammingAssetPath;
GLFWwindow* Application::glfw_window_;

/// ���̻ص�
/// \param window
/// \param key
/// \param scancode
/// \param action
/// \param mods
static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    Input::RecordKey(key, action);
}
/// ��갴���ص�
/// \param window
/// \param button
/// \param action
/// \param mods
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
    Input::RecordKey(button, action);
    std::cout << "mouse_button_callback:" << button << "," << action << std::endl;
}
/// ����ƶ��ص�
/// \param window
/// \param x
/// \param y
void mouse_move_callback(GLFWwindow* window, double x, double y)
{
    Input::set_mousePosition(x, y);
    std::cout << "mouse_move_callback:" << x << "," << y << std::endl;
}
/// �����ֻص�
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

/// <summary>
/// ��ʼ������
/// </summary>
void Application::Init()
{
    EASY_MAIN_THREAD;
    profiler::startListen();// ����profiler���������ȴ�gui���ӡ�
    RenderDevice::Init(new RenderDeviceOpenGL());
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



 

    glfwSetKeyCallback(glfw_window_, key_callback);
    glfwSetMouseButtonCallback(glfw_window_, mouse_button_callback);
    glfwSetScrollCallback(glfw_window_, mouse_scroll_callback);
    glfwSetCursorPosCallback(glfw_window_, mouse_move_callback);
    //��ʼ����Ⱦ����������(������Ⱦ�߳�)
    RenderTaskConsumer::Init(glfw_window_);

    UpdateScreenSize();
    //��Ч��ʼ��
    Audio::Init();
}

void Application::UpdateScreenSize() {
    RenderTaskProducer::ProduceRenderTaskUpdateScreenSize();
}


void Application::Run()
{

    while (true) 
    {
        EASY_BLOCK("Frame") {
        if (!glfwWindowShouldClose(glfw_window_))
        {
            Update();
            Render();

            glfwSwapBuffers(glfw_window_);   
            EASY_BLOCK("glfwPollEvents")
            {
                glfwPollEvents();
            }
            EASY_END_BLOCK
        }
        EASY_END_BLOCK
    }
   }

    RenderTaskConsumer::Exit();
    glfwDestroyWindow(glfw_window_);

    glfwTerminate();
    exit(EXIT_SUCCESS);
}

void Application::FixedUpdate()
{
    EASY_FUNCTION(profiler::colors::Magenta); // ��Ǻ���
}
void Application::Render()
{
    EASY_FUNCTION(profiler::colors::Magenta); // ��Ǻ���
    //�������������ÿ�������View Projection����������һ����Ⱦ��
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
    EASY_FUNCTION(profiler::colors::Magenta); // ��Ǻ���
    Time::Update();
    UpdateScreenSize();

    GameObject::Foreach([](GameObject* game_object) {
        game_object->ForeachComponent([](Component* component) {
            component->Update();
            });
        });

    Input::Update();
    Audio::Update();
}

	