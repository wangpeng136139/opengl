#include "AudioStudioEvent.h"
//
// Created by captainchen on 2021/8/10.
//
#include "../../Component/GameObject.h"
#include "../../Component/Transform.h"
#include "../../common/Debug.h"

//    //按键盘1、2、3设置参数值，切换不同的地面类型，播放不同的脚步声
//if (Input::GetKeyUp(KEY_CODE_1)) {
//    audio_studio_event_->SetParameterByName("groundtype", 0.0f);
//}
//else if (Input::GetKeyUp(KEY_CODE_2)) {
//    audio_studio_event_->SetParameterByName("groundtype", 1.0f);
//}
//else if (Input::GetKeyUp(KEY_CODE_3)) {
//    audio_studio_event_->SetParameterByName("groundtype", 2.0f);
//}

 //设置听者位置
//glm::mat4 rotate_mat4 = glm::rotate(glm::mat4(1.0f), glm::radians(Time::delta_time() * 60), glm::vec3(0.0f, 0.0f, 1.0f));
//glm::vec4 old_pos = glm::vec4(transform_player_->position(), 1.0f);
//glm::vec4 new_pos = rotate_mat4 * old_pos;//旋转矩阵 * 原来的坐标 = 以零点做旋转。
//transform_player_->set_position(glm::vec3(new_pos));
//auto player_pos = transform_player_->position();
//AudioStudio::setListenerAttributes(player_pos.x, player_pos.y, player_pos.z);


AudioStudioEvent::AudioStudioEvent() {}
AudioStudioEvent::~AudioStudioEvent() {}


FMOD_RESULT AudioStudioEvent::SetParameterByName(const char* name, float value, bool ignore_seek_speed) {
    return FMOD_Studio_EventInstance_SetParameterByName(event_instance_, name, value, ignore_seek_speed);
}

FMOD_RESULT AudioStudioEvent::Set3DAttribute(float x, float y, float z) {

    FMOD_3D_ATTRIBUTES attributes = { { x,y,z } };
    return FMOD_Studio_EventInstance_Set3DAttributes(event_instance_, &attributes);
}

void AudioStudioEvent::Start() {
    if (event_instance_ == nullptr) {
        DEBUG_LOG_ERROR("event_instance_== nullptr");
        return;
    }
    FMOD_RESULT result = FMOD_Studio_EventInstance_Start(event_instance_);
    if (result != FMOD_OK) {
        DEBUG_LOG_ERROR("FMOD_Studio_EventInstance_Start result:{}", result);
        return;
    }
}

void AudioStudioEvent::Pause() {
    if (event_instance_ == nullptr) {
        DEBUG_LOG_ERROR("event_instance_== nullptr");
        return;
    }
    FMOD_RESULT result = FMOD_Studio_EventInstance_SetPaused(event_instance_, true);
    if (result != FMOD_OK) {
        DEBUG_LOG_ERROR("FMOD_Studio_EventInstance_SetPaused result:{}", result);
        return;
    }
}

void AudioStudioEvent::Stop() {
    if (event_instance_ == nullptr) {
        DEBUG_LOG_ERROR("event_instance_== nullptr");
        return;
    }
    FMOD_RESULT result = FMOD_Studio_EventInstance_Stop(event_instance_, FMOD_STUDIO_STOP_MODE::FMOD_STUDIO_STOP_IMMEDIATE);
    if (result != FMOD_OK) {
        DEBUG_LOG_ERROR("FMOD_Studio_EventInstance_Stop result:{}", result);
        return;
    }
}
