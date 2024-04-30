#include <iostream>
#include <glad/glad.h>
#define GLM_ENABLE_EXPERIMENTAL
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtx/transform2.hpp>
#include<glm/gtx/euler_angles.hpp>
#include <glm/ext.hpp>
#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include "../common/render/textures/Texture2D.h"
#include "../common/render/mesh/MeshRenderer.h"
#include "../common/component/GameObject.h"
#include "../common/component/Transform.h"
#include "../common/render/camera/Camera.h"
#include "../common/eventstytem/Input.h";
#include <iostream>
#include "../common/eventstytem/key_code.h"
#include <rttr/type>
#include <rttr/registration>
using namespace std;


using namespace std;

//顶点


GLFWwindow* window_use_key_mouse_control;
GLint mvp_location_use_key_mouse_control, vpos_location_use_key_mouse_control, vcol_location_use_key_mouse_control, u_diffuse_texture_location_use_key_mouse_control, a_uv_location_use_key_mouse_control;
GLuint kVBO_use_key_mouse_control, kEBO_use_key_mouse_control, kVAO_use_key_mouse_control;
Texture2D* texture2d_use_key_mouse_control = nullptr;
MeshFilter* mesh_load_use_key_mouse_control = nullptr;

/// 创建VAO
void GeneratorVertexArrayObject_use_key_mouse_control() {
    glGenVertexArrays(1, &kVAO_use_key_mouse_control);
}


//创建VBO和EBO
void GeneratorBufferObject_use_key_mouse_control()
{
    //在GPU上创建缓冲区对象
    glGenBuffers(1, &kVBO_use_key_mouse_control);
    //将缓冲区对象指定为顶点缓冲区对象
    glBindBuffer(GL_ARRAY_BUFFER, kVBO_use_key_mouse_control);
    //上传顶点数据到缓冲区对象
    glBufferData(GL_ARRAY_BUFFER, mesh_load_use_key_mouse_control->GetMesh()->vertex_num_ * sizeof(Vertex), mesh_load_use_key_mouse_control->GetMesh()->vertex_data_, GL_STATIC_DRAW);

    //在GPU上创建缓冲区对象
    glGenBuffers(1, &kEBO_use_key_mouse_control);
    //将缓冲区对象指定为顶点索引缓冲区对象
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, kEBO_use_key_mouse_control);
    //上传顶点索引数据到缓冲区对象
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, mesh_load_use_key_mouse_control->GetMesh()->vertex_index_num_ * sizeof(unsigned short), mesh_load_use_key_mouse_control->GetMesh()->vertex_index_data_, GL_STATIC_DRAW);
    //设置VAO
    glBindVertexArray(kVAO_use_key_mouse_control);
    {
        //指定当前使用的VBO
        glBindBuffer(GL_ARRAY_BUFFER, kVBO_use_key_mouse_control);
        //将Shader变量(a_pos)和顶点坐标VBO句柄进行关联，最后的0表示数据偏移量。
        glVertexAttribPointer(vpos_location_use_key_mouse_control, 3, GL_FLOAT, false, sizeof(Vertex), 0);
        //启用顶点Shader属性(a_color)，指定与顶点颜色数据进行关联。
        glVertexAttribPointer(vcol_location_use_key_mouse_control, 4, GL_FLOAT, false, sizeof(Vertex), (void*)(sizeof(float) * 3));
        //将Shader变量(a_uv)和顶点UV坐标VBO句柄进行关联。
        glVertexAttribPointer(a_uv_location_use_key_mouse_control, 2, GL_FLOAT, false, sizeof(Vertex), (void*)(sizeof(float) * (3 + 4)));

        glEnableVertexAttribArray(vpos_location_use_key_mouse_control);
        glEnableVertexAttribArray(vcol_location_use_key_mouse_control);
        glEnableVertexAttribArray(a_uv_location_use_key_mouse_control);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, kEBO_use_key_mouse_control);
    }
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

static void error_callback_use_key_mouse_control(int error, const char* description)
{
    fprintf(stderr, "Error: %s\n", description);
}


/// 键盘回调
/// \param window
/// \param key
/// \param scancode
/// \param action
/// \param mods
static void key_callback_use_key_mouse_control(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    Input::RecordKey(key, action);
}
/// 鼠标按键回调
/// \param window
/// \param button
/// \param action
/// \param mods
void mouse_button_callback_use_key_mouse_control(GLFWwindow* window, int button, int action, int mods)
{
    Input::RecordKey(button, action);
    std::cout << "mouse_button_callback:" << button << "," << action << std::endl;
}
/// 鼠标移动回调
/// \param window
/// \param x
/// \param y
void mouse_move_callback_use_key_mouse_control(GLFWwindow* window, double x, double y)
{
    Input::set_mousePosition(x, y);
    std::cout << "mouse_move_callback:" << x << "," << y << std::endl;
}
/// 鼠标滚轮回调
/// \param window
/// \param x
/// \param y
void mouse_scroll_callback_use_key_mouse_control(GLFWwindow* window, double x, double y)
{
    Input::RecordScroll(y);
    std::cout << "mouse_scroll_callback:" << x << "," << y << std::endl;
}

void init_opengl_use_key_mouse_control()
{
    //设置错误回调
    glfwSetErrorCallback(error_callback_use_key_mouse_control);
    /* 初始化glfw */
    if (!glfwInit())
        exit(EXIT_FAILURE);

    //指定opengl版本号
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
    //创建窗口
    window_use_key_mouse_control = glfwCreateWindow(960, 640, "Simple example", NULL, NULL);
    if (!window_use_key_mouse_control)
    {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glfwMakeContextCurrent(window_use_key_mouse_control);
    // 加载OpenGL 指针   
    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
    //交换间隔表示交换缓冲区之前等待的帧数，通常称为vsync。
   //默认情况下，交换间隔为0，但因为屏幕每秒只更新60-75次，所以大部分的画面不会被显示。
   //而且，缓冲区有可能在屏幕更新的中间交换，出现屏幕撕裂的情况。
   //所以，可以将该间隔设为1，即每帧更新一次。它可以设置为更高的值，但这可能导致输入延迟。
    glfwSwapInterval(1);

    glfwSetKeyCallback(window_use_key_mouse_control, key_callback_use_key_mouse_control);
    glfwSetMouseButtonCallback(window_use_key_mouse_control, mouse_button_callback_use_key_mouse_control);
    glfwSetScrollCallback(window_use_key_mouse_control, mouse_scroll_callback_use_key_mouse_control);
    glfwSetCursorPosCallback(window_use_key_mouse_control, mouse_move_callback_use_key_mouse_control);

}
//
///// 编译、链接Shader  
//void compile_shader_use_key_mouse_control()
//{
//    Shader * shader = new Shader();
//    shader->Find("resources/shader/Unlit");
//    program_use_key_mouse_control = shader->GetProgramId();
//}


//创建Texture
void CreateTexturem_use_key_mouse_control(std::string image_file_path)
{
    texture2d_use_key_mouse_control = Texture2D::LoadFromFileTpc(image_file_path);
}


int draw_use_key_mouse_control(void)
{

    //VertexRemoveDumplicate_use_key_mouse_control();
   //MeshFilter::ExportMesh("cube.mesh", kVertexRemoveDumplicateVectorv_use_key_mouse_control, kVertexIndexVector_use_key_mouse_control);
    init_opengl_use_key_mouse_control();
    /*CreateTexturem_use_key_mouse_control("resources/textures/1.cpt");
      string a = "resources/textures/1.png";
      string b  = "resources/textures/1.cpt";
      Texture2D::CompressImageFile(a,b);
      return 0;*/
    GameObject* obj = new GameObject("test");

    Transform* transform = dynamic_cast<Transform*>(obj->AddComponent("Transform"));

    Material* material = new Material();
    material->Parse("resources/material/cube.mat");

    mesh_load_use_key_mouse_control = new MeshFilter();
    mesh_load_use_key_mouse_control->LoadMesh("resources/mesh/cube.mesh");


    MeshRenderer* meshRender = dynamic_cast<MeshRenderer*>(obj->AddComponent("MeshRenderer"));
    meshRender->SetMaterial(material);
    meshRender->SetMeshFilter(mesh_load_use_key_mouse_control);


    GameObject* camera_obj = new GameObject("Main_Camera");
    Transform* cameraTransform = dynamic_cast<Transform*>(camera_obj->AddComponent("Transform"));
    cameraTransform->set_position(glm::vec3(0, 0, 10));
    Camera* camera = dynamic_cast<Camera*>(camera_obj->AddComponent("Camera"));

    //上一帧的鼠标位置
    glm::vec2 last_frame_mouse_position = Input::mousePosition();
    while (!glfwWindowShouldClose(window_use_key_mouse_control))
    {
        float ratio;
        int width, height;

        glfwGetFramebufferSize(window_use_key_mouse_control, &width, &height);
        glViewport(0, 0, width, height);
        ratio = width / (float)height;
        //glm::mat4 trans = glm::translate(glm::vec3(0, 0, 0)); //不移动顶点坐标;
        camera->SetView(glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
        camera->SetProjection(60, ratio, 1.1f, 1000.0f);
        camera->Clear();

        //旋转物体
        if (Input::GetKeyDown(KEY_CODE_R)) {
            static float rotate_eulerAngle = 0.f;
            rotate_eulerAngle += 0.1f;
            glm::vec3 rotation = transform->rotation();
            rotation.y = rotate_eulerAngle;
            transform->set_rotation(rotation);
        }

        //旋转相机
        if (Input::GetKeyDown(KEY_CODE_LEFT_ALT) && Input::GetMouseButtonDown(MOUSE_BUTTON_LEFT)) {
            float degrees = Input::mousePosition().x - last_frame_mouse_position.x;

            glm::mat4 old_mat4 = glm::mat4(1.0f);
            std::cout << glm::to_string(old_mat4) << std::endl;

            glm::mat4 rotate_mat4 = glm::rotate(old_mat4, glm::radians(degrees), glm::vec3(0.0f, 1.0f, 0.0f));//以相机所在坐标系位置，计算用于旋转的矩阵，这里是零点，所以直接用方阵。
            glm::vec4 old_pos = glm::vec4(cameraTransform->position(), 1.0f);
            glm::vec4 new_pos = rotate_mat4 * old_pos;//旋转矩阵 * 原来的坐标 = 相机以零点做旋转。
            std::cout << glm::to_string(new_pos) << std::endl;

            cameraTransform->set_position(glm::vec3(new_pos));
        }

        Input::Update();
        meshRender->SetView(camera->view_mat4());
        meshRender->SetProjection(camera->projection_mat4());
        meshRender->TestRender();


        glfwSwapBuffers(window_use_key_mouse_control);
        glfwPollEvents();
    }

    glfwDestroyWindow(window_use_key_mouse_control);

    glfwTerminate();
    exit(EXIT_SUCCESS);
}