#pragma once

class GameObject;
class Component {
public:
    Component();
    virtual ~Component();
    virtual void OnEnable();
    virtual void Awake();
    virtual void Update();

    /// ��Ⱦ֮ǰ
    virtual void OnPreRender();
    /// ��Ⱦ֮��
    virtual void OnPostRender();

    virtual void OnDisable();
    GameObject* game_object() { return game_object_; }
    virtual void set_game_object(GameObject* game_object) { game_object_ = game_object; }
private:
    GameObject* game_object_;
};
