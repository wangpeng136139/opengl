#ifndef UNTITLED_RENDERER_H
#define UNTITLED_RENDERER_H

#include <thread>
#include <glad/glad.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

class Renderer {
public:
    Renderer(GLFWwindow* window);
    ~Renderer();

private:
    /// ��Ⱦ�߳�������
    void RenderMain();
    void create_buffer();
    void compile_shader();
private:
    GLFWwindow* window_;//glfw�����Ĵ���
    std::thread render_thread_;//��Ⱦ�߳�
    GLuint vertex_shader, fragment_shader, program;
    GLint vpos_location, vcol_location;
    GLuint vbo_pos, vbo_color, vao;
};


#endif //UNTITLED_RENDERER_H
