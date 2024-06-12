#pragma once
#include "../vertex/Vertex.h"
//Mesh�ļ�ͷ
struct MeshFileHead {
    char type_[4];
    int vertex_num_;//�������
    int vertex_index_num_;//��������
};

/// �������������Ȩ��,ÿ�����������Թ���4��������
struct VertexRelateBoneInfo {
    char bone_index_[4];//����������һ���������128������char���С�
    char bone_weight_[4];//����Ȩ�أ�Ȩ�ز��ᳬ��100��������char���;Ϳ��ԡ�
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

