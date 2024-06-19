#include "../common/render_head.h"



using namespace std;


#ifndef UNTITLED_SHADERSOURCE_H
#define UNTITLED_SHADERSOURCE_H

//������ɫ������
static const char* vertex_shader_text_quad =
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
static const char* fragment_shader_text_quad =
"#version 110\n"
"varying vec4 v_color;\n"
"void main()\n"
"{\n"
"    gl_FragColor = v_color;\n"
"}\n";

#endif //UNTITLED_SHADERSOURCE_H

using namespace std;
 
static const glm::vec3 kPositions_Quad[6] = {
    //��һ��������
    { -1.0f, -1.0f,0.0f},//����
    {  1.0f, -1.0f,0.0f},//����
    {  1.0f,  1.0f,0.0f},//����
    //�ڶ���������
    {  1.0f,  1.0f,0.0f},//����
    { -1.0f,  1.0f,0.0f},//����
    { -1.0f, -1.0f,0.0f} //����
};

static const glm::vec4 kColors_Quad[6] = {
    //��һ����������ɫ
           { 1.f, 0.f, 0.f ,1.f},//����
           { 0.f, 1.f, 0.f ,1.f},//����
           { 0.f, 0.f, 1.f ,1.f},//����
           //�ڶ�����������ɫ
           { 0.f, 0.f, 1.f ,1.f},//����
           { 1.f, 0.f, 0.f ,1.f},//����
           { 1.f, 0.f, 0.f ,1.f} //����
};



GLFWwindow* window_quad;
GLuint vertex_shader_quad, fragment_shader_quad, program_quad;
GLint mvp_location_quad, vpos_location_quad, vcol_location_quad;


static void error_callbackri_quad(int error, const char* description)
{
    fprintf(stderr, "Error: %s\n", description);
}



void init_opengl_quad()
{
    //���ô���ص�
    glfwSetErrorCallback(error_callbackri_quad);
    /* ��ʼ��glfw */
    if (!glfwInit())
        exit(EXIT_FAILURE);

    //ָ��opengl�汾��
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    //��������
    window_quad = glfwCreateWindow(960, 640, "Simple example", NULL, NULL);
    if (!window_quad)
    {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glfwMakeContextCurrent(window_quad);
    // ����OpenGL ָ��   
    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
    //���������ʾ����������֮ǰ�ȴ���֡����ͨ����Ϊvsync��
   //Ĭ������£��������Ϊ0������Ϊ��Ļÿ��ֻ����60-75�Σ����Դ󲿷ֵĻ��治�ᱻ��ʾ��
   //���ң��������п�������Ļ���µ��м佻����������Ļ˺�ѵ������
   //���ԣ����Խ��ü����Ϊ1����ÿ֡����һ�Ρ�����������Ϊ���ߵ�ֵ��������ܵ��������ӳ١�
    glfwSwapInterval(1);

}

/// ���롢����Shader  
void compile_shader_quad()
{
    //��������Shader
    vertex_shader_quad = glCreateShader(GL_VERTEX_SHADER);
    //ָ��ShaderԴ��
    glShaderSource(vertex_shader_quad, 1, &vertex_shader_text_quad, NULL);
    //����Shader
    glCompileShader(vertex_shader_quad);
    //��ȡ������
    GLint compile_status = GL_FALSE;
    glGetShaderiv(vertex_shader_quad, GL_COMPILE_STATUS, &compile_status);
    if (compile_status == GL_FALSE)
    {
        GLchar message[256];
        glGetShaderInfoLog(vertex_shader_quad, sizeof(message), 0, message);
        cout << "compile vs error:" << message << endl;
    }

    //����Ƭ��Shader
    fragment_shader_quad = glCreateShader(GL_FRAGMENT_SHADER);
    //ָ��ShaderԴ��
    glShaderSource(fragment_shader_quad, 1, &fragment_shader_text_quad, NULL);
    //����Shader
    glCompileShader(fragment_shader_quad);
    //��ȡ������
    compile_status = GL_FALSE;
    glGetShaderiv(fragment_shader_quad, GL_COMPILE_STATUS, &compile_status);
    if (compile_status == GL_FALSE)
    {
        GLchar message[256];
        glGetShaderInfoLog(fragment_shader_quad, sizeof(message), 0, message);
        cout << "compile fs error:" << message << endl;
    }


    //����GPU����
    program_quad = glCreateProgram();
    //����Shader
    glAttachShader(program_quad, vertex_shader_quad);
    glAttachShader(program_quad, fragment_shader_quad);
    //Link
    glLinkProgram(program_quad);
    //��ȡ������
    GLint link_status = GL_FALSE;
    glGetProgramiv(program_quad, GL_LINK_STATUS, &link_status);
    if (link_status == GL_FALSE)
    {
        GLchar message[256];
        glGetProgramInfoLog(program_quad, sizeof(message), 0, message);
        cout << "link error:" << message << endl;
    }
}

int draw_quad(void)
{
    init_opengl_quad();

    compile_shader_quad();

    //��ȡshader����ID
    mvp_location_quad = glGetUniformLocation(program_quad, "u_mvp");
    vpos_location_quad = glGetAttribLocation(program_quad, "a_pos");
    vcol_location_quad = glGetAttribLocation(program_quad, "a_color");

    while (!glfwWindowShouldClose(window_quad))
    {
        float ratio;
        int width, height;
        glm::mat4 model, view, projection, mvp;

        //��ȡ������
        glfwGetFramebufferSize(window_quad, &width, &height);
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
        glUseProgram(program_quad);
        {
            //���ö���Shader����(a_pos)��ָ���붥���������ݽ��й���
            glEnableVertexAttribArray(vpos_location_quad);
            glVertexAttribPointer(vpos_location_quad, 3, GL_FLOAT, false, sizeof(glm::vec3), kPositions_Quad);

            //���ö���Shader����(a_color)��ָ���붥����ɫ���ݽ��й���
            glEnableVertexAttribArray(vcol_location_quad);
            glVertexAttribPointer(vcol_location_quad, 3, GL_FLOAT, false, sizeof(glm::vec4), kColors_Quad);

            //�ϴ�mvp����
            glUniformMatrix4fv(mvp_location_quad, 1, GL_FALSE, &mvp[0][0]);

            //�ϴ��������ݲ����л���
            glDrawArrays(GL_TRIANGLES, 0, 6);
        }

        glfwSwapBuffers(window_quad);
        glfwPollEvents();
    }

    glfwDestroyWindow(window_quad);

    glfwTerminate();
    exit(EXIT_SUCCESS);
}