#ifndef UNTITLED_RENDERTASKSETUNIFORMMATRIX4FV_H
#define UNTITLED_RENDERTASKSETUNIFORMMATRIX4FV_H
#include "RenderTaskBase.h"
#include <glm/glm.hpp>
class RenderTaskSetUniformMatrix4fv : public RenderTaskBase {
public:
    RenderTaskSetUniformMatrix4fv() {
        render_command_ = RenderCommand::SET_UNIFORM_MATRIX_4FV;
    }
    ~RenderTaskSetUniformMatrix4fv() {
        free(uniform_name_);
    }
public:
    unsigned int shader_program_handle_ = 0;//��ɫ��������
    char* uniform_name_ = nullptr;//uniform������
    bool transpose_ = false;//�Ƿ�ת��
    glm::mat4 matrix_;//4x4��������
};

#endif
