
#ifndef UNTITLED_GAME_COMPONENT_H
#define UNTITLED_GAME_COMPONENT_H
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


    bool active() { return active_; }
    void set_active(bool active) { active_ = active; }

    virtual void OnDisable();
    GameObject* game_object() { return game_object_; }
    virtual void set_game_object(GameObject* game_object) { game_object_ = game_object; }
private:
    bool active_;//�Ƿ񼤻�
    GameObject* game_object_;
};
#endif