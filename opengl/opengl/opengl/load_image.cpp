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
#include "Texture2D.h"

using namespace std;


#ifndef UNTITLED_SHADERSOURCE_H
#define UNTITLED_SHADERSOURCE_H

//������ɫ������
static const char* vertex_shader_text_load_image =
"#version 110\n"

"uniform mat4 u_mvp;\n"

"attribute  vec3 a_pos;\n"
"attribute  vec4 a_color;\n"
"attribute  vec2 a_uv;\n"

"varying vec4 v_color;\n"
"varying vec2 v_uv;\n"
"void main()\n"
"{\n"
"    gl_Position = u_mvp * vec4(a_pos, 1.0);\n"
"    v_color = a_color;\n"
"   v_uv = a_uv;\n"
"}\n";
//Ƭ����ɫ������
static const char* fragment_shader_text_load_image =
"#version 110\n"
"uniform sampler2D u_diffuse_texture;\n"
"varying vec4 v_color;\n"
"varying vec2 v_uv;"
"void main()\n"
"{\n"
"    gl_FragColor = texture2D(u_diffuse_texture,v_uv);\n"
"}\n";

#endif //UNTITLED_SHADERSOURCE_H

using namespace std;

static const glm::vec3 kPositions_load_image[36] = {
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

static const glm::vec4 kColors_load_image[36] = {
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

static const glm::vec2 kUvs_load_image[36] =
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


GLFWwindow* window_load_image;
GLuint vertex_shader_load_image, fragment_shader_load_image, program_load_image;
GLint mvp_location_load_image, vpos_location_load_image, vcol_location_load_image, u_diffuse_texture_location_load_image, a_uv_location_load_image;
Texture2D* texture2d_load_image = nullptr;


static void error_callbac_load_image(int error, const char* description)
{
    fprintf(stderr, "Error: %s\n", description);
}



void init_opengl_load_image()
{
    //���ô���ص�
    glfwSetErrorCallback(error_callbac_load_image);
    /* ��ʼ��glfw */
    if (!glfwInit())
        exit(EXIT_FAILURE);

    //ָ��opengl�汾��
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    //��������
    window_load_image = glfwCreateWindow(960, 640, "Simple example", NULL, NULL);
    if (!window_load_image)
    {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glfwMakeContextCurrent(window_load_image);
    // ����OpenGL ָ��   
    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
    //���������ʾ����������֮ǰ�ȴ���֡����ͨ����Ϊvsync��
   //Ĭ������£��������Ϊ0������Ϊ��Ļÿ��ֻ����60-75�Σ����Դ󲿷ֵĻ��治�ᱻ��ʾ��
   //���ң��������п�������Ļ���µ��м佻����������Ļ˺�ѵ������
   //���ԣ����Խ��ü����Ϊ1����ÿ֡����һ�Ρ�����������Ϊ���ߵ�ֵ��������ܵ��������ӳ١�
    glfwSwapInterval(1);

}

/// ���롢����Shader  
void compile_shader_load_image()
{
    //��������Shader
    vertex_shader_load_image = glCreateShader(GL_VERTEX_SHADER);
    //ָ��ShaderԴ��
    glShaderSource(vertex_shader_load_image, 1, &vertex_shader_text_load_image, NULL);
    //����Shader
    glCompileShader(vertex_shader_load_image);
    //��ȡ������
    GLint compile_status = GL_FALSE;
    glGetShaderiv(vertex_shader_load_image, GL_COMPILE_STATUS, &compile_status);
    if (compile_status == GL_FALSE)
    {
        GLchar message[256];
        glGetShaderInfoLog(vertex_shader_load_image, sizeof(message), 0, message);
        cout << "compile vs error:" << message << endl;
    }

    //����Ƭ��Shader
    fragment_shader_load_image = glCreateShader(GL_FRAGMENT_SHADER);
    //ָ��ShaderԴ��
    glShaderSource(fragment_shader_load_image, 1, &fragment_shader_text_load_image, NULL);
    //����Shader
    glCompileShader(fragment_shader_load_image);
    //��ȡ������
    compile_status = GL_FALSE;
    glGetShaderiv(fragment_shader_load_image, GL_COMPILE_STATUS, &compile_status);
    if (compile_status == GL_FALSE)
    {
        GLchar message[256];
        glGetShaderInfoLog(fragment_shader_load_image, sizeof(message), 0, message);
        cout << "compile fs error:" << message << endl;
    }


    //����GPU����
    program_load_image = glCreateProgram();
    //����Shader
    glAttachShader(program_load_image, vertex_shader_load_image);
    glAttachShader(program_load_image, fragment_shader_load_image);
    //Link
    glLinkProgram(program_load_image);
    //��ȡ������
    GLint link_status = GL_FALSE;
    glGetProgramiv(program_load_image, GL_LINK_STATUS, &link_status);
    if (link_status == GL_FALSE)
    {
        GLchar message[256];
        glGetProgramInfoLog(program_load_image, sizeof(message), 0, message);
        cout << "link error:" << message << endl;
    }
}

//����Texture
void CreateTexture_load_image(std::string image_file_path)
{
    texture2d_load_image = Texture2D::LoadFromFile(image_file_path);
}

int draw_load_image(void)
{
    init_opengl_load_image();
    CreateTexture_load_image("1.png");
    compile_shader_load_image();

    //��ȡshader����ID
    mvp_location_load_image = glGetUniformLocation(program_load_image, "u_mvp");
    vpos_location_load_image = glGetAttribLocation(program_load_image, "a_pos");
    vcol_location_load_image = glGetAttribLocation(program_load_image, "a_color");
    a_uv_location_load_image = glGetAttribLocation(program_load_image, "a_uv");
    u_diffuse_texture_location_load_image = glGetUniformLocation(program_load_image, "u_diffuse_texture");

    while (!glfwWindowShouldClose(window_load_image))
    {
        float ratio;
        int width, height;
        glm::mat4 model, view, projection, mvp;

        //��ȡ������
        glfwGetFramebufferSize(window_load_image, &width, &height);
        ratio = width / (float)height;

        glViewport(0, 0, width, height);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearColor(49.f / 255, 77.f / 255, 121.f / 255, 1.f);

        //����ϵ�任
        glm::mat4 trans = glm::translate(glm::vec3(0, 0, 0)); //���ƶ���������;
        static float rotate_eulerAngle = 0.f;
        rotate_eulerAngle += 1;
        glm::mat4 rotation = glm::eulerAngleYXZ(glm::radians(rotate_eulerAngle), glm::radians(rotate_eulerAngle), glm::radians(rotate_eulerAngle)); //ʹ��ŷ������ת;
        //glm::mat4 rotation = glm::eulerAngleYXZ(glm::radians(0.f), glm::radians(0.f), glm::radians(0.f)); //ʹ��ŷ������ת;
        glm::mat4 scale = glm::scale(glm::vec3(2.0f, 2.0f, 2.0f)); //����;
        model = trans * scale * rotation;


        view = glm::lookAt(glm::vec3(0, 0, 10), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));

        projection = glm::perspective(glm::radians(60.f), ratio, 1.f, 1000.f);

        mvp = projection * view * model;

        //ָ��GPU����(����ָ��������ɫ����Ƭ����ɫ��)
        glUseProgram(program_load_image);
        {
            glEnable(GL_DEPTH_TEST);
            glEnable(GL_CULL_FACE);//���������޳�
              
            //���ö���Shader����(a_pos)��ָ���붥���������ݽ��й���
            glEnableVertexAttribArray(vpos_location_load_image);
            glVertexAttribPointer(vpos_location_load_image, 3, GL_FLOAT, false, sizeof(glm::vec3), kPositions_load_image);

            //���ö���Shader����(a_color)��ָ���붥����ɫ���ݽ��й���
            glEnableVertexAttribArray(vcol_location_load_image);
            glVertexAttribPointer(vcol_location_load_image, 3, GL_FLOAT, false, sizeof(glm::vec4), kColors_load_image);

            //���ö���Shader����(a_uv)��ָ���붥��UV���ݽ��й���
            glEnableVertexAttribArray(a_uv_location_load_image);
            glVertexAttribPointer(a_uv_location_load_image, 2, GL_FLOAT, false, sizeof(glm::vec2), kUvs_load_image);

            //�ϴ�mvp����
            glUniformMatrix4fv(mvp_location_load_image, 1, GL_FALSE, &mvp[0][0]);

            //��ͼ����
            //��������Ԫ0
            glActiveTexture(GL_TEXTURE0);
            //�����ص�ͼƬ���������󶨵�����Ԫ0��Texture2D�ϡ�
            glBindTexture(GL_TEXTURE_2D, texture2d_load_image->gl_texture_id_);
            //����Shader���������Ԫ0��ȡ��ɫ����
            glUniform1i(u_diffuse_texture_location_load_image, 0);

            //void glDrawArrays(GLenum mode,GLint first,GLsizei count);����
            glDrawArrays(GL_TRIANGLES, 0, 6 * 6);//��ʾ�ӵ�0�����㿪ʼ�����ܹ���6��ÿ����6�����㡣
        }

        glfwSwapBuffers(window_load_image);
        glfwPollEvents();
    }

    glfwDestroyWindow(window_load_image);

    glfwTerminate();
    exit(EXIT_SUCCESS);
}