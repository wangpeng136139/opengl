

#ifndef UNTITLED_GAME_OBJECT_H
#define UNTITLED_GAME_OBJECT_H

#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <memory>
#include <list>
#include <functional>
#include "Component.h"

class GameObject {
public:
    GameObject();
    GameObject(std::string name);
    virtual ~GameObject();

    std::string& name() { return name_; }
    void set_name(std::string name) { name_ = name; }

    /// 添加组件
    /// \param component_type_name 组件类名
    /// \return
    Component* AddComponent(std::string component_type_name);

    
    template <class T = Component> T* AddComponent();

    /// 附加组件实例
    /// \param component_instance_table
    void AttachComponent(Component* component);
    /// 获取组件    
    /// \param component_type_name 组件类名
    /// \return
    Component* GetComponent(std::string component_type_name);

    /// 获取所有同名组件
    /// \param component_type_name 组件类名
    /// \return
    std::vector<Component*>& GetComponents(std::string component_type_name);

    void ForeachComponent(std::function<void(Component* component)> func);
    unsigned char layer() { return layer_; }
    void set_layer(unsigned char layer) { layer_ = layer; }
    bool active() { return active_; }
    void set_active(bool active) { active_ = active; }



    /// 获取组件，仅用于C++中。
    /// \tparam T 组件类型
    /// \return 组件实例
    template <class T = Component>
    T* GetComponent() {
        //获取类名
        type t = type::get<T>();
        std::string component_type_name = t.get_name().to_string();
        std::vector<Component*> component_vec;

        if (component_type_instance_map_.find(component_type_name) != component_type_instance_map_.end()) {
            component_vec = component_type_instance_map_[component_type_name];
        }
        if (component_vec.size() == 0) {
            //没有找到组件,就去查找子类组件
            auto derived_classes = t.get_derived_classes();
            for (auto derived_class : derived_classes) {
                std::string derived_class_type_name = derived_class.get_name().to_string();
                if (component_type_instance_map_.find(derived_class_type_name) != component_type_instance_map_.end()) {
                    component_vec = component_type_instance_map_[derived_class_type_name];
                    if (component_vec.size() != 0) {
                        break;
                    }
                }
            }
        }
        if (component_vec.size() == 0) {
            return nullptr;
        }
        return dynamic_cast<T*>(component_vec[0]);
    }


private:
    unsigned char layer_;//将物体分不同的层，用于相机分层、物理碰撞分层等。
    std::string name_;
    std::unordered_map<std::string, std::vector<Component*>> component_type_instance_map_;
    bool active_;//是否激活
public:
    /// 遍历所有Camera
    /// \param func
    static void Foreach(std::function<void(GameObject* game_object)> func);
private:
    static std::list<GameObject*> game_object_list_;
    
};


#endif //UNTITLED_GAME_OBJECT_H
