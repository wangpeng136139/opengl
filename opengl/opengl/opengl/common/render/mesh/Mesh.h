#pragma once
#include "../vertex/Vertex.h"
//Mesh文件头
struct MeshFileHead {
    char type_[4];
    int vertex_num_;//顶点个数
    int vertex_index_num_;//索引个数
};

/// 顶点关联骨骼及权重,每个顶点最多可以关联4个骨骼。
struct VertexRelateBoneInfo {
    char bone_index_[4];//骨骼索引，一般骨骼少于128个，用char就行。
    char bone_weight_[4];//骨骼权重，权重不会超过100，所以用char类型就可以。
};

//Mesh数据
struct Mesh {
    unsigned short vertex_num_;//顶点个数
    unsigned short vertex_index_num_;//索引个数
    Vertex* vertex_data_;//顶点数据
    unsigned short* vertex_index_data_;//顶点索引数据

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

    /// 获取字节数
    unsigned short size() {
        auto total_bytes_ = sizeof(vertex_num_) + vertex_num_ * sizeof(Vertex) + sizeof(vertex_index_num_) + vertex_index_num_ * sizeof(unsigned short);
        return total_bytes_;
    }
};

