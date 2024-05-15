//
// Created by captainchen on 2021/8/10.
//

#ifndef UNTITLED_AUDIO_STUDIO_H
#define UNTITLED_AUDIO_STUDIO_H

#include <iostream>
#include "fmod/api/core/inc/fmod.h"
#include "fmod/api/studio/inc/fmod_studio.h"
#include "AudioStudioEvent.h"

using namespace std;

class AudioStudio {
public:
    /// ��ʼ��FMOD Studio
    /// \return
    static FMOD_RESULT Init();

    /// ˢ֡
    /// \return
    static FMOD_RESULT Update();

    /// ���� bank �ļ�
    /// \param file_name
    /// \return
    static FMOD_RESULT LoadBankFile(string file_name);

    /// ��ȡEventʵ�������û�оʹ�����
    /// \param event_path
    /// \return
    static AudioStudioEvent* CreateEventInstance(const char* event_path);

    /// ������������
    /// \param x
    /// \param y
    /// \param z
    static void setListenerAttributes(float x, float y, float z);

private:
    static FMOD_STUDIO_SYSTEM* system_;
};


#endif //UNTITLED_AUDIO_STUDIO_H
