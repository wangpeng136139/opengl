#ifndef UNTITLED_MESH_MESHRENDERER_H
#define UNTITLED_MESH_MESHRENDERER_H

#include "MeshFilter.h"
#include "../material/render_material_head.h"

class MeshRenderer:public Component
{
public:
    MeshRenderer();
    ~MeshRenderer() override;

    void SetMaterial(Material* material);//设置Material
    Material* material() { return material_; }



    void SetMVP(glm::mat4 mvp);

    void Render();//渲染
private:
    Material* material_;
    unsigned int element_buffer_object_ = 0;//索引缓冲区对象
    unsigned int vertex_array_object_handle_ = 0;//顶点数组对象句柄
    unsigned int vertex_buffer_object_handle_ = 0;//顶端缓冲区句柄
};

#endif