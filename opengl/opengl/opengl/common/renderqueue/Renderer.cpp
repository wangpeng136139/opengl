#include "Renderer.h"

Renderer::Renderer(GLFWwindow* window) :window_(window) {
    render_thread_ = std::thread(&Renderer::RenderMain, this);//创建渲染线程，并指定渲染函数入口。
    render_thread_.detach();
}
Renderer::~Renderer() {
    if (render_thread_.joinable()) {
        render_thread_.join();//等待渲染线程结束
    }
}



/// 创建缓冲区
void Renderer::create_buffer() {

}



/// 编译、链接Shader
void Renderer::compile_shader()
{   
}


void Renderer::RenderMain() {

}