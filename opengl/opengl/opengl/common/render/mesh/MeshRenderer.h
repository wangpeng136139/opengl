#ifndef UNTITLED_MESH_MESHRENDERER_H
#define UNTITLED_MESH_MESHRENDERER_H

#include "MeshFilter.h"
#include "../material/render_material_head.h"

class MeshRenderer:public Component
{
public:
    MeshRenderer();
    ~MeshRenderer() override;

    void SetMaterial(Material* material);//����Material
    Material* material() { return material_; }



    void SetMVP(glm::mat4 mvp);

    void Render();//��Ⱦ
private:
    Material* material_;
    unsigned int element_buffer_object_ = 0;//��������������
    unsigned int vertex_array_object_handle_ = 0;//�������������
    unsigned int vertex_buffer_object_handle_ = 0;//���˻��������
};

#endif