#pragma once
#ifndef UNTITLED_AUDIOCLIP_H
#define UNTITLED_AUDIOCLIP_H

#include "AudioCore.h"
#include <string>

/// AudioClip hosts fmod sound
class AudioClip {
public:
    AudioClip();
    ~AudioClip();

    FMOD_SOUND* fmod_sound() { return fmod_sound_; }
public:
    /// ������Ч�ļ�������AudioClipʵ��,ע��Ĭ����2D���֡�
    /// \param audio_file_path
    /// \return
    static AudioClip* LoadFromFile(std::string audio_file_path);

private:
    FMOD_SOUND* fmod_sound_;
};


#endif //UNTITLED_AUDIOCLIP_H
