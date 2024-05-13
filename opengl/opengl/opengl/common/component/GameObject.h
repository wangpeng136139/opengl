#pragma once

#ifndef UNTITLED_GAME_OBJECT_H
#define UNTITLED_GAME_OBJECT_H

#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <memory>
#include <list>
#include <functional>


class Component;
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

    template <class T>
    T* AddComponent();

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
private:
    unsigned char layer_;//������ֲ�ͬ�Ĳ㣬��������ֲ㡢������ײ�ֲ�ȡ�
    std::string name_;
    std::unordered_map<std::string, std::vector<Component*>> component_type_instance_map_;
public:
    /// ��������Camera
    /// \param func
    static void Foreach(std::function<void(GameObject* game_object)> func);
private:
    static std::list<GameObject*> game_object_list_;
    
};


#endif //UNTITLED_GAME_OBJECT_H
