#pragma once
#ifndef UNTITLED_ANIMATION_H
#define UNTITLED_ANIMATION_H

#include <unordered_map>
#include <string>
#include "../component/Component.h"


class AnimationClip;
/// ��������
class Animation :public Component {
public:
    Animation();
    ~Animation();

    /// ���� skeleton_anim �ļ�
    /// \param path skeleton_anim �ļ�·��
    /// \param alias_name �����������������һ���������������
    void LoadAnimationClipFromFile(const char* path, const char* alias_name);

    /// ���Ŷ���
    /// \param alias_name ��������
    void Play(const char* alias_name);

    /// ��ȡ��ǰ���ŵĶ���
    AnimationClip* current_animation_clip() const { return current_animation_clip_; }

public:
    // ˢ֡
    void Update() override;

private:
    /// �����б�
    std::unordered_map<std::string, AnimationClip*> animation_clips_map_;
    /// ��ǰ���ŵĶ���
    AnimationClip* current_animation_clip_;
};


#endif //UNTITLED_ANIMATION_H