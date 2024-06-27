#ifndef UNTITLED_MESH_TESTMESHRENDERER_H
#define UNTITLED_MESH_TESTMESHRENDERER_H

#include "MeshFilter.h"
#include "../material/render_material_head.h"

class TestMeshRenderer :public Component
{
public:
    TestMeshRenderer();
    ~TestMeshRenderer() override;

    void SetMaterial(Material* material);//����Material
    Material* material() { return material_; }

    void SetMeshFilter(MeshFilter* mesh_filter);
    MeshFilter* mesh_filter() { return mesh_filter_; }

    void SetView(glm::mat4 view) { view_ = view; };
    void SetProjection(glm::mat4 projection) { projection_ = projection; };


    void SetMVP(glm::mat4 mvp);

    void TestRender();
    void MVPRender();
    void Render();//��Ⱦ
private:
    Material* material_;
    MeshFilter* mesh_filter_;
    glm::mat4 mvp_;

    glm::mat4 view_;
    glm::mat4 projection_;
    unsigned int vertex_buffer_object_ = 0;//���㻺��������
    unsigned int element_buffer_object_ = 0;//��������������
    unsigned int vertex_array_object_ = 0;//�����������
};

#endif