#ifndef UNTITLED_MESH_MESH_H
#define UNTITLED_MESH_MESH_H

#include "../../render_base_head.h"
#include "../../component/Component.h"

//Mesh�ļ�ͷ
struct MeshFileHead {
    char type_[4];
    int vertex_num_;//�������
    int vertex_index_num_;//��������
    char name_[32];//����
};

/// �������������Ȩ��,ÿ�����������Թ���4��������
struct VertexRelateBoneInfo {
    char bone_index_[4];//����������һ���������128������char���С�
    char bone_weight_[4];//����Ȩ�أ�Ȩ�ز��ᳬ��100��������char���;Ϳ��ԡ�
};

//Mesh�ļ�
struct MeshFile {
    MeshFileHead head_;
    Vertex* vertex_;
    unsigned short* index_;

    MeshFile() {
        vertex_ = nullptr;
        index_ = nullptr;
    }

    ~MeshFile() {
        if (vertex_ != nullptr) {
            delete[] vertex_;
            vertex_ = nullptr;
        }
        if (index_ != nullptr) {
            delete[] index_;
            index_ = nullptr;
        }
    }

    // д���ļ�
    void Write(std::string filePath) {
        std::ofstream file(filePath, std::ios::binary);
        if (file.is_open()) {
            file.write(reinterpret_cast<char*>(&head_), sizeof(head_));
            file.write(reinterpret_cast<char*>(vertex_), sizeof(Vertex) * head_.vertex_num_);
            file.write(reinterpret_cast<char*>(index_), sizeof(unsigned short) * head_.vertex_index_num_);
            file.close();
        }
    }
};


//Mesh����
struct Mesh {
    unsigned short vertex_num_;//�������
    unsigned short vertex_index_num_;//��������
    Vertex* vertex_data_;//��������
    unsigned short* vertex_index_data_;//������������

    Mesh() {
        vertex_num_ = 0;
        vertex_index_num_ = 0;
        vertex_data_ = nullptr;
        vertex_index_data_ = nullptr;
    }

    ~Mesh() {
        if (vertex_data_ != nullptr) {
            delete[] vertex_data_;
            vertex_data_ = nullptr;
        }
        if (vertex_index_data_ != nullptr) {
            delete[] vertex_index_data_;
            vertex_index_data_ = nullptr;
        }
    }

    /// ��ȡ�ֽ���
    unsigned short size() {
        auto total_bytes_ = sizeof(vertex_num_) + vertex_num_ * sizeof(Vertex) + sizeof(vertex_index_num_) + vertex_index_num_ * sizeof(unsigned short);
        return total_bytes_;
    }
};

#endif
