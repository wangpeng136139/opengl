#pragma once
#include "../vertex/Vertex.h"
//Mesh�ļ�ͷ
struct MeshFileHead {
    char type_[4];
    int vertex_num_;//�������
    int vertex_index_num_;//��������
};

//Mesh����
struct Mesh {
    unsigned short vertex_num_;//�������
    unsigned short vertex_index_num_;//��������
    Vertex* vertex_data_;//��������
    unsigned short* vertex_index_data_;//������������
};

