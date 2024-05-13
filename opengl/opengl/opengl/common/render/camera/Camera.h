#pragma once
#include "glm/glm.hpp"
#include "../../component/Component.h"
#include <vector>
#include <functional>

class Camera : public Component
{
public:
    /// �������λ�� ����
    /// \param cameraFowrad �����ǰ����
    /// \param cameraUp ������Ϸ���
    void SetView(const glm::vec3& cameraFowrad, const glm::vec3& cameraUp);
    /// ���������Ұ
    /// \param fovDegrees   �����Ұ ���ӽǶ�
    /// \param aspectRatio  ��߱�
    /// \param nearClip ���ü���
    /// \param farClip  Զ�ü���
    void SetProjection(float fovDegrees, float aspectRatio, float nearClip, float farClip);


    glm::mat4& view_mat4() { return view_mat4_; }
    glm::mat4& projection_mat4() { return projection_mat4_; }

    /// ����������ɫ
    /// \param r
    /// \param g
    /// \param b
    /// \param a
    void set_clear_color(float r, float g, float b, float a) { clear_color_ = glm::vec4(r, g, b, a); }

    /// ����ˢ֡������������
    /// \param clear_flag
    void set_clear_flag(unsigned int clear_flag) { clear_flag_ = clear_flag; }

    void Clear();

    unsigned char culling_mask() { return culling_mask_; }
    void set_culling_mask(unsigned char culling_mask) { culling_mask_ = culling_mask; }

    Camera();

    ~Camera() override;

    /// ��������Camera
    /// \param func
    static void Foreach(std::function<void()> func);

    void set_depth(unsigned char depth);

    unsigned char depth(){return depth_;}
public:
    static void Sort();
    /// ����all_camera_ʱ���ֵ����Ǹ�Camera��
    /// \return
    static Camera* current_camera() { return current_camera_; }
private:
	glm::mat4 view_mat4_;//ָ���������ͳ���
	glm::mat4 projection_mat4_;//ָ�������Χ

	glm::vec4 clear_color_;//������ɫ
	unsigned int clear_flag_;//ˢ�����ݱ�־
    unsigned char depth_;//�������
    unsigned char culling_mask_;//�޳�
private:
    static std::vector<Camera*> all_camera_;
    static Camera* current_camera_;
};

