#include "AudioSource.h"
#include <rttr/registration>
#include "spdlog/spdlog.h"
#include "../../component/GameObject.h"
#include "../../component/Transform.h"

using namespace rttr;
RTTR_REGISTRATION
{
registration::class_<AudioSource>("AudioSource")
.constructor<>()(rttr::policy::ctor::as_raw_ptr);
}

AudioSource::AudioSource() :Component() {}

void AudioSource::Set3DMode(bool mode_3d) {
    if (mode_3d) {
        fmod_mode_ = fmod_mode_ | FMOD_3D;
    }
    else {
        if (fmod_mode_ & FMOD_3D) {
            fmod_mode_ = fmod_mode_ ^ FMOD_3D;
        }
    }
    FMOD_RESULT result = FMOD_Channel_SetMode(fmod_channel_, fmod_mode_);
    if (result != FMOD_OK) {
        spdlog::error("AudioSource::Set3DMode FMOD_Channel_SetMode result:{}", result);
    }
}

void AudioSource::Play() {
    if (audio_clip_ == nullptr) {
        spdlog::error("AudioSource::Play audio_clip_== nullptr");
        return;
    }
    if (audio_clip_->fmod_sound() == nullptr) {
        spdlog::error("AudioSource::Play audio_clip_->fmod_sound()==nullptr");
        return;
    }
    FMOD_RESULT result;
    FMOD_BOOL paused = false;
    //�ж���Ч�Ƿ���ͣ
    result = FMOD_Channel_GetPaused(fmod_channel_, &paused);//��Ч������Ϻ�channel�����գ����� FMOD_ERR_INVALID_HANDLE
    switch (result) {
    case FMOD_OK:
        if (paused) {
            result = FMOD_Channel_SetPaused(fmod_channel_, false);
        }
        break;
    case FMOD_ERR_INVALID_PARAM://channelĬ����nullptr���Ƿ�������
    case FMOD_ERR_INVALID_HANDLE://��Ч������Ϻ�channel�����ա�
    case FMOD_ERR_CHANNEL_STOLEN://��Ч������Ϻ�channel�������ұ����������Sound��
        //������Ч
        result = AudioCore::PlaySound(audio_clip_->fmod_sound(), nullptr, false, &fmod_channel_);
        break;
    default:
        break;
    }
}

void AudioSource::Pause() {
    FMOD_RESULT result;
    FMOD_BOOL paused = false;
    //�ж���Ч�Ƿ���ͣ
    result = FMOD_Channel_GetPaused(fmod_channel_, &paused);//��Ч������Ϻ�channel�����գ����� FMOD_ERR_INVALID_HANDLE
    if (result == FMOD_OK) {
        if (!paused) {
            result = FMOD_Channel_SetPaused(fmod_channel_, true);//��ͣ����
        }
        return;
    }
    spdlog::error("AudioSource::Paused FMOD_Channel_GetPaused result:{}", result);
}

void AudioSource::Stop() {
    FMOD_RESULT result;
    FMOD_BOOL paused = false;
    result = FMOD_Channel_Stop(fmod_channel_);
    if (result == FMOD_OK) {
        return;
    }
    spdlog::error("AudioSource::Stop FMOD_Channel_Stop result:{}", result);
}

bool AudioSource::Paused() {
    FMOD_RESULT result;
    FMOD_BOOL paused = false;
    //�ж���Ч�Ƿ���ͣ
    result = FMOD_Channel_GetPaused(fmod_channel_, &paused);//��Ч������Ϻ�channel�����գ����� FMOD_ERR_INVALID_HANDLE
    if (result == FMOD_OK) {
        return paused;
    }
    spdlog::error("AudioSource::Paused FMOD_Channel_GetPaused result:{}", result);
    return true;
}

void AudioSource::SetLoop(bool mode_loop) {
    if (mode_loop) {
        fmod_mode_ = fmod_mode_ | FMOD_LOOP_NORMAL;
    }
    else {
        if (fmod_mode_ & FMOD_LOOP_NORMAL) {
            fmod_mode_ = fmod_mode_ ^ FMOD_LOOP_NORMAL;
        }
    }

    FMOD_RESULT result = FMOD_Channel_SetMode(fmod_channel_, fmod_mode_);
    if (result != FMOD_OK) {
        spdlog::error("AudioSource::SetLoop FMOD_Channel_SetMode result:{}", result);
    }
}

void AudioSource::Update() {
    Component::Update();

    if (fmod_mode_ ^ FMOD_3D) {
        auto component_transform = game_object()->GetComponent("Transform");
        auto transform = dynamic_cast<Transform*>(component_transform);
        if (!transform) {
            return;
        }
        auto pos = transform->position();
        FMOD_VECTOR audio_source_pos = { pos.x, pos.y, pos.z };
        FMOD_VECTOR vel = { 0.0f, 0.0f, 0.0f };
        FMOD_Channel_Set3DAttributes(fmod_channel_, &audio_source_pos, &vel);
    }
}
