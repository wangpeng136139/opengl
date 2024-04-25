#pragma once
#include "../vertex/Vertex.h"
//Mesh文件头
struct MeshFileHead {
    char type_[4];
    int vertex_num_;//顶点个数
    int vertex_index_num_;//索引个数
};

//Mesh数据
struct Mesh {
    unsigned short vertex_num_;//顶点个数
    unsigned short vertex_index_num_;//索引个数
    Vertex* vertex_data_;//顶点数据
    unsigned short* vertex_index_data_;//顶点索引数据
};

