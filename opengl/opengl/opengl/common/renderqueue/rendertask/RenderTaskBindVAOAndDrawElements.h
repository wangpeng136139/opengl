#ifndef UNTITLED_RENDERTASKBINDVAOANDDRAWELEMENTS_H
#define UNTITLED_RENDERTASKBINDVAOANDDRAWELEMENTS_H

#include "RenderTaskBase.h"


/// ��VAO������
class RenderTaskBindVAOAndDrawElements :public RenderTaskBase {
public:
    RenderTaskBindVAOAndDrawElements() {
        render_command_ = RenderCommand::BIND_VAO_AND_DRAW_ELEMENTS;
    }
    ~RenderTaskBindVAOAndDrawElements() {}
public:
    unsigned int vao_handle_;
    unsigned int vertex_index_num_;//��������
};

#endif
