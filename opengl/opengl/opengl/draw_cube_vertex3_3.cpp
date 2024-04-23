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
#include "Texture2D.h"


using namespace std;


#ifndef UNTITLED_SHADERSOURCE_H
#define UNTITLED_SHADERSOURCE_H

//顶点着色器代码
static const char* vertex_shader_text_cube_vertex3_3 =
"#version 330 core\n"

"uniform mat4 u_mvp;\n"

"layout(location = 0) in  vec3 a_pos;\n"
"layout(location = 1) in  vec4 a_color;\n"
"layout(location = 2) in  vec2 a_uv;\n"

"out vec4 v_color;\n"
"out vec2 v_uv;\n"

"void main()\n"
"{\n"
"    gl_Position = u_mvp * vec4(a_pos, 1.0);\n"
"    v_color = a_color;\n"
"    v_uv = a_uv;\n"
"}\n";
//片段着色器代码
static const char* fragment_shader_text_cube_vertex3_3 =
"#version 330 core\n"
"uniform sampler2D u_diffuse_texture;"
"in vec4 v_color;\n"
"in vec2 v_uv;\n"
"layout(location = 0) out vec4 o_fragColor;\n"
"void main()\n"
"{\n"
"    o_fragColor = texture(u_diffuse_texture,v_uv) * v_color;\n"
"}\n";

#endif //UNTITLED_SHADERSOURCE_H

using namespace std;

//顶点
struct  Vertex_cube_vertex3_3
{
    glm::vec3 pos_;
    glm::vec4 color_;
    glm::vec2 uv_;
};

//原始顶点数组
static const Vertex_cube_vertex3_3 kVertexs_cube_vertex3_3[36] = {
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

static const glm::vec3 kPositions_cube_vertex3_3[36] = {
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

static const glm::vec4 kColors_cube_vertex3_3[36] = {
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

static const glm::vec2 kUvs_cube_vertex3_3[36] =
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

GLFWwindow* window_cube_vertex3_3;
GLuint vertex_shader_cube_vertex3_3, fragment_shader_cube_vertex3_3, program_cube_vertex3_3;
GLint mvp_location_cube_vertex3_3, vpos_location_cube_vertex3_3, vcol_location_cube_vertex3_3, u_diffuse_texture_location_cube_vertex3_3, a_uv_location_cube_vertex3_3;
GLuint kVBO_cube_vertex3_3, kEBO_cube_vertex3_3, kVAO_cube_vertex3_3;
Texture2D* texture2d_cube_vertex3_3 = nullptr;
//去重的顶点Vector
static vector<Vertex_cube_vertex3_3> kVertexRemoveDumplicateVectorv_cube_vertex3_3;
//顶点索引Vector
static vector<unsigned short> kVertexIndexVector_cube_vertex3_3;

//顶点去重
static void VertexRemoveDumplicate_cube_vertex3_3() {
    for (int i = 0; i < 36; ++i) {
        const Vertex_cube_vertex3_3& vertex = kVertexs_cube_vertex3_3[i];
        //判断顶点是否存在
        int index = -1;
        for (int j = 0; j < kVertexRemoveDumplicateVectorv_cube_vertex3_3.size(); ++j) {
            if (vertex.pos_ == kVertexRemoveDumplicateVectorv_cube_vertex3_3[j].pos_ && vertex.color_ == kVertexRemoveDumplicateVectorv_cube_vertex3_3[j].color_ && vertex.uv_ == kVertexRemoveDumplicateVectorv_cube_vertex3_3[j].uv_) {
                index = j;
                break;
            }
        }
        if (index < 0) {
            //没找到就将目标顶点加入kVertexRemoveDumplicateVector，并记录索引为kVertexRemoveDumplicateVector.size()。
            kVertexRemoveDumplicateVectorv_cube_vertex3_3.push_back(vertex);
            kVertexIndexVector_cube_vertex3_3.push_back(kVertexRemoveDumplicateVectorv_cube_vertex3_3.size() - 1);
        }
        else {
            //找到了目标顶点，记录索引为kVertexRemoveDumplicateVector的位置。
            kVertexIndexVector_cube_vertex3_3.push_back(index);
        }
    }
}
/// 创建VAO
void GeneratorVertexArrayObject_cube_vertex3_3() {
    glGenVertexArrays(1, &kVAO_cube_vertex3_3);
}


//创建VBO和EBO
void GeneratorBufferObject_cube_vertex3_3()
{
    //在GPU上创建缓冲区对象
    glGenBuffers(1, &kVBO_cube_vertex3_3);
    //将缓冲区对象指定为顶点缓冲区对象
    glBindBuffer(GL_ARRAY_BUFFER, kVBO_cube_vertex3_3);
    //上传顶点数据到缓冲区对象
    glBufferData(GL_ARRAY_BUFFER, kVertexRemoveDumplicateVectorv_cube_vertex3_3.size() * sizeof(Vertex_cube_vertex3_3), &kVertexRemoveDumplicateVectorv_cube_vertex3_3[0], GL_STATIC_DRAW);

    //在GPU上创建缓冲区对象
    glGenBuffers(1, &kEBO_cube_vertex3_3);
    //将缓冲区对象指定为顶点索引缓冲区对象
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, kEBO_cube_vertex3_3);
    //上传顶点索引数据到缓冲区对象
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, kVertexIndexVector_cube_vertex3_3.size() * sizeof(unsigned short), &kVertexIndexVector_cube_vertex3_3[0], GL_STATIC_DRAW);
    //设置VAO
    glBindVertexArray(kVAO_cube_vertex3_3);
    {
        //指定当前使用的VBO
        glBindBuffer(GL_ARRAY_BUFFER, kVBO_cube_vertex3_3);
        //将Shader变量(a_pos)和顶点坐标VBO句柄进行关联，最后的0表示数据偏移量。
        glVertexAttribPointer(vpos_location_cube_vertex3_3, 3, GL_FLOAT, false, sizeof(Vertex_cube_vertex3_3), 0);
        //启用顶点Shader属性(a_color)，指定与顶点颜色数据进行关联。
        glVertexAttribPointer(vcol_location_cube_vertex3_3, 4, GL_FLOAT, false, sizeof(Vertex_cube_vertex3_3), (void*)(sizeof(float) * 3));
        //将Shader变量(a_uv)和顶点UV坐标VBO句柄进行关联。
        glVertexAttribPointer(a_uv_location_cube_vertex3_3, 2, GL_FLOAT, false, sizeof(Vertex_cube_vertex3_3), (void*)(sizeof(float) * (3 + 4)));

        glEnableVertexAttribArray(vpos_location_cube_vertex3_3);
        glEnableVertexAttribArray(vcol_location_cube_vertex3_3);
        glEnableVertexAttribArray(a_uv_location_cube_vertex3_3);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, kEBO_cube_vertex3_3);
    }
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

static void error_callback_cube_vertex3_3(int error, const char* description)
{
    fprintf(stderr, "Error: %s\n", description);
}



void init_opengl_cube_vertex3_3()
{
    //设置错误回调
    glfwSetErrorCallback(error_callback_cube_vertex3_3);
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
    window_cube_vertex3_3 = glfwCreateWindow(960, 640, "Simple example", NULL, NULL);
    if (!window_cube_vertex3_3)
    {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glfwMakeContextCurrent(window_cube_vertex3_3);
    // 加载OpenGL 指针   
    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
    //交换间隔表示交换缓冲区之前等待的帧数，通常称为vsync。
   //默认情况下，交换间隔为0，但因为屏幕每秒只更新60-75次，所以大部分的画面不会被显示。
   //而且，缓冲区有可能在屏幕更新的中间交换，出现屏幕撕裂的情况。
   //所以，可以将该间隔设为1，即每帧更新一次。它可以设置为更高的值，但这可能导致输入延迟。
    glfwSwapInterval(1);

}

/// 编译、链接Shader  
void compile_shader_cube_vertex3_3()
{
    //创建顶点Shader
    vertex_shader_cube_vertex3_3 = glCreateShader(GL_VERTEX_SHADER);
    //指定Shader源码
    glShaderSource(vertex_shader_cube_vertex3_3, 1, &vertex_shader_text_cube_vertex3_3, NULL);
    //编译Shader
    glCompileShader(vertex_shader_cube_vertex3_3);
    //获取编译结果
    GLint compile_status = GL_FALSE;
    glGetShaderiv(vertex_shader_cube_vertex3_3, GL_COMPILE_STATUS, &compile_status);
    if (compile_status == GL_FALSE)
    {
        GLchar message[256];
        glGetShaderInfoLog(vertex_shader_cube_vertex3_3, sizeof(message), 0, message);
        cout << "compile vs error:" << message << endl;
    }

    //创建片段Shader
    fragment_shader_cube_vertex3_3 = glCreateShader(GL_FRAGMENT_SHADER);
    //指定Shader源码
    glShaderSource(fragment_shader_cube_vertex3_3, 1, &fragment_shader_text_cube_vertex3_3, NULL);
    //编译Shader
    glCompileShader(fragment_shader_cube_vertex3_3);
    //获取编译结果
    compile_status = GL_FALSE;
    glGetShaderiv(fragment_shader_cube_vertex3_3, GL_COMPILE_STATUS, &compile_status);
    if (compile_status == GL_FALSE)
    {
        GLchar message[256];
        glGetShaderInfoLog(fragment_shader_cube_vertex3_3, sizeof(message), 0, message);
        cout << "compile fs error:" << message << endl;
    }


    //创建GPU程序
    program_cube_vertex3_3 = glCreateProgram();
    //附加Shader
    glAttachShader(program_cube_vertex3_3, vertex_shader_cube_vertex3_3);
    glAttachShader(program_cube_vertex3_3, fragment_shader_cube_vertex3_3);
    //Link
    glLinkProgram(program_cube_vertex3_3);
    //获取编译结果
    GLint link_status = GL_FALSE;
    glGetProgramiv(program_cube_vertex3_3, GL_LINK_STATUS, &link_status);
    if (link_status == GL_FALSE)
    {
        GLchar message[256];
        glGetProgramInfoLog(program_cube_vertex3_3, sizeof(message), 0, message);
        cout << "link error:" << message << endl;
    }
}


//创建Texture
void CreateTexturem_cube_vertex3_3(std::string image_file_path)
{
    texture2d_cube_vertex3_3 = Texture2D::LoadFromFile(image_file_path);
}


int draw_cube_vertex3_3(void)
{
    VertexRemoveDumplicate_cube_vertex3_3();
    init_opengl_cube_vertex3_3();
    CreateTexturem_cube_vertex3_3("1.png");
    GeneratorVertexArrayObject_cube_vertex3_3();
    GeneratorBufferObject_cube_vertex3_3();
    compile_shader_cube_vertex3_3();

    //获取shader属性ID
    mvp_location_cube_vertex3_3 = glGetUniformLocation(program_cube_vertex3_3, "u_mvp");
    vpos_location_cube_vertex3_3 = glGetAttribLocation(program_cube_vertex3_3, "a_pos");
    vcol_location_cube_vertex3_3 = glGetAttribLocation(program_cube_vertex3_3, "a_color");
    a_uv_location_cube_vertex3_3 = glGetAttribLocation(program_cube_vertex3_3, "a_uv");
    u_diffuse_texture_location_cube_vertex3_3 = glGetUniformLocation(program_cube_vertex3_3, "u_diffuse_texture");

    while (!glfwWindowShouldClose(window_cube_vertex3_3))
    {
        float ratio;
        int width, height;
        glm::mat4 model, view, projection, mvp;

        glfwGetFramebufferSize(window_cube_vertex3_3, &width, &height);
        ratio = width / (float)height;

        glViewport(0, 0, width, height);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearColor(49.f / 255, 77.f / 255, 121.f / 255, 1.f);

        glm::mat4 trans = glm::translate(glm::vec3(0, 0, 0)); //不移动顶点坐标;

        static float rotate_eulerAngle = 0.f;
        rotate_eulerAngle += 1;
        glm::mat4 rotation = glm::eulerAngleYXZ(glm::radians(rotate_eulerAngle), glm::radians(rotate_eulerAngle), glm::radians(rotate_eulerAngle)); //使用欧拉角旋转;

        glm::mat4 scale = glm::scale(glm::vec3(2.0f, 2.0f, 2.0f)); //缩放;
        model = trans * scale * rotation;

        view = glm::lookAt(glm::vec3(0, 0, 10), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));

        projection = glm::perspective(glm::radians(60.f), ratio, 1.f, 1000.f);

        mvp = projection * view * model;

        //指定GPU程序(就是指定顶点着色器、片段着色器)
        glUseProgram(program_cube_vertex3_3);
        {
            glEnable(GL_DEPTH_TEST);
            glEnable(GL_CULL_FACE);//开启背面剔除

            //指定当前使用的VBO
            glBindBuffer(GL_ARRAY_BUFFER, kVBO_cube_vertex3_3);
            //将Shader变量(a_pos)和顶点坐标VBO句柄进行关联，最后的0表示数据偏移量。
            glEnableVertexAttribArray(vpos_location_cube_vertex3_3);
            glVertexAttribPointer(vpos_location_cube_vertex3_3, 3, GL_FLOAT, false, sizeof(Vertex_cube_vertex3_3), 0);
            //启用顶点Shader属性(a_color)，指定与顶点颜色数据进行关联
            glEnableVertexAttribArray(vcol_location_cube_vertex3_3);
            glVertexAttribPointer(vcol_location_cube_vertex3_3, 4, GL_FLOAT, false, sizeof(Vertex_cube_vertex3_3), (void*)(sizeof(float) * 3));
            //将Shader变量(a_uv)和顶点UV坐标VBO句柄进行关联，最后的0表示数据偏移量。
            glEnableVertexAttribArray(a_uv_location_cube_vertex3_3);
            glVertexAttribPointer(a_uv_location_cube_vertex3_3, 2, GL_FLOAT, false, sizeof(Vertex_cube_vertex3_3), (void*)(sizeof(float) * (3 + 4)));

            //上传mvp矩阵
            glUniformMatrix4fv(mvp_location_cube_vertex3_3, 1, GL_FALSE, &mvp[0][0]);

            //贴图设置
            //激活纹理单元0
            glActiveTexture(GL_TEXTURE0);
            //将加载的图片纹理句柄，绑定到纹理单元0的Texture2D上。
            glBindTexture(GL_TEXTURE_2D, texture2d_cube_vertex3_3->gl_texture_id_);
            //设置Shader程序从纹理单元0读取颜色数据
            glUniform1i(u_diffuse_texture_location_cube_vertex3_3, 0);
            glBindVertexArray(kVAO_cube_vertex3_3);
            {
                glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_SHORT, 0);//使用顶点索引进行绘制，最后的0表示数据偏移量。
            }
            glBindVertexArray(0);
        }
        glfwSwapBuffers(window_cube_vertex3_3);
        glfwPollEvents();
    }

    glfwDestroyWindow(window_cube_vertex3_3);

    glfwTerminate();
    exit(EXIT_SUCCESS);
}