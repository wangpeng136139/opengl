#ifndef UNTITLED_ANIMATION_CLIP_H
#define UNTITLED_ANIMATION_CLIP_H
#include <vector>
#include <string>
#include <unordered_map>
#include <glm/glm.hpp>

/// ��������Ƭ��
class AnimationClip {
public:
    AnimationClip();
    ~AnimationClip();

    /// ���ض���Ƭ��
    /// \param file_path
    void LoadFromFile(const char* file_path);

    /// ��ȡ����ʱ��
    float duration() {
        return this->duration_;
    }

    /// ��ȡ����T-pose
    /// \param bone_index ����index
    /// \return ����T-pose
    glm::mat4& GetBoneTPose(unsigned char bone_index);

    /// ��ȡ��ǰ֡���µĹ�������
    std::vector<glm::mat4>& GetCurrentFrameBoneMatrix();

public:
    /// ���Ź�������
    void Play();

    /// ˢ֡�����㵱ǰʱ��������֡
    void Update();

    /// ֹͣ����
    void Stop();

private:
    /// Ԥ�����������
    void Bake();

    /// �ݹ�����������,�Ӹ��ڵ㿪ʼ��Blender������ʱ��Ҫȷ���ȵ������ڵ㡣
    /// \param bone_name
    /// \param parent_matrix
    /// \param bone_matrix
    void CalculateBoneMatrix(std::vector<glm::mat4>& current_frame_bone_matrices, unsigned short bone_index, const glm::mat4& parent_matrix);

private:
    /// ���й�������
    std::vector<std::string> bone_names_;
    /// �������ӽڵ�  
    std::vector<std::vector<unsigned short>> bone_children_vector_;
    /// ����T-pose
    std::vector<glm::mat4> bone_t_pose_vector_;
    /// ����ʱ��
    float duration_ = 0.0f;
    /// ��֡��
    unsigned short frame_count_ = 0;
    /// ÿһ֡ÿһ��������λ�ƾ���
    std::vector<std::vector<glm::mat4>> bone_matrix_frames_vector_;
    /// ����������ʼ����ʱ��
    float start_time_ = 0.0f;
    /// ���������Ƿ��ڲ���
    bool is_playing_ = false;
    /// ��ǰ֡
    unsigned short current_frame_ = 0;
};


#endif //UNTITLED_ANIMATION_CLIP_H