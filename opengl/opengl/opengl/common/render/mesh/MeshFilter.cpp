#include "MeshFilter.h"
#include <fstream>
#include <iostream>
#include "vector";
#include <rttr/registration>
using namespace std;

using namespace rttr;
RTTR_REGISTRATION
{
    registration::class_<MeshFilter>("MeshFilter")
            .constructor<>()(rttr::policy::ctor::as_raw_ptr);
}



//导出Mesh文件
void MeshFilter::ExportMesh(string save_path, vector<Vertex> kVertexRemoveDumplicateVector, vector<unsigned short> kVertexIndexVector) {
    ofstream output_file_stream(save_path, ios::out | ios::binary);
    MeshFileHead mesh_file_head;
    mesh_file_head.type_[0] = 'm';
    mesh_file_head.type_[1] = 'e';
    mesh_file_head.type_[2] = 's';
    mesh_file_head.type_[3] = 'h';
    mesh_file_head.vertex_num_ = kVertexRemoveDumplicateVector.size();
    mesh_file_head.vertex_index_num_ = kVertexIndexVector.size();
    //写入文件头
    output_file_stream.write((char*)&mesh_file_head, sizeof(mesh_file_head));
    //写入顶点数据
    output_file_stream.write((char*)&kVertexRemoveDumplicateVector[0], kVertexRemoveDumplicateVector.size() * sizeof(Vertex));
    //写入索引数据
    output_file_stream.write((char*)&kVertexIndexVector[0], kVertexIndexVector.size() * sizeof(unsigned short));
    output_file_stream.close();
}

void MeshFilter::LoadMesh(std::string mesh_file_path) {
    //读取 Mesh文件头
    std::ifstream input_file_stream(mesh_file_path, std::ios::in | std::ios::binary);
    MeshFileHead mesh_file_head;
    input_file_stream.read((char*)&mesh_file_head, sizeof(mesh_file_head));
    //读取顶点数据
    unsigned char* vertex_data = (unsigned char*)malloc(mesh_file_head.vertex_num_ * sizeof(Vertex));
    input_file_stream.read((char*)vertex_data, mesh_file_head.vertex_num_ * sizeof(Vertex));
    //读取顶点索引数据
    unsigned short* vertex_index_data = (unsigned short*)malloc(mesh_file_head.vertex_index_num_ * sizeof(unsigned short));
    input_file_stream.read((char*)vertex_index_data, mesh_file_head.vertex_index_num_ * sizeof(unsigned short));
    input_file_stream.close();
    mesh_ = new Mesh();
    mesh_->vertex_num_ = mesh_file_head.vertex_num_;
    mesh_->vertex_index_num_ = mesh_file_head.vertex_index_num_;
    mesh_->vertex_data_ = (Vertex*)vertex_data;
    mesh_->vertex_index_data_ = vertex_index_data;
}

void MeshFilter::CreateMesh(std::vector<Vertex>& vertex_data, std::vector<unsigned short>& vertex_index_data) {
    mesh_ = new Mesh();
    mesh_->vertex_num_ = vertex_data.size();
    mesh_->vertex_index_num_ = vertex_index_data.size();

    unsigned short vertex_data_size = mesh_->vertex_num_ * sizeof(Vertex);
    mesh_->vertex_data_ = static_cast<Vertex*>(malloc(vertex_data_size));
    memcpy(mesh_->vertex_data_, &vertex_data[0], vertex_data_size);

    unsigned short vertex_index_data_size = mesh_->vertex_num_ * sizeof(Vertex);
    mesh_->vertex_index_data_ = static_cast<unsigned short*>(malloc(vertex_index_data_size));
    memcpy(mesh_->vertex_index_data_, &vertex_index_data[0], vertex_index_data_size);
}


