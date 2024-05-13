#include <iostream>
#include <glad/glad.h>
#define GLM_ENABLE_EXPERIMENTAL
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtx/transform2.hpp>
#include<glm/gtx/euler_angles.hpp>

#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include "../common/render/textures/Texture2D.h"
#include "../common/render/mesh/MeshRenderer.h"
#include "../common/component/GameObject.h"
#include "../common/component/Transform.h"
#include "../common/render/camera/Camera.h"
#include "../common/render/font/Font.h"
#include <rttr/type>
#include <rttr/registration>
using namespace std;


using namespace std;

//����

//ԭʼ��������
static const Vertex kVertexs_use_font[36] = {
    //Front
    glm::vec3(-1.0f, -1.0f, 1.0f), glm::vec4(1.0f,1.0f,1.0f,1.0f),   glm::vec2(0.0f, 0.0f),
    glm::vec3(1.0f, -1.0f, 1.0f), glm::vec4(1.0f,1.0f,1.0f,1.0f),   glm::vec2(1.0f, 0.0f),
    glm::vec3(1.0f,  1.0f, 1.0f), glm::vec4(1.0f,1.0f,1.0f,1.0f),   glm::vec2(1.0f, 1.0f),

    glm::vec3(-1.0f, -1.0f, 1.0f), glm::vec4(1.0f,1.0f,1.0f,1.0f),   glm::vec2(0.0f, 0.0f),
    glm::vec3(1.0f,  1.0f, 1.0f), glm::vec4(1.0f,1.0f,1.0f,1.0f),   glm::vec2(1.0f, 1.0f),
    glm::vec3(-1.0f,  1.0f, 1.0f), glm::vec4(1.0f,1.0f,1.0f,1.0f),   glm::vec2(0.0f, 1.0f),

    //back
    glm::vec3(1.0f,  1.0f, -1.0f), glm::vec4(1.0f,1.0f,1.0f,1.0f),   glm::vec2(0.0f, 1.0f),
    glm::vec3(1.0f, -1.0f, -1.0f), glm::vec4(1.0f,1.0f,1.0f,1.0f),   glm::vec2(0.0f, 0.0f),
    glm::vec3(-1.0f, -1.0f, -1.0f), glm::vec4(1.0f,1.0f,1.0f,1.0f),   glm::vec2(1.0f, 0.0f),

    glm::vec3(1.0f,  1.0f, -1.0f), glm::vec4(1.0f,1.0f,1.0f,1.0f),   glm::vec2(0.0f, 1.0f),
    glm::vec3(-1.0f, -1.0f, -1.0f), glm::vec4(1.0f,1.0f,1.0f,1.0f),   glm::vec2(1.0f, 0.0f),
    glm::vec3(-1.0f,  1.0f, -1.0f), glm::vec4(1.0f,1.0f,1.0f,1.0f),   glm::vec2(1.0f, 1.0f),


    //left
    glm::vec3(-1.0f, 1.0f, 1.0f), glm::vec4(1.0f,1.0f,1.0f,1.0f),   glm::vec2(1.0f, 1.0f),
    glm::vec3(-1.0f, -1.0f, -1.0f), glm::vec4(1.0f,1.0f,1.0f,1.0f),   glm::vec2(0.0f, 0.0f),
    glm::vec3(-1.0f, -1.0f, 1.0f), glm::vec4(1.0f,1.0f,1.0f,1.0f),   glm::vec2(1.0f, 0.0f),

    glm::vec3(-1.0f, 1.0f, -1.0f), glm::vec4(1.0f,1.0f,1.0f,1.0f),   glm::vec2(0.0f, 1.0f),
    glm::vec3(-1.0f, -1.0f, -1.0f), glm::vec4(1.0f,1.0f,1.0f,1.0f),   glm::vec2(0.0f, 0.0f),
    glm::vec3(-1.0f, 1.0f, 1.0f), glm::vec4(1.0f,1.0f,1.0f,1.0f),   glm::vec2(1.0f, 1.0f),

    //right
    glm::vec3(1.0f, -1.0f, 1.0f), glm::vec4(1.0f,1.0f,1.0f,1.0f),   glm::vec2(0.0f, 0.0f),
    glm::vec3(1.0f, -1.0f, -1.0f), glm::vec4(1.0f,1.0f,1.0f,1.0f),   glm::vec2(1.0f, 0.0f),
    glm::vec3(1.0f, 1.0f, -1.0f), glm::vec4(1.0f,1.0f,1.0f,1.0f),   glm::vec2(1.0f, 1.0f),

    glm::vec3(1.0f, -1.0f, 1.0f), glm::vec4(1.0f,1.0f,1.0f,1.0f),   glm::vec2(0.0f, 0.0f),
    glm::vec3(1.0f, 1.0f, -1.0f), glm::vec4(1.0f,1.0f,1.0f,1.0f),   glm::vec2(1.0f, 1.0f),
    glm::vec3(1.0f, 1.0f, 1.0f), glm::vec4(1.0f,1.0f,1.0f,1.0f),   glm::vec2(0.0f, 1.0f),

    //up
    glm::vec3(-1.0f, 1.0f, 1.0f), glm::vec4(1.0f,1.0f,1.0f,1.0f),   glm::vec2(0.0f, 0.0f),
    glm::vec3(1.0f, 1.0f, 1.0f), glm::vec4(1.0f,1.0f,1.0f,1.0f),   glm::vec2(1.0f, 0.0f),
    glm::vec3(1.0f, 1.0f, -1.0f), glm::vec4(1.0f,1.0f,1.0f,1.0f),   glm::vec2(1.0f, 1.0f),

    glm::vec3(-1.0f, 1.0f, 1.0f), glm::vec4(1.0f,1.0f,1.0f,1.0f),   glm::vec2(0.0f, 0.0f),
    glm::vec3(1.0f, 1.0f, -1.0f), glm::vec4(1.0f,1.0f,1.0f,1.0f),   glm::vec2(1.0f, 1.0f),
    glm::vec3(-1.0f, 1.0f, -1.0f), glm::vec4(1.0f,1.0f,1.0f,1.0f),   glm::vec2(0.0f, 1.0f),

    //down
    glm::vec3(-1.0f, -1.0f, -1.0f), glm::vec4(1.0f,1.0f,1.0f,1.0f),   glm::vec2(0.0f, 0.0f),
    glm::vec3(1.0f, -1.0f, -1.0f), glm::vec4(1.0f,1.0f,1.0f,1.0f),   glm::vec2(1.0f, 0.0f),
    glm::vec3(1.0f, -1.0f, 1.0f), glm::vec4(1.0f,1.0f,1.0f,1.0f),   glm::vec2(1.0f, 1.0f),

    glm::vec3(-1.0f, -1.0f, -1.0f), glm::vec4(1.0f,1.0f,1.0f,1.0f),   glm::vec2(0.0f, 0.0f),
    glm::vec3(1.0f, -1.0f, 1.0f), glm::vec4(1.0f,1.0f,1.0f,1.0f),   glm::vec2(1.0f, 1.0f),
    glm::vec3(-1.0f, -1.0f, 1.0f), glm::vec4(1.0f,1.0f,1.0f,1.0f),   glm::vec2(0.0f, 1.0f),
};

static const glm::vec3 kPositions_use_font[36] = {
    //Front
    glm::vec3(-1.0f, -1.0f, 1.0f),
    glm::vec3(1.0f, -1.0f, 1.0f),
    glm::vec3(1.0f, 1.0f, 1.0f),
    glm::vec3(-1.0f, -1.0f, 1.0f),
    glm::vec3(1.0f, 1.0f, 1.0f),
    glm::vec3(-1.0f, 1.0f, 1.0f),
    //back
    glm::vec3(1.0f, -1.0f, -1.0f),
    glm::vec3(-1.0f, -1.0f, -1.0f),
    glm::vec3(-1.0f, 1.0f, -1.0f),
    glm::vec3(1.0f, -1.0f, -1.0f),
    glm::vec3(-1.0f, 1.0f, -1.0f),
    glm::vec3(1.0f, 1.0f, -1.0f),
    //left
    glm::vec3(-1.0f, -1.0f, -1.0f),
    glm::vec3(-1.0f, -1.0f, 1.0f),
    glm::vec3(-1.0f, 1.0f, 1.0f),
    glm::vec3(-1.0f, -1.0f, -1.0f),
    glm::vec3(-1.0f, 1.0f, 1.0f),
    glm::vec3(-1.0f, 1.0f, -1.0f),
    //right
    glm::vec3(1.0f, -1.0f, 1.0f),
    glm::vec3(1.0f, -1.0f, -1.0f),
    glm::vec3(1.0f, 1.0f, -1.0f),
    glm::vec3(1.0f, -1.0f, 1.0f),
    glm::vec3(1.0f, 1.0f, -1.0f),
    glm::vec3(1.0f, 1.0f, 1.0f),
    //up
    glm::vec3(-1.0f, 1.0f, 1.0f),
    glm::vec3(1.0f, 1.0f, 1.0f),
    glm::vec3(1.0f, 1.0f, -1.0f),
    glm::vec3(-1.0f, 1.0f, 1.0f),
    glm::vec3(1.0f, 1.0f, -1.0f),
    glm::vec3(-1.0f, 1.0f, -1.0f),
    //down
    glm::vec3(-1.0f, -1.0f, -1.0f),
    glm::vec3(1.0f, -1.0f, -1.0f),
    glm::vec3(1.0f, -1.0f, 1.0f),
    glm::vec3(-1.0f, -1.0f, -1.0f),
    glm::vec3(1.0f, -1.0f, 1.0f),
    glm::vec3(-1.0f, -1.0f, 1.0f),
};

static const glm::vec4 kColors_use_font[36] = {
    //Front
          glm::vec4(1, 0, 0, 1),
          glm::vec4(1, 0, 0, 1),
          glm::vec4(1, 0, 0, 1),

          glm::vec4(1, 0, 0, 1),
          glm::vec4(1, 0, 0, 1),
          glm::vec4(1, 0, 0, 1),

          //back
          glm::vec4(1, 0, 0, 1),
          glm::vec4(1, 0, 0, 1),
          glm::vec4(1, 0, 0, 1),

          glm::vec4(1, 0, 0, 1),
          glm::vec4(1, 0, 0, 1),
          glm::vec4(1, 0, 0, 1),

          //left
          glm::vec4(0, 1, 0, 1),
          glm::vec4(0, 1, 0, 1),
          glm::vec4(0, 1, 0, 1),

          glm::vec4(0, 1, 0, 1),
          glm::vec4(0, 1, 0, 1),
          glm::vec4(0, 1, 0, 1),

          //right
          glm::vec4(0, 1, 0, 1),
          glm::vec4(0, 1, 0, 1),
          glm::vec4(0, 1, 0, 1),

          glm::vec4(0, 1, 0, 1),
          glm::vec4(0, 1, 0, 1),
          glm::vec4(0, 1, 0, 1),

          //up
          glm::vec4(0, 0, 1, 1),
          glm::vec4(0, 0, 1, 1),
          glm::vec4(0, 0, 1, 1),

          glm::vec4(0, 0, 1, 1),
          glm::vec4(0, 0, 1, 1),
          glm::vec4(0, 0, 1, 1),

          //down
          glm::vec4(0, 0, 1, 1),
          glm::vec4(0, 0, 1, 1),
          glm::vec4(0, 0, 1, 1),

          glm::vec4(0, 0, 1, 1),
          glm::vec4(0, 0, 1, 1),
          glm::vec4(0, 0, 1, 1),
};

static const glm::vec2 kUvs_use_font[36] =
{
    //Front
    glm::vec2(0.0f, 0.0f),
    glm::vec2(1.0f, 0.0f),
    glm::vec2(1.0f, 1.0f),

    glm::vec2(0.0f, 0.0f),
    glm::vec2(1.0f, 1.0f),
    glm::vec2(0.0f, 1.0f),

    //back
    glm::vec2(0.0f, 0.0f),
    glm::vec2(1.0f, 0.0f),
    glm::vec2(1.0f, 1.0f),

    glm::vec2(0.0f, 0.0f),
    glm::vec2(1.0f, 1.0f),
    glm::vec2(0.0f, 1.0f),

    //left
    glm::vec2(0.0f, 0.0f),
    glm::vec2(1.0f, 0.0f),
    glm::vec2(1.0f, 1.0f),

    glm::vec2(0.0f, 0.0f),
    glm::vec2(1.0f, 1.0f),
    glm::vec2(0.0f, 1.0f),

    //right
    glm::vec2(0.0f, 0.0f),
    glm::vec2(1.0f, 0.0f),
    glm::vec2(1.0f, 1.0f),

    glm::vec2(0.0f, 0.0f),
    glm::vec2(1.0f, 1.0f),
    glm::vec2(0.0f, 1.0f),

    //up
    glm::vec2(0.0f, 0.0f),
    glm::vec2(1.0f, 0.0f),
    glm::vec2(1.0f, 1.0f),

    glm::vec2(0.0f, 0.0f),
    glm::vec2(1.0f, 1.0f),
    glm::vec2(0.0f, 1.0f),

    //down
    glm::vec2(0.0f, 0.0f),
    glm::vec2(1.0f, 0.0f),
    glm::vec2(1.0f, 1.0f),

    glm::vec2(0.0f, 0.0f),
    glm::vec2(1.0f, 1.0f),
    glm::vec2(0.0f, 1.0f),
};

GLFWwindow* window_use_font;
GLint mvp_location_use_font, vpos_location_use_font, vcol_location_use_font, u_diffuse_texture_location_use_font, a_uv_location_use_font;
GLuint kVBO_use_font, kEBO_use_font, kVAO_use_font;
Texture2D* texture2d_use_font = nullptr;
MeshFilter* mesh_load_use_font = nullptr;
//ȥ�صĶ���Vector
static vector<Vertex> kVertexRemoveDumplicateVectorv_use_font;
//��������Vector
static vector<unsigned short> kVertexIndexVector_use_font;

//����ȥ��
static void VertexRemoveDumplicate_use_font() {
    for (int i = 0; i < 36; ++i) {
        const Vertex& vertex = kVertexs_use_font[i];
        //�ж϶����Ƿ����
        int index = -1;
        for (int j = 0; j < kVertexRemoveDumplicateVectorv_use_font.size(); ++j) {
            if (vertex.pos_ == kVertexRemoveDumplicateVectorv_use_font[j].pos_ && vertex.color_ == kVertexRemoveDumplicateVectorv_use_font[j].color_ && vertex.uv_ == kVertexRemoveDumplicateVectorv_use_font[j].uv_) {
                index = j;
                break;
            }
        }
        if (index < 0) {
            //û�ҵ��ͽ�Ŀ�궥�����kVertexRemoveDumplicateVector������¼����ΪkVertexRemoveDumplicateVector.size()��
            kVertexRemoveDumplicateVectorv_use_font.push_back(vertex);
            kVertexIndexVector_use_font.push_back(kVertexRemoveDumplicateVectorv_use_font.size() - 1);
        }
        else {
            //�ҵ���Ŀ�궥�㣬��¼����ΪkVertexRemoveDumplicateVector��λ�á�
            kVertexIndexVector_use_font.push_back(index);
        }
    }
}
/// ����VAO
void GeneratorVertexArrayObject_use_font() {
    glGenVertexArrays(1, &kVAO_use_font);
}


//����VBO��EBO
void GeneratorBufferObject_use_font()
{
    //��GPU�ϴ�������������
    glGenBuffers(1, &kVBO_use_font);
    //������������ָ��Ϊ���㻺��������
    glBindBuffer(GL_ARRAY_BUFFER, kVBO_use_font);
    //�ϴ��������ݵ�����������
    glBufferData(GL_ARRAY_BUFFER, mesh_load_use_font->GetMesh()->vertex_num_ * sizeof(Vertex), mesh_load_use_font->GetMesh()->vertex_data_, GL_STATIC_DRAW);

    //��GPU�ϴ�������������
    glGenBuffers(1, &kEBO_use_font);
    //������������ָ��Ϊ������������������
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, kEBO_use_font);
    //�ϴ������������ݵ�����������
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, mesh_load_use_font->GetMesh()->vertex_index_num_ * sizeof(unsigned short), mesh_load_use_font->GetMesh()->vertex_index_data_, GL_STATIC_DRAW);
    //����VAO
    glBindVertexArray(kVAO_use_font);
    {
        //ָ����ǰʹ�õ�VBO
        glBindBuffer(GL_ARRAY_BUFFER, kVBO_use_font);
        //��Shader����(a_pos)�Ͷ�������VBO������й���������0��ʾ����ƫ������
        glVertexAttribPointer(vpos_location_use_font, 3, GL_FLOAT, false, sizeof(Vertex), 0);
        //���ö���Shader����(a_color)��ָ���붥����ɫ���ݽ��й�����
        glVertexAttribPointer(vcol_location_use_font, 4, GL_FLOAT, false, sizeof(Vertex), (void*)(sizeof(float) * 3));
        //��Shader����(a_uv)�Ͷ���UV����VBO������й�����
        glVertexAttribPointer(a_uv_location_use_font, 2, GL_FLOAT, false, sizeof(Vertex), (void*)(sizeof(float) * (3 + 4)));

        glEnableVertexAttribArray(vpos_location_use_font);
        glEnableVertexAttribArray(vcol_location_use_font);
        glEnableVertexAttribArray(a_uv_location_use_font);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, kEBO_use_font);
    }
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

static void error_callback_use_font(int error, const char* description)
{
    fprintf(stderr, "Error: %s\n", description);
}



void init_opengl_use_font()
{
    //���ô���ص�
    glfwSetErrorCallback(error_callback_use_font);
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
    window_use_font = glfwCreateWindow(960, 640, "Simple example", NULL, NULL);
    if (!window_use_font)
    {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glfwMakeContextCurrent(window_use_font);
    // ����OpenGL ָ��   
    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
    //���������ʾ����������֮ǰ�ȴ���֡����ͨ����Ϊvsync��
   //Ĭ������£��������Ϊ0������Ϊ��Ļÿ��ֻ����60-75�Σ����Դ󲿷ֵĻ��治�ᱻ��ʾ��
   //���ң��������п�������Ļ���µ��м佻����������Ļ˺�ѵ������
   //���ԣ����Խ��ü����Ϊ1����ÿ֡����һ�Ρ�����������Ϊ���ߵ�ֵ��������ܵ��������ӳ١�
    glfwSwapInterval(1);

}
//
///// ���롢����Shader  
//void compile_shader_use_font()
//{
//    Shader * shader = new Shader();
//    shader->Find("resources/shader/Unlit");
//    program_use_font = shader->GetProgramId();
//}




//����Texture
void CreateTexturem_use_font(std::string image_file_path)
{
    texture2d_use_font = Texture2D::LoadFromFileTpc(image_file_path);
}

std::vector<MeshRenderer *> CreateFont_use_font()
{
    //����������ͼ
    std::vector<MeshRenderer*> vec;
    Font* font = Font::LoadFromFile("resources/font/SOURCEHANSANSCN-HEAVY.OTF", 20);
    std::string str = "Captain";
    std::vector<Font::Character*> character_vec=font->LoadStr(str);
    for (auto character : character_vec)
    {
        int offset_x = 0;
        offset_x += 2;
        //��ΪFreeType���ɵ�bitmap�����µߵ��ģ���������UV����ҲҪ����Ӧ��ת�������Ͻ���Ϊ��㡣
        vector<Vertex> vertex_vector = {
                {{-1.0f + offset_x, 2.0f, 1.0f}, {1.0f,0.0f,0.0f,1.0f},   {character->left_top_x_, character->right_bottom_y_}},
                {{ 1.0f + offset_x, 2.0f, 1.0f}, {1.0f,0.0f,0.0f,1.0f},   {character->right_bottom_x_, character->right_bottom_y_}},
                {{ 1.0f + offset_x,  4.0f, 1.0f}, {0.0f,1.0f,0.0f,1.0f},   {character->right_bottom_x_, character->left_top_y_}},
                {{-1.0f + offset_x,  4.0f, 1.0f}, {0.0f,1.0f,0.0f,1.0f},   {character->left_top_x_, character->left_top_y_}}
        };
        vector<unsigned short> index_vector = {
                0,1,2,
                0,2,3
        };
        //����ģ�� GameObject
        auto go = new GameObject("SOURCEHANSANSCN-HEAVY");
        go->set_layer(0x01);
        //���� Transform ���
        auto transform = dynamic_cast<Transform*>(go->AddComponent("Transform"));
        transform->set_position({ 2.f,0.f,0.f });
        //���� MeshFilter ���
        auto mesh_filter = dynamic_cast<MeshFilter*>(go->AddComponent("MeshFilter"));
        mesh_filter->CreateMesh(vertex_vector, index_vector);
        //���� Material
        auto material = new Material();//���ò���
        material->Parse("resources/material/font.mat");
        //���� MeshRenderer ���
        auto mesh_renderer = dynamic_cast<MeshRenderer*>(go->AddComponent("MeshRenderer"));
        mesh_renderer->SetMaterial(material);
        mesh_renderer->SetMeshFilter(mesh_filter);

        //ʹ��������ͼ
        material->SetTexture("u_diffuse_texture", font->font_texture());

        vec.push_back(mesh_renderer);
    }


  
    return vec;
}

int draw_use_font(void)
{

   
    init_opengl_use_font();

    GameObject* obj = new GameObject("test");


    Transform* transform = dynamic_cast<Transform*>(obj->AddComponent("Transform"));

    Material* material = new Material();
    material->Parse("resources/material/cube.mat");

    mesh_load_use_font = new MeshFilter();
    mesh_load_use_font->LoadMesh("resources/mesh/cube.mesh");


    MeshRenderer* meshRender = dynamic_cast<MeshRenderer*>(obj->AddComponent("MeshRenderer"));
    meshRender->SetMaterial(material);
    meshRender->SetMeshFilter(mesh_load_use_font);


    GameObject* camera_obj = new GameObject("Main_Camera");
    Transform* cameraTransform = dynamic_cast<Transform*>(camera_obj->AddComponent("Transform"));
    cameraTransform->set_position(glm::vec3(0, 0, 10));
    Camera* camera = dynamic_cast<Camera*>(camera_obj->AddComponent("Camera"));


    auto font_vec = CreateFont_use_font();
    while (!glfwWindowShouldClose(window_use_font))
    {
        float ratio;
        int width, height;

        glfwGetFramebufferSize(window_use_font, &width, &height);
        glViewport(0, 0, width, height);
        ratio = width / (float)height;
        //glm::mat4 trans = glm::translate(glm::vec3(0, 0, 0)); //���ƶ���������;
        camera->SetView(glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
        camera->SetProjection(60, ratio, 1.1f, 1000.0f);
        camera->Clear();

        static float rotate_eulerAngle = 0.f;
        rotate_eulerAngle += 0.1f;
        glm::vec3 rotation = transform->rotation();
        rotation.y = rotate_eulerAngle;
        transform->set_rotation(rotation);


        meshRender->SetView(camera->view_mat4());
        meshRender->SetProjection(camera->projection_mat4());
        meshRender->TestRender();

        for (auto font : font_vec)
        {
            font->SetView(camera->view_mat4());
            font->SetProjection(camera->projection_mat4());
            font->TestRender();
        }



        glfwSwapBuffers(window_use_font);
        glfwPollEvents();
    }

    glfwDestroyWindow(window_use_font);

    glfwTerminate();
    exit(EXIT_SUCCESS);
}