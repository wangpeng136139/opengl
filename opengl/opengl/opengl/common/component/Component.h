
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

    /// 渲染之前
    virtual void OnPreRender();
    /// 渲染之后
    virtual void OnPostRender();


    bool active() { return active_; }
    void set_active(bool active) { active_ = active; }

    virtual void OnDisable();
    GameObject* game_object() { return game_object_; }
    virtual void set_game_object(GameObject* game_object) { game_object_ = game_object; }
private:
    bool active_;//是否激活
    GameObject* game_object_;
};
#endif