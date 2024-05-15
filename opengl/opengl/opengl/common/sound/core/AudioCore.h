#ifndef UNTITLED_AUDIOCORE_H
#define UNTITLED_AUDIOCORE_H
#include "fmod/api/core/inc/fmod.h"


class AudioCore {
public:
    /// ��ʼ��fmod
    static void Init();
    /// ������Ч
    /// \param name_or_data
    /// \param mode
    /// \param ex_info
    /// \param sound
    /// \return
    static FMOD_RESULT CreateSound(const char* name_or_data, FMOD_MODE mode, FMOD_CREATESOUNDEXINFO* ex_info, FMOD_SOUND** sound);

    /// ����sound��Ӧ����Ч
    /// \param sound
    /// \param channel_group
    /// \param paused
    /// \param channel
    /// \return
    static FMOD_RESULT PlaySound(FMOD_SOUND* sound, FMOD_CHANNELGROUP* channel_group, bool paused, FMOD_CHANNEL** channel);

    /// ˢ֡
    /// \return
    static FMOD_RESULT Update();

    static FMOD_RESULT Set3DListenerAttributes(int listener, const FMOD_VECTOR* pos, const FMOD_VECTOR* vel, const FMOD_VECTOR* forward, const FMOD_VECTOR* up);
private:
    static FMOD_SYSTEM* fmod_system_;//fmod��Ч����ϵͳ
};


#endif //UNTITLED_AUDIO_H
