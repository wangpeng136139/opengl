#ifndef UNTITLED_RENDERTASKSETUNIFORM1I_H
#define UNTITLED_RENDERTASKSETUNIFORM1I_H

#include "RenderTaskBase.h"
/// 上传1个int值
class RenderTaskSetUniform1i :public RenderTaskBase {
public:
    RenderTaskSetUniform1i() {
        render_command_ = RenderCommand::SET_UNIFORM_1I;
    }
    ~RenderTaskSetUniform1i() {
        free(uniform_name_);
    }
public:
    unsigned int shader_program_handle_;//shader程序句柄
    char* uniform_name_ = nullptr;//uniform变量名
    int value_;//目标值
};
#endif

