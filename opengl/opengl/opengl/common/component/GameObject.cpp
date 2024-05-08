
#include "GameObject.h"
#include "Component.h"
#include <rttr/registration>
using namespace rttr;   

std::list<GameObject*> GameObject::game_object_list_;

GameObject::GameObject() :layer_(0x01) {
    game_object_list_.push_back(this);
}
   
GameObject::GameObject(std::string name) :GameObject(){
    set_name(name);
}

GameObject::~GameObject() {

}

template <class T>
T* GameObject::AddComponent() {
    T* component = new T();
    rttr::type t = rttr::type::get(*component);
    std::string component_type_name = t.get_name().to_string();
    component->set_game_object(this);
    if (component_type_instance_map_.find(component_type_name) == component_type_instance_map_.end()) {
        std::vector<Component*> component_vec;
        component_vec.push_back(component);
        component_type_instance_map_[component_type_name] = component_vec;
    }
    else {
        component_type_instance_map_[component_type_name].push_back(component);
    }
    return component;
}

Component* GameObject::AddComponent(std::string component_type_name) {
    type t = type::get_by_name(component_type_name.c_str());
    rttr::variant var = t.create();    // 创建实例
    Component* component = var.get_value<Component*>();
    component->set_game_object(this);

    if (component_type_instance_map_.find(component_type_name) == component_type_instance_map_.end()) {
        std::vector<Component*> component_vec;
        component_vec.push_back(component);
        component_type_instance_map_[component_type_name] = component_vec;
    }   
    else {
        component_type_instance_map_[component_type_name].push_back(component);
    }
    return component;
}


std::vector<Component*>& GameObject::GetComponents(std::string component_type_name) {
    return component_type_instance_map_[component_type_name];
}



/// 遍历所有Component
/// \param func
void GameObject::ForeachComponent(std::function<void(Component* component)> func)
{
    for (auto& v : component_type_instance_map_) {
        for (auto& iter : v.second) {
            Component* component = iter;
            func(component);
        }
    }
}

void GameObject::Foreach(std::function<void(GameObject* game_object)> func) {
    for (auto iter = game_object_list_.begin(); iter != game_object_list_.end(); iter++) {
        auto game_object = *iter;
        func(game_object);
    }
}



Component* GameObject::GetComponent(std::string component_type_name) {
    if (component_type_instance_map_.size() < 1)
    {
        return nullptr;
    }
   auto it = component_type_instance_map_.find(component_type_name);
    if (component_type_instance_map_.find(component_type_name) == component_type_instance_map_.end()) {
        return nullptr;
    }
    if (component_type_instance_map_[component_type_name].size() == 0) {
        return nullptr;
    }
    return component_type_instance_map_[component_type_name][0];
}
