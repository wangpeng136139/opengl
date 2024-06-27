#include "MeshRenderer.h"
#include <rttr/registration>
#include "../camera/Camera.h"

#define GLM_ENABLE_EXPERIMENTAL
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtx/transform2.hpp>
#include<glm/gtx/euler_angles.hpp>
#include "../../../common/renderqueue/GPUResourceMapper.h";
#include "../../../common/renderqueue/RenderTaskProducer.h"
#include <glad/glad.h>

using namespace rttr;
RTTR_REGISTRATION
{
registration::class_<MeshRenderer>("MeshRenderer")
.constructor<>()(rttr::policy::ctor::as_raw_ptr);
}


MeshRenderer::MeshRenderer() {

}

MeshRenderer::~MeshRenderer() {

}


void MeshRenderer::SetMaterial(Material* material) {
    material_ = material;
}



void MeshRenderer::Render() {
    //�ӵ�ǰCamera��ȡView Projection
    auto current_camera = Camera::current_camera();
    if (current_camera == nullptr) {
        return;
    }
    //�ж������ culling_mask �Ƿ������ǰ���� layer
    if ((current_camera->culling_mask() & game_object()->layer()) == 0x00) {
        return;
    }


    glm::mat4 view = current_camera->view_mat4();
    glm::mat4 projection = current_camera->projection_mat4();

    //������ȡ Transform ���������mvp��
    auto component_transform = game_object()->GetComponent<Transform>();
    auto transform = dynamic_cast<Transform*>(component_transform);
    if (!transform) {
        return;
    }

    glm::mat4 trans = glm::translate(transform->position());
    auto rotation = transform->rotation();
    glm::mat4 eulerAngleYXZ = glm::eulerAngleYXZ(glm::radians(rotation.y), glm::radians(rotation.x), glm::radians(rotation.z));
    glm::mat4 scale = glm::scale(transform->scale()); //����;
    glm::mat4 model = trans * scale * eulerAngleYXZ;
    glm::mat4 mvp = projection * view * model;

    //������ȡ MeshFilter ���
    auto component_meshfilter = game_object()->GetComponent("MeshFilter");
    auto mesh_filter = dynamic_cast<MeshFilter*>(component_meshfilter);
    if (!mesh_filter) {
        return;
    }   
    //��������Ƥ������Чʱ����Ⱦ������ƤMesh
   Mesh* mesh = mesh_filter->skinned_mesh() == nullptr ? mesh_filter->GetMesh() : mesh_filter->skinned_mesh();
   //ָ��Ŀ��Shader����
   auto shader = material_->shader();
    //��ȡ`Shader`��`gl_program_id`��ָ��ΪĿ��Shader����
    GLuint shader_program_handle = material_->shader()->GetProgramId();
    if (vertex_array_object_handle_ == 0) {
        vertex_array_object_handle_ = GPUResourceMapper::GenerateVAOHandle();
        vertex_buffer_object_handle_ = GPUResourceMapper::GenerateVBOHandle();
        //�������񣺴���VAO
        RenderTaskProducer::ProduceRenderTaskCreateVAO(shader_program_handle, vertex_array_object_handle_, vertex_buffer_object_handle_, mesh->vertex_num_ * sizeof(Vertex), sizeof(Vertex), mesh->vertex_data_, mesh->vertex_index_num_ * sizeof(unsigned short), mesh->vertex_index_data_);
    }
    else {
        //�������񣺸���VBO
        RenderTaskProducer::ProduceRenderTaskUpdateVBOSubData(vertex_buffer_object_handle_, mesh->vertex_num_ * sizeof(Vertex), mesh->vertex_data_);
    }

    shader->Active();
    {
        // PreRender
        game_object()->ForeachComponent([](Component* component) {
            component->OnPreRender();
            });

        if (current_camera->camera_use_for() == Camera::CameraUseFor::SCENE) {
            RenderTaskProducer::ProduceRenderTaskSetEnableState(GL_DEPTH_TEST, true);
        }
        else {
            RenderTaskProducer::ProduceRenderTaskSetEnableState(GL_DEPTH_TEST, false);
        }
        RenderTaskProducer::ProduceRenderTaskSetEnableState(GL_CULL_FACE, true);
        RenderTaskProducer::ProduceRenderTaskSetEnableState(GL_BLEND, true);
        RenderTaskProducer::ProduceRenderTaskSetBlenderFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        //�ϴ�mvp����
        RenderTaskProducer::ProduceRenderTaskSetUniformMatrix4fv(shader_program_handle, "u_mvp", false, mvp);

        //��Pass�ڵ��õ������Texture
        std::vector<std::pair<std::string, Texture2D*>> textures = material_->textures();
        for (int texture_index = 0; texture_index < textures.size(); ++texture_index) {
            //��������Ԫ,�����ص�ͼƬ���������󶨵�����Ԫ�ϡ�
            RenderTaskProducer::ProduceRenderTaskActiveAndBindTexture(GL_TEXTURE0 + texture_index, textures[texture_index].second->texture_handle_);
            //����Shader���������Ԫ��ȡ��ɫ����
            RenderTaskProducer::ProduceRenderTaskSetUniform1i(shader_program_handle, textures[texture_index].first.c_str(), texture_index);
        }
        // ��VAO������
        RenderTaskProducer::ProduceRenderTaskBindVAOAndDrawElements(vertex_array_object_handle_, mesh->vertex_index_num_);

        // PostRender
        game_object()->ForeachComponent([](Component* component) {
            component->OnPostRender();
            });
    }
}

