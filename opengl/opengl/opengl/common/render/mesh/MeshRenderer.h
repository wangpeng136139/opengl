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

    void SetMeshFilter(MeshFilter* mesh_filter);
    MeshFilter* mesh_filter() { return mesh_filter_; }

    void SetView(glm::mat4 view) { view_ = view; };
    void SetProjection(glm::mat4 projection) { projection_ = projection; };


    void SetMVP(glm::mat4 mvp);

    void TestRender();
    void MVPRender();
    void Render();//渲染
private:
    Material* material_;
    MeshFilter* mesh_filter_;
    glm::mat4 mvp_;

    glm::mat4 view_;
    glm::mat4 projection_;
    unsigned int vertex_buffer_object_ = 0;//顶点缓冲区对象
    unsigned int element_buffer_object_ = 0;//索引缓冲区对象
    unsigned int vertex_array_object_ = 0;//顶点数组对象
};

#endif