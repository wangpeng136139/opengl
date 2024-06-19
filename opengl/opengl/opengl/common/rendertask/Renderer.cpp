#include "Renderer.h"

Renderer::Renderer(GLFWwindow* window) :window_(window) {
    render_thread_ = std::thread(&Renderer::RenderMain, this);//������Ⱦ�̣߳���ָ����Ⱦ������ڡ�
    render_thread_.detach();
}
Renderer::~Renderer() {
    if (render_thread_.joinable()) {
        render_thread_.join();//�ȴ���Ⱦ�߳̽���
    }
}



/// ����������
void Renderer::create_buffer() {

}



/// ���롢����Shader
void Renderer::compile_shader()
{   
}


void Renderer::RenderMain() {

}