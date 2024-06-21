#ifndef UNTITLED_RENDERTASKSETUNIFORM1I_H
#define UNTITLED_RENDERTASKSETUNIFORM1I_H

#include "RenderTaskBase.h"
/// �ϴ�1��intֵ
class RenderTaskSetUniform1i :public RenderTaskBase {
public:
    RenderTaskSetUniform1i() {
        render_command_ = RenderCommand::SET_UNIFORM_1I;
    }
    ~RenderTaskSetUniform1i() {
        free(uniform_name_);
    }
public:
    unsigned int shader_program_handle_;//shader������
    char* uniform_name_ = nullptr;//uniform������
    int value_;//Ŀ��ֵ
};
#endif

