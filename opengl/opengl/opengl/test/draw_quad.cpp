#include "../common/render_head.h"



using namespace std;


#ifndef UNTITLED_SHADERSOURCE_H
#define UNTITLED_SHADERSOURCE_H

//顶点着色器代码
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
//片段着色器代码
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
    //第一个三角形
    { -1.0f, -1.0f,0.0f},//左下
    {  1.0f, -1.0f,0.0f},//右下
    {  1.0f,  1.0f,0.0f},//右上
    //第二个三角形
    {  1.0f,  1.0f,0.0f},//右上
    { -1.0f,  1.0f,0.0f},//左上
    { -1.0f, -1.0f,0.0f} //左下
};

static const glm::vec4 kColors_Quad[6] = {
    //第一个三角形颜色
           { 1.f, 0.f, 0.f ,1.f},//左下
           { 0.f, 1.f, 0.f ,1.f},//右下
           { 0.f, 0.f, 1.f ,1.f},//右上
           //第二个三角形颜色
           { 0.f, 0.f, 1.f ,1.f},//右上
           { 1.f, 0.f, 0.f ,1.f},//左上
           { 1.f, 0.f, 0.f ,1.f} //左下
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
    //设置错误回调
    glfwSetErrorCallback(error_callbackri_quad);
    /* 初始化glfw */
    if (!glfwInit())
        exit(EXIT_FAILURE);

    //指定opengl版本号
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    //创建窗口
    window_quad = glfwCreateWindow(960, 640, "Simple example", NULL, NULL);
    if (!window_quad)
    {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glfwMakeContextCurrent(window_quad);
    // 加载OpenGL 指针   
    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
    //交换间隔表示交换缓冲区之前等待的帧数，通常称为vsync。
   //默认情况下，交换间隔为0，但因为屏幕每秒只更新60-75次，所以大部分的画面不会被显示。
   //而且，缓冲区有可能在屏幕更新的中间交换，出现屏幕撕裂的情况。
   //所以，可以将该间隔设为1，即每帧更新一次。它可以设置为更高的值，但这可能导致输入延迟。
    glfwSwapInterval(1);

}

/// 编译、链接Shader  
void compile_shader_quad()
{
    //创建顶点Shader
    vertex_shader_quad = glCreateShader(GL_VERTEX_SHADER);
    //指定Shader源码
    glShaderSource(vertex_shader_quad, 1, &vertex_shader_text_quad, NULL);
    //编译Shader
    glCompileShader(vertex_shader_quad);
    //获取编译结果
    GLint compile_status = GL_FALSE;
    glGetShaderiv(vertex_shader_quad, GL_COMPILE_STATUS, &compile_status);
    if (compile_status == GL_FALSE)
    {
        GLchar message[256];
        glGetShaderInfoLog(vertex_shader_quad, sizeof(message), 0, message);
        cout << "compile vs error:" << message << endl;
    }

    //创建片段Shader
    fragment_shader_quad = glCreateShader(GL_FRAGMENT_SHADER);
    //指定Shader源码
    glShaderSource(fragment_shader_quad, 1, &fragment_shader_text_quad, NULL);
    //编译Shader
    glCompileShader(fragment_shader_quad);
    //获取编译结果
    compile_status = GL_FALSE;
    glGetShaderiv(fragment_shader_quad, GL_COMPILE_STATUS, &compile_status);
    if (compile_status == GL_FALSE)
    {
        GLchar message[256];
        glGetShaderInfoLog(fragment_shader_quad, sizeof(message), 0, message);
        cout << "compile fs error:" << message << endl;
    }


    //创建GPU程序
    program_quad = glCreateProgram();
    //附加Shader
    glAttachShader(program_quad, vertex_shader_quad);
    glAttachShader(program_quad, fragment_shader_quad);
    //Link
    glLinkProgram(program_quad);
    //获取编译结果
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

    //获取shader属性ID
    mvp_location_quad = glGetUniformLocation(program_quad, "u_mvp");
    vpos_location_quad = glGetAttribLocation(program_quad, "a_pos");
    vcol_location_quad = glGetAttribLocation(program_quad, "a_color");

    while (!glfwWindowShouldClose(window_quad))
    {
        float ratio;
        int width, height;
        glm::mat4 model, view, projection, mvp;

        //获取画面宽高
        glfwGetFramebufferSize(window_quad, &width, &height);
        ratio = width / (float)height;

        glViewport(0, 0, width, height);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearColor(49.f / 255, 77.f / 255, 121.f / 255, 1.f);

        //坐标系变换
        glm::mat4 trans = glm::translate(glm::vec3(0, 0, 0)); //不移动顶点坐标;
        glm::mat4 rotation = glm::eulerAngleYXZ(glm::radians(0.f), glm::radians(0.f), glm::radians(0.f)); //使用欧拉角旋转;
        glm::mat4 scale = glm::scale(glm::vec3(2.0f, 2.0f, 2.0f)); //缩放;
        model = trans * scale * rotation;

        view = glm::lookAt(glm::vec3(0, 0, 10), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));

        projection = glm::perspective(glm::radians(60.f), ratio, 1.f, 1000.f);

        mvp = projection * view * model;

        //指定GPU程序(就是指定顶点着色器、片段着色器)
        glUseProgram(program_quad);
        {
            //启用顶点Shader属性(a_pos)，指定与顶点坐标数据进行关联
            glEnableVertexAttribArray(vpos_location_quad);
            glVertexAttribPointer(vpos_location_quad, 3, GL_FLOAT, false, sizeof(glm::vec3), kPositions_Quad);

            //启用顶点Shader属性(a_color)，指定与顶点颜色数据进行关联
            glEnableVertexAttribArray(vcol_location_quad);
            glVertexAttribPointer(vcol_location_quad, 3, GL_FLOAT, false, sizeof(glm::vec4), kColors_Quad);

            //上传mvp矩阵
            glUniformMatrix4fv(mvp_location_quad, 1, GL_FALSE, &mvp[0][0]);

            //上传顶点数据并进行绘制
            glDrawArrays(GL_TRIANGLES, 0, 6);
        }

        glfwSwapBuffers(window_quad);
        glfwPollEvents();
    }

    glfwDestroyWindow(window_quad);

    glfwTerminate();
    exit(EXIT_SUCCESS);
}