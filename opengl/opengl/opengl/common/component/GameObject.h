#pragma once

#ifndef UNTITLED_GAME_OBJECT_H
#define UNTITLED_GAME_OBJECT_H

#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <memory>


class Component;
class GameObject {
public:
    GameObject();
    GameObject(std::string name);
    ~GameObject();

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

private:
    std::string name_;
    std::unordered_map<std::string, std::vector<Component*>> component_type_instance_map_;
};


#endif //UNTITLED_GAME_OBJECT_H
