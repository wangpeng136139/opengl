#include "SkinnedMeshRenderer.h"
#include <rttr/registration>
#include "../../component/GameObject.h"
#include "MeshFilter.h"
#include "../../animation/Animation.h"
#include "../../animation/AnimationClip.h"
#include "../../common/Debug.h"
#include <glm/glm.hpp>


using namespace rttr;
RTTR_REGISTRATION
{
registration::class_<SkinnedMeshRenderer>("SkinnedMeshRenderer")
.constructor<>()(rttr::policy::ctor::as_raw_ptr);
}

SkinnedMeshRenderer::SkinnedMeshRenderer() :MeshRenderer() {

}

SkinnedMeshRenderer::~SkinnedMeshRenderer()
{

}

void SkinnedMeshRenderer::Update() {
    //������ȡ MeshFilter ���
    auto component_mesh_filter = game_object()->GetComponent("MeshFilter");
    auto mesh_filter = dynamic_cast<MeshFilter*>(component_mesh_filter);
    if (!mesh_filter) {
        DEBUG_LOG_ERROR("SkinnedMeshRenderer::Update() failed, can't get MeshFilter component");
        return;
    }
    //��ȡ Mesh
    auto mesh = mesh_filter->GetMesh();
    if (!mesh) {
        DEBUG_LOG_ERROR("SkinnedMeshRenderer::Update() failed, can't get Mesh");
        return;
    }
    //��ȡ�������������Ϣ(4����������������Ȩ��)������Ϊ�������
    auto vertex_relate_bone_infos = mesh_filter->vertex_relate_bone_infos();
    if (!vertex_relate_bone_infos) {
        DEBUG_LOG_ERROR("SkinnedMeshRenderer::Update() failed, can't get vertex_relate_bone_infos");
        return;
    }

    //������ȡ Animation ���
    auto component_animation = game_object()->GetComponent("Animation");
    auto animation = dynamic_cast<Animation*>(component_animation);
    if (!animation) {
        DEBUG_LOG_ERROR("SkinnedMeshRenderer::Update() failed, can't get Animation component");
        return;
    }
    //��ȡ��ǰ���ŵ� AnimationClip
    auto animation_clip = animation->current_animation_clip();
    if (!animation_clip) {
        DEBUG_LOG_ERROR("SkinnedMeshRenderer::Update() failed, can't get current AnimationClip");
        return;
    }
    //��ȡ��ǰ֡���µĹ�������
    std::vector<glm::mat4>& bone_matrices = animation_clip->GetCurrentFrameBoneMatrix();
    //��ȡ SkinnedMesh
    Mesh* skinned_mesh = mesh_filter->skinned_mesh();
    if (skinned_mesh == nullptr) {
        //����Mesh����
        skinned_mesh = static_cast<Mesh*>(malloc(mesh->size()));
        memcpy(skinned_mesh, mesh, mesh->size());
        mesh_filter->set_skinned_mesh(skinned_mesh);

        //������������ vertex_data_
        skinned_mesh->vertex_data_ = static_cast<Vertex*>(malloc(mesh->vertex_num_ * sizeof(Vertex)));
        memcpy(skinned_mesh->vertex_data_, mesh->vertex_data_, mesh->vertex_num_ * sizeof(Vertex));
    }
    //���㵱ǰ֡����λ��
    for (int i = 0; i < skinned_mesh->vertex_num_; i++) {
        auto& vertex = mesh->vertex_data_[i];

        glm::vec4 pos_by_bones;//��ÿ��Bone����һ��λ�ã�Ȼ�����Ȩ�أ�������

        for (int j = 0; j < 4; j++) {
            auto& bone_index = vertex_relate_bone_infos[i].bone_index_[j];//��������Ĺ�������
            if (bone_index == -1) {
                continue;
            }
            float bone_weight = vertex_relate_bone_infos[i].bone_weight_[j] / 100.f;//��������Ĺ���Ȩ��

            //��ȡ��ǰ��������Ĺ���T-Pos����
            glm::mat4& bone_t_pose_matrix = animation_clip->GetBoneTPose(bone_index);
            //��ȡT-Pos����������
            glm::mat4 bone_t_pose_matrix_inverse = glm::inverse(bone_t_pose_matrix);
            //����������ת���������ռ�
            glm::vec4 vertex_position = bone_t_pose_matrix_inverse * glm::vec4(vertex.pos_, 1.0f);

            //��ǰ֡��������Ĺ�������
            auto& bone_matrix = bone_matrices[bone_index];
            //���㵱ǰ֡����λ��(ģ������ϵ��bone_matrix����������ģ������ϵ��λ�ã����õ���������ϵ��λ���ϣ�ss��ת������ģ������ϵ)
            glm::vec4 pos_in_world = bone_matrix * vertex_position;

            //����Ȩ��
            pos_by_bones = pos_by_bones + pos_in_world * bone_weight;
        }
        glm::vec3 vec3(pos_by_bones);
        skinned_mesh->vertex_data_[i].pos_ = vec3;
    }
}

