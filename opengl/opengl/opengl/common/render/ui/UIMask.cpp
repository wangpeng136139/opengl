//
// Created by captain on 2021/10/15.
//

#include "UIMask.h"
#include <vector>
#include <rttr/registration>
#include "../../component/GameObject.h"
#include "../../render/textures/Texture2D.h"
#include "../../render/material/Material.h"
#include "../../render/mesh/MeshFilter.h"
#include "../../common/Debug.h"
#include "../../render/mesh/MeshRenderer.h"
#include "../../renderdevice/RenderDevice.h"

using namespace rttr;
RTTR_REGISTRATION{
    registration::class_<UIMask>("UIMask")
            .constructor<>()(rttr::policy::ctor::as_raw_ptr);
}


UIMask::UIMask() {

}

UIMask::~UIMask() {

}

void UIMask::OnEnable() {

}

void UIMask::Update() {
    Component::Update();
    if (texture2D_ == nullptr) {
        return;
    }
    MeshFilter* mesh_filter = dynamic_cast<MeshFilter*>(game_object()->GetComponent("MeshFilter"));
    if (mesh_filter == nullptr) {
        //���� MeshFilter
        std::vector<Vertex> vertex_vector = {
                { {0.f, 0.0f, 0.0f}, {1.0f,1.0f,1.0f,1.0f},   {0.f, 0.f} },
                { {texture2D_->width(), 0.0f, 0.0f}, {1.0f,1.0f,1.0f,1.0f},   {1.f, 0.f} },
                { {texture2D_->width(),  texture2D_->height(), 0.0f}, {1.0f,1.0f,1.0f,1.0f},   {1.f, 1.f} },
                { {0.f,  texture2D_->height(), 0.0f}, {1.0f,1.0f,1.0f,1.0f},   {0.f, 1.f} }
        };
        std::vector<unsigned short> index_vector = {
                0,1,2,
                0,2,3
        };
        mesh_filter = dynamic_cast<MeshFilter*>(game_object()->AddComponent("MeshFilter"));
        mesh_filter->CreateMesh(vertex_vector, index_vector);

        //���� Material
        auto material = new Material();//���ò���
        material->Parse("material/ui_mask.mat");
        material->SetTexture("u_diffuse_texture", texture2D_);

        //���� MeshRenderer ���
        auto mesh_renderer = dynamic_cast<MeshRenderer*>(game_object()->AddComponent("MeshRenderer"));
        mesh_renderer->SetMaterial(material);
    }
}

void UIMask::OnPreRender() {
    Component::OnPreRender();
    RenderDevice::instance()->Enable(RenderDevice::STENCIL_TEST);//����ģ�����
    glClearStencil(0); __CHECK_GL_ERROR__//����Ĭ��ģ��ֵ 0
        glStencilFunc(GL_NEVER, 0x0, 0xFF); __CHECK_GL_ERROR__//ͨͨ��ͨ��ģ����ԡ�
        glStencilOp(GL_INCR, GL_INCR, GL_INCR); __CHECK_GL_ERROR__//���ص�ģ��ֵ 0+1 = 1
}

void UIMask::OnPostRender() {
    Component::OnPostRender();
}

void UIMask::OnDisable() {
    RenderDevice::instance()->Disable(RenderDevice::STENCIL_TEST);
}
