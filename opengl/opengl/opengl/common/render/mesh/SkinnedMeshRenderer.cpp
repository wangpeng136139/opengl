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
    //主动获取 MeshFilter 组件
    auto component_mesh_filter = game_object()->GetComponent("MeshFilter");
    auto mesh_filter = dynamic_cast<MeshFilter*>(component_mesh_filter);
    if (!mesh_filter) {
        DEBUG_LOG_ERROR("SkinnedMeshRenderer::Update() failed, can't get MeshFilter component");
        return;
    }
    //获取 Mesh
    auto mesh = mesh_filter->GetMesh();
    if (!mesh) {
        DEBUG_LOG_ERROR("SkinnedMeshRenderer::Update() failed, can't get Mesh");
        return;
    }
    //获取顶点关联骨骼信息(4个骨骼索引、骨骼权重)，长度为顶点个数
    auto vertex_relate_bone_infos = mesh_filter->vertex_relate_bone_infos();
    if (!vertex_relate_bone_infos) {
        DEBUG_LOG_ERROR("SkinnedMeshRenderer::Update() failed, can't get vertex_relate_bone_infos");
        return;
    }

    //主动获取 Animation 组件
    auto component_animation = game_object()->GetComponent("Animation");
    auto animation = dynamic_cast<Animation*>(component_animation);
    if (!animation) {
        DEBUG_LOG_ERROR("SkinnedMeshRenderer::Update() failed, can't get Animation component");
        return;
    }
    //获取当前播放的 AnimationClip
    auto animation_clip = animation->current_animation_clip();
    if (!animation_clip) {
        DEBUG_LOG_ERROR("SkinnedMeshRenderer::Update() failed, can't get current AnimationClip");
        return;
    }
    //获取当前帧最新的骨骼矩阵
    std::vector<glm::mat4>& bone_matrices = animation_clip->GetCurrentFrameBoneMatrix();
    //获取 SkinnedMesh
    Mesh* skinned_mesh = mesh_filter->skinned_mesh();
    if (skinned_mesh == nullptr) {
        //拷贝Mesh整体
        skinned_mesh = static_cast<Mesh*>(malloc(mesh->size()));
        memcpy(skinned_mesh, mesh, mesh->size());
        mesh_filter->set_skinned_mesh(skinned_mesh);

        //拷贝顶点数据 vertex_data_
        skinned_mesh->vertex_data_ = static_cast<Vertex*>(malloc(mesh->vertex_num_ * sizeof(Vertex)));
        memcpy(skinned_mesh->vertex_data_, mesh->vertex_data_, mesh->vertex_num_ * sizeof(Vertex));
    }
    //计算当前帧顶点位置
    for (int i = 0; i < skinned_mesh->vertex_num_; i++) {
        auto& vertex = mesh->vertex_data_[i];

        glm::vec4 pos_by_bones;//对每个Bone计算一次位置，然后乘以权重，最后求和

        for (int j = 0; j < 4; j++) {
            auto& bone_index = vertex_relate_bone_infos[i].bone_index_[j];//顶点关联的骨骼索引
            if (bone_index == -1) {
                continue;
            }
            float bone_weight = vertex_relate_bone_infos[i].bone_weight_[j] / 100.f;//顶点关联的骨骼权重

            //获取当前顶点关联的骨骼T-Pos矩阵
            glm::mat4& bone_t_pose_matrix = animation_clip->GetBoneTPose(bone_index);
            //获取T-Pos矩阵的逆矩阵
            glm::mat4 bone_t_pose_matrix_inverse = glm::inverse(bone_t_pose_matrix);
            //将顶点坐标转换到骨骼空间
            glm::vec4 vertex_position = bone_t_pose_matrix_inverse * glm::vec4(vertex.pos_, 1.0f);

            //当前帧顶点关联的骨骼矩阵
            auto& bone_matrix = bone_matrices[bone_index];
            //计算当前帧顶点位置(模型坐标系，bone_matrix里带了相对于模型坐标系的位置，作用到骨骼坐标系的位置上，ss就转换到了模型坐标系)
            glm::vec4 pos_in_world = bone_matrix * vertex_position;

            //乘以权重
            pos_by_bones = pos_by_bones + pos_in_world * bone_weight;
        }
        glm::vec3 vec3(pos_by_bones);
        skinned_mesh->vertex_data_[i].pos_ = vec3;
    }
}

