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
    unsigned int shader_program_handle_ = 0;//着色器程序句柄
    char* uniform_name_ = nullptr;//uniform变量名
    bool transpose_ = false;//是否转置
    glm::mat4 matrix_;//4x4矩阵数据
};

#endif
