#pragma once

class GameObject;
class Component {
public:
     Component();
    ~Component();
    GameObject* game_object() { return game_object_; }
    virtual void set_game_object(GameObject* game_object) { game_object_ = game_object; }
private:
    GameObject* game_object_;
};
