#ifndef UNTITLED_RENDERTASKUPDATEVBOSUBDATA_H
#define UNTITLED_RENDERTASKUPDATEVBOSUBDATA_H
#include "RenderTaskBase.h"
/// 更新VBO数据
class RenderTaskUpdateVBOSubData :public RenderTaskBase {
public:
    RenderTaskUpdateVBOSubData() {
        render_command_ = RenderCommand::UPDATE_VBO_SUB_DATA;
    }
    ~RenderTaskUpdateVBOSubData() {
        free(vertex_data_);
    }
public:
    unsigned int vbo_handle_ = 0;//VBO句柄
    unsigned int vertex_data_size_;//顶点数据大小
    void* vertex_data_;//顶点数据
};
#endif
