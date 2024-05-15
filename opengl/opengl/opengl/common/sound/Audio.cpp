#include "Audio.h"

#ifdef USE_FMOD_STUDIO
#include "./studio/AudioStudio.h"
#define AudioSolution AudioStudio
#else
#include "./core/AudioCore.h"
#define AudioSolution AudioCore
#endif

void Audio::Init() {
    AudioSolution::Init();
}

void Audio::Update() {
    AudioSolution::Update();
}
