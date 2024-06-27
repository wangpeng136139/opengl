

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

    /// ������
    /// \param component_type_name �������
    /// \return
    Component* AddComponent(std::string component_type_name);

    
    template <class T = Component> T* AddComponent();

    /// �������ʵ��
    /// \param component_instance_table
    void AttachComponent(Component* component);
    /// ��ȡ���    
    /// \param component_type_name �������
    /// \return
    Component* GetComponent(std::string component_type_name);

    /// ��ȡ����ͬ�����
    /// \param component_type_name �������
    /// \return
    std::vector<Component*>& GetComponents(std::string component_type_name);

    void ForeachComponent(std::function<void(Component* component)> func);
    unsigned char layer() { return layer_; }
    void set_layer(unsigned char layer) { layer_ = layer; }
    bool active() { return active_; }
    void set_active(bool active) { active_ = active; }



    /// ��ȡ�����������C++�С�
    /// \tparam T �������
    /// \return ���ʵ��
    template <class T = Component>
    T* GetComponent() {
        //��ȡ����
        type t = type::get<T>();
        std::string component_type_name = t.get_name().to_string();
        std::vector<Component*> component_vec;

        if (component_type_instance_map_.find(component_type_name) != component_type_instance_map_.end()) {
            component_vec = component_type_instance_map_[component_type_name];
        }
        if (component_vec.size() == 0) {
            //û���ҵ����,��ȥ�����������
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
    unsigned char layer_;//������ֲ�ͬ�Ĳ㣬��������ֲ㡢������ײ�ֲ�ȡ�
    std::string name_;
    std::unordered_map<std::string, std::vector<Component*>> component_type_instance_map_;
    bool active_;//�Ƿ񼤻�
public:
    /// ��������Camera
    /// \param func
    static void Foreach(std::function<void(GameObject* game_object)> func);
private:
    static std::list<GameObject*> game_object_list_;
    
};


#endif //UNTITLED_GAME_OBJECT_H
