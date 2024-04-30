#include "Camera.h"
#include <rttr/registration>
#include "../../component/Transform.h"
#include "../../component/GameObject.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/glm.hpp>

#define GLM_ENABLE_EXPERIMENTAL
#include<glm/gtx/transform2.hpp>
#include<glm/gtx/euler_angles.hpp>


#include <glad/glad.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

using namespace rttr;
RTTR_REGISTRATION//×¢²á·´Éä
{
    registration::class_<Camera>("Camera")
            .constructor<>()(rttr::policy::ctor::as_raw_ptr);
}

std::vector<Camera*> Camera::all_camera_;
Camera* Camera::current_camera_;
Camera::Camera() :clear_color_(49.f / 255, 77.f / 255, 121.f / 255, 1.f), clear_flag_(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT), culling_mask_(0x01) {
    all_camera_.push_back(this);
}


Camera::~Camera() {
    auto iter = std::find(all_camera_.begin(), all_camera_.end(), this);
    if (iter != all_camera_.end()) {
        all_camera_.erase(iter);
    }
}

void Camera::Foreach(std::function<void()> func) {
    for (auto iter = all_camera_.begin(); iter != all_camera_.end(); iter++) {
        current_camera_ = *iter;
        current_camera_->Clear();
        func();
    }
}


void Camera::set_depth(unsigned char depth) {
    if (depth_ == depth) {
        return;
    }
    depth_ = depth;
    Sort();
}
/// °´ depth_ ÅÅÐò
void Camera::Sort() {
    std::sort(all_camera_.begin(), all_camera_.end(), [](Camera* a, Camera* b) {
        return a->depth() < b->depth();
        });
}


void Camera::SetView(const glm::vec3& cameraForward, const glm::vec3& cameraUp) {
    auto transform = dynamic_cast<Transform*>(game_object()->GetComponent("Transform"));
    view_mat4_ = glm::lookAt(transform->position(), cameraForward, cameraUp);
}

void Camera::SetProjection(float fovDegrees, float aspectRatio, float nearClip, float farClip) {
    projection_mat4_ = glm::perspective(glm::radians(fovDegrees), aspectRatio, nearClip, farClip);
}

void Camera::Clear() {
    glClear(clear_flag_);
    glClearColor(clear_color_.r, clear_color_.g, clear_color_.b, clear_color_.a);
}