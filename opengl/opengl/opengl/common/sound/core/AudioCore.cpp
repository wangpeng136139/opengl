
#include "AudioCore.h"
#include <fmod/api/core/inc/fmod.h>
#include "spdlog/spdlog.h"

FMOD_SYSTEM* AudioCore::fmod_system_;

void AudioCore::Init() {  
    FMOD_RESULT       result;
    // ����FMOD Systemʵ��
    result = FMOD_System_Create(&fmod_system_);
    spdlog::info("FMOD::System_Create ret code {}", result);
    //��ȡ�汾��
    unsigned int      version;
    result = FMOD_System_GetVersion(fmod_system_, &version);
    spdlog::info("FMOD_System_GetVersion ret code {}", result);
    if (version < FMOD_VERSION) {
        spdlog::critical("FMOD lib version {} doesn't match header version {}", version, FMOD_VERSION);
        return;
    }
    //��ʼ�� ϵͳ
    result = FMOD_System_Init(fmod_system_, 32, FMOD_INIT_NORMAL, 0);
    spdlog::info("FMOD_System_Init ret code {}", result);
}


FMOD_RESULT AudioCore::Update() {
    return FMOD_System_Update(fmod_system_);
}

FMOD_RESULT
AudioCore::CreateSound(const char* name_or_data, FMOD_MODE mode, FMOD_CREATESOUNDEXINFO* ex_info, FMOD_SOUND** sound) {
    return FMOD_System_CreateSound(fmod_system_, name_or_data, mode, ex_info, sound);
}


FMOD_RESULT AudioCore::PlaySound(FMOD_SOUND* sound, FMOD_CHANNELGROUP* channel_group, bool paused, FMOD_CHANNEL** channel) {
    return FMOD_System_PlaySound(fmod_system_, sound, channel_group, paused, channel);
}

FMOD_RESULT
AudioCore::Set3DListenerAttributes(int listener, const FMOD_VECTOR* pos, const FMOD_VECTOR* vel, const FMOD_VECTOR* forward,
    const FMOD_VECTOR* up) {
    return FMOD_System_Set3DListenerAttributes(fmod_system_, listener, pos, vel, forward, up);
}
