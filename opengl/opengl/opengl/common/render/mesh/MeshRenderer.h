#pragma once
#include "Mesh.h"
#include "MeshFilter.h"
#include "../material/Material.h"

class MeshRenderer:public Component
{
public:
    MeshRenderer();
    ~MeshRenderer();

    void SetMaterial(Material* material);//设置Material
    Material* material() { return material_; }

    void SetMeshFilter(MeshFilter* mesh_filter);
    MeshFilter* mesh_filter() { return mesh_filter_; }

    void SetMVP(glm::mat4 mvp);

    void Render();//渲染
private:
    Material* material_;
    MeshFilter* mesh_filter_;
    glm::mat4 mvp_;
    unsigned int vertex_buffer_object_ = 0;//顶点缓冲区对象
    unsigned int element_buffer_object_ = 0;//索引缓冲区对象
    unsigned int vertex_array_object_ = 0;//顶点数组对象
};

