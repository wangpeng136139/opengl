#include "../common/render_head.h"


using namespace std;


#ifndef UNTITLED_SHADERSOURCE_H
#define UNTITLED_SHADERSOURCE_H

//������ɫ������
static const char* vertex_shader_text_triangle =
"#version 110\n"

"uniform mat4 u_mvp;\n"

"attribute  vec3 a_pos;\n"
"attribute  vec4 a_color;\n"

"varying vec4 v_color;\n"

"void main()\n"
"{\n"
"    gl_Position = u_mvp * vec4(a_pos, 1.0);\n"
"    v_color = a_color;\n"
"}\n";
//Ƭ����ɫ������
static const char* fragment_shader_text_triangle =
"#version 110\n"
"varying vec4 v_color;\n"
"void main()\n"
"{\n"
"    gl_FragColor = v_color;\n"    
"}\n";

#endif //UNTITLED_SHADERSOURCE_H

#ifndef UNTITLED_VERTEXDATA_H
#define UNTITLED_VERTEXDATA_H


static const glm::vec3 kPositions_Triangle[3] = {
        glm::vec3{ -1.0f, -1.0f,0.0f},
        glm::vec3{  1.0f, -1.0f,0.0f},
        glm::vec3{   0.f,  1.0f,0.0f}
};

static const glm::vec4 kColors_Triangle[3] = {
        glm::vec4{ 1.f, 0.f, 0.f ,1.f},
        glm::vec4{ 0.f, 1.f, 0.f ,1.f},
        glm::vec4{ 0.f, 0.f, 1.f ,1.f}
};

#endif //UNTITLED_VERTEXDATA_H

static void error_callback_triangle(int error, const char* description)
{
    fprintf(stderr, "Error: %s\n", description);
}

GLFWwindow* window_triangle;
GLuint vertex_shader_triangle, fragment_shader_triangle, program_triangle;
GLint mvp_location_triangle, vpos_location_triangle, vcol_location_triangle;

/// ��ʼ��OpenGL
void init_opengl_triangle()
{
    cout << "init opengl" << endl;

    //���ô���ص�
    glfwSetErrorCallback(error_callback_triangle);

    if (!glfwInit())
        exit(EXIT_FAILURE);

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

    //��������
    window_triangle = glfwCreateWindow(960, 640, "Simple example", NULL, NULL);
    if (!window_triangle)
    {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glfwMakeContextCurrent(window_triangle);
    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
    glfwSwapInterval(1);


}

/// ���롢����Shader  
void compile_shader_triangle()
{
    //��������Shader
    vertex_shader_triangle = glCreateShader(GL_VERTEX_SHADER);
    //ָ��ShaderԴ��
    glShaderSource(vertex_shader_triangle, 1, &vertex_shader_text_triangle, NULL);
    //����Shader
    glCompileShader(vertex_shader_triangle);
    //��ȡ������
    GLint compile_status = GL_FALSE;
    glGetShaderiv(vertex_shader_triangle, GL_COMPILE_STATUS, &compile_status);
    if (compile_status == GL_FALSE)
    {
        GLchar message[256];
        glGetShaderInfoLog(vertex_shader_triangle, sizeof(message), 0, message);
        cout << "compile vs error:" << message << endl;
    }

    //����Ƭ��Shader
    fragment_shader_triangle = glCreateShader(GL_FRAGMENT_SHADER);
    //ָ��ShaderԴ��
    glShaderSource(fragment_shader_triangle, 1, &fragment_shader_text_triangle, NULL);
    //����Shader
    glCompileShader(fragment_shader_triangle);
    //��ȡ������
    compile_status = GL_FALSE;
    glGetShaderiv(fragment_shader_triangle, GL_COMPILE_STATUS, &compile_status);
    if (compile_status == GL_FALSE)
    {
        GLchar message[256];
        glGetShaderInfoLog(fragment_shader_triangle, sizeof(message), 0, message);
        cout << "compile fs error:" << message << endl;
    }


    //����GPU����
    program_triangle = glCreateProgram();
    //����Shader
    glAttachShader(program_triangle, vertex_shader_triangle);
    glAttachShader(program_triangle, fragment_shader_triangle);
    //Link
    glLinkProgram(program_triangle);
    //��ȡ������
    GLint link_status = GL_FALSE;
    glGetProgramiv(program_triangle, GL_LINK_STATUS, &link_status);
    if (link_status == GL_FALSE)
    {
        GLchar message[256];
        glGetProgramInfoLog(program_triangle, sizeof(message), 0, message);
        cout << "link error:" << message << endl;
    }
}

int draw_triangle(void)
{
    init_opengl_triangle();

    compile_shader_triangle();

    //��ȡshader����ID
    mvp_location_triangle = glGetUniformLocation(program_triangle, "u_mvp");
    vpos_location_triangle = glGetAttribLocation(program_triangle, "a_pos");
    vcol_location_triangle = glGetAttribLocation(program_triangle, "a_color");

    while (!glfwWindowShouldClose(window_triangle))
    {
        float ratio;
        int width, height;
        glm::mat4 model, view, projection, mvp;

        //��ȡ������
        glfwGetFramebufferSize(window_triangle, &width, &height);
        ratio = width / (float)height;

        glViewport(0, 0, width, height);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearColor(49.f / 255, 77.f / 255, 121.f / 255, 1.f);

        //����ϵ�任
        glm::mat4 trans = glm::translate(glm::vec3(0, 0, 0)); //���ƶ���������;
        glm::mat4 rotation = glm::eulerAngleYXZ(glm::radians(0.f), glm::radians(0.f), glm::radians(0.f)); //ʹ��ŷ������ת;
        glm::mat4 scale = glm::scale(glm::vec3(2.0f, 2.0f, 2.0f)); //����;
        model = trans * scale * rotation;

        view = glm::lookAt(glm::vec3(0, 0, 10), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));

        projection = glm::perspective(glm::radians(60.f), ratio, 1.f, 1000.f);

        mvp = projection * view * model;

        //ָ��GPU����(����ָ��������ɫ����Ƭ����ɫ��)
        glUseProgram(program_triangle);
        {
            //���ö���Shader����(a_pos)��ָ���붥���������ݽ��й���
            glEnableVertexAttribArray(vpos_location_triangle);
            glVertexAttribPointer(vpos_location_triangle, 3, GL_FLOAT, false, sizeof(glm::vec3), kPositions_Triangle);

            //���ö���Shader����(a_color)��ָ���붥����ɫ���ݽ��й���
            glEnableVertexAttribArray(vcol_location_triangle);
            glVertexAttribPointer(vcol_location_triangle, 3, GL_FLOAT, false, sizeof(glm::vec4), kColors_Triangle);

            //�ϴ�mvp����
            glUniformMatrix4fv(mvp_location_triangle, 1, GL_FALSE, &mvp[0][0]);

            //�ϴ��������ݲ����л���
            glDrawArrays(GL_TRIANGLES, 0, 3);
        }

        glfwSwapBuffers(window_triangle);
        glfwPollEvents();
    }

    glfwDestroyWindow(window_triangle);

    glfwTerminate();
    exit(EXIT_SUCCESS);
}