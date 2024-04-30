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

//����


GLFWwindow* window_use_key_mouse_control;
GLint mvp_location_use_key_mouse_control, vpos_location_use_key_mouse_control, vcol_location_use_key_mouse_control, u_diffuse_texture_location_use_key_mouse_control, a_uv_location_use_key_mouse_control;
GLuint kVBO_use_key_mouse_control, kEBO_use_key_mouse_control, kVAO_use_key_mouse_control;
Texture2D* texture2d_use_key_mouse_control = nullptr;
MeshFilter* mesh_load_use_key_mouse_control = nullptr;

/// ����VAO
void GeneratorVertexArrayObject_use_key_mouse_control() {
    glGenVertexArrays(1, &kVAO_use_key_mouse_control);
}


//����VBO��EBO
void GeneratorBufferObject_use_key_mouse_control()
{
    //��GPU�ϴ�������������
    glGenBuffers(1, &kVBO_use_key_mouse_control);
    //������������ָ��Ϊ���㻺��������
    glBindBuffer(GL_ARRAY_BUFFER, kVBO_use_key_mouse_control);
    //�ϴ��������ݵ�����������
    glBufferData(GL_ARRAY_BUFFER, mesh_load_use_key_mouse_control->GetMesh()->vertex_num_ * sizeof(Vertex), mesh_load_use_key_mouse_control->GetMesh()->vertex_data_, GL_STATIC_DRAW);

    //��GPU�ϴ�������������
    glGenBuffers(1, &kEBO_use_key_mouse_control);
    //������������ָ��Ϊ������������������
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, kEBO_use_key_mouse_control);
    //�ϴ������������ݵ�����������
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, mesh_load_use_key_mouse_control->GetMesh()->vertex_index_num_ * sizeof(unsigned short), mesh_load_use_key_mouse_control->GetMesh()->vertex_index_data_, GL_STATIC_DRAW);
    //����VAO
    glBindVertexArray(kVAO_use_key_mouse_control);
    {
        //ָ����ǰʹ�õ�VBO
        glBindBuffer(GL_ARRAY_BUFFER, kVBO_use_key_mouse_control);
        //��Shader����(a_pos)�Ͷ�������VBO������й���������0��ʾ����ƫ������
        glVertexAttribPointer(vpos_location_use_key_mouse_control, 3, GL_FLOAT, false, sizeof(Vertex), 0);
        //���ö���Shader����(a_color)��ָ���붥����ɫ���ݽ��й�����
        glVertexAttribPointer(vcol_location_use_key_mouse_control, 4, GL_FLOAT, false, sizeof(Vertex), (void*)(sizeof(float) * 3));
        //��Shader����(a_uv)�Ͷ���UV����VBO������й�����
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


/// ���̻ص�
/// \param window
/// \param key
/// \param scancode
/// \param action
/// \param mods
static void key_callback_use_key_mouse_control(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    Input::RecordKey(key, action);
}
/// ��갴���ص�
/// \param window
/// \param button
/// \param action
/// \param mods
void mouse_button_callback_use_key_mouse_control(GLFWwindow* window, int button, int action, int mods)
{
    Input::RecordKey(button, action);
    std::cout << "mouse_button_callback:" << button << "," << action << std::endl;
}
/// ����ƶ��ص�
/// \param window
/// \param x
/// \param y
void mouse_move_callback_use_key_mouse_control(GLFWwindow* window, double x, double y)
{
    Input::set_mousePosition(x, y);
    std::cout << "mouse_move_callback:" << x << "," << y << std::endl;
}
/// �����ֻص�
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
    //���ô���ص�
    glfwSetErrorCallback(error_callback_use_key_mouse_control);
    /* ��ʼ��glfw */
    if (!glfwInit())
        exit(EXIT_FAILURE);

    //ָ��opengl�汾��
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
    //��������
    window_use_key_mouse_control = glfwCreateWindow(960, 640, "Simple example", NULL, NULL);
    if (!window_use_key_mouse_control)
    {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glfwMakeContextCurrent(window_use_key_mouse_control);
    // ����OpenGL ָ��   
    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
    //���������ʾ����������֮ǰ�ȴ���֡����ͨ����Ϊvsync��
   //Ĭ������£��������Ϊ0������Ϊ��Ļÿ��ֻ����60-75�Σ����Դ󲿷ֵĻ��治�ᱻ��ʾ��
   //���ң��������п�������Ļ���µ��м佻����������Ļ˺�ѵ������
   //���ԣ����Խ��ü����Ϊ1����ÿ֡����һ�Ρ�����������Ϊ���ߵ�ֵ��������ܵ��������ӳ١�
    glfwSwapInterval(1);

    glfwSetKeyCallback(window_use_key_mouse_control, key_callback_use_key_mouse_control);
    glfwSetMouseButtonCallback(window_use_key_mouse_control, mouse_button_callback_use_key_mouse_control);
    glfwSetScrollCallback(window_use_key_mouse_control, mouse_scroll_callback_use_key_mouse_control);
    glfwSetCursorPosCallback(window_use_key_mouse_control, mouse_move_callback_use_key_mouse_control);

}
//
///// ���롢����Shader  
//void compile_shader_use_key_mouse_control()
//{
//    Shader * shader = new Shader();
//    shader->Find("resources/shader/Unlit");
//    program_use_key_mouse_control = shader->GetProgramId();
//}


//����Texture
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

    //��һ֡�����λ��
    glm::vec2 last_frame_mouse_position = Input::mousePosition();
    while (!glfwWindowShouldClose(window_use_key_mouse_control))
    {
        float ratio;
        int width, height;

        glfwGetFramebufferSize(window_use_key_mouse_control, &width, &height);
        glViewport(0, 0, width, height);
        ratio = width / (float)height;
        //glm::mat4 trans = glm::translate(glm::vec3(0, 0, 0)); //���ƶ���������;
        camera->SetView(glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
        camera->SetProjection(60, ratio, 1.1f, 1000.0f);
        camera->Clear();

        //��ת����
        if (Input::GetKeyDown(KEY_CODE_R)) {
            static float rotate_eulerAngle = 0.f;
            rotate_eulerAngle += 0.1f;
            glm::vec3 rotation = transform->rotation();
            rotation.y = rotate_eulerAngle;
            transform->set_rotation(rotation);
        }

        //��ת���
        if (Input::GetKeyDown(KEY_CODE_LEFT_ALT) && Input::GetMouseButtonDown(MOUSE_BUTTON_LEFT)) {
            float degrees = Input::mousePosition().x - last_frame_mouse_position.x;

            glm::mat4 old_mat4 = glm::mat4(1.0f);
            std::cout << glm::to_string(old_mat4) << std::endl;

            glm::mat4 rotate_mat4 = glm::rotate(old_mat4, glm::radians(degrees), glm::vec3(0.0f, 1.0f, 0.0f));//�������������ϵλ�ã�����������ת�ľ�����������㣬����ֱ���÷���
            glm::vec4 old_pos = glm::vec4(cameraTransform->position(), 1.0f);
            glm::vec4 new_pos = rotate_mat4 * old_pos;//��ת���� * ԭ�������� = ������������ת��
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