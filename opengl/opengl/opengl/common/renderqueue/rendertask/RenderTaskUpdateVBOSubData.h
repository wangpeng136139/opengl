#ifndef UNTITLED_RENDERTASKUPDATEVBOSUBDATA_H
#define UNTITLED_RENDERTASKUPDATEVBOSUBDATA_H
#include "RenderTaskBase.h"
/// ����VBO����
class RenderTaskUpdateVBOSubData :public RenderTaskBase {
public:
    RenderTaskUpdateVBOSubData() {
        render_command_ = RenderCommand::UPDATE_VBO_SUB_DATA;
    }
    ~RenderTaskUpdateVBOSubData() {
        free(vertex_data_);
    }
public:
    unsigned int vbo_handle_ = 0;//VBO���
    unsigned int vertex_data_size_;//�������ݴ�С
    void* vertex_data_;//��������
};
#endif
