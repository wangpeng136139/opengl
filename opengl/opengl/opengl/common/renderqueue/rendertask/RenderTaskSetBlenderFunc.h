#ifndef UNTITLED_RENDERTASKSETBLENDERFUNC_H
#define UNTITLED_RENDERTASKSETBLENDERFUNC_H
#include "RenderTaskBase.h"
/// ���û�Ϻ���
class RenderTaskSetBlenderFunc : public RenderTaskBase {
public:
    RenderTaskSetBlenderFunc() {
        render_command_ = RenderCommand::SET_BLENDER_FUNC;
    }
    ~RenderTaskSetBlenderFunc() {}
public:
    unsigned int source_blending_factor_;//Դ�������
    unsigned int destination_blending_factor_;//Ŀ��������
};
#endif 
