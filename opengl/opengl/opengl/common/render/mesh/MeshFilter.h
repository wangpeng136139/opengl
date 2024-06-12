#pragma once
#include "Mesh.h"
#include "../vertex/Vertex.h";
#include <string>
#include <vector>;
#include "../../component/Component.h"
using namespace std;

class MeshFilter:public Component
{
public:
	MeshFilter();
	~MeshFilter() override;
	static void ExportMesh(string save_path, vector<Vertex> kVertexRemoveDumplicateVector, vector<unsigned short> kVertexIndexVector);
	void LoadMesh(std::string mesh_file_path);
	Mesh *GetMesh(){return mesh_;}
	void CreateMesh(std::vector<Vertex>& vertex_data, std::vector<unsigned short>& vertex_index_data);
	/// 获取顶点关联骨骼信息(4个骨骼索引、骨骼权重)，长度为顶点个数
	VertexRelateBoneInfo* vertex_relate_bone_infos() { return vertex_relate_bone_infos_; };
	/// 加载权重文件
	/// \param weight_file_path 权重文件路径
	void LoadWeight(string weight_file_path);


	/// 获取蒙皮Mesh对象指针
	Mesh* skinned_mesh() { return skinned_mesh_; };
	void set_skinned_mesh(Mesh* skinned_mesh) { skinned_mesh_ = skinned_mesh; };
private:
	Mesh* mesh_;//Mesh对象
	Mesh* skinned_mesh_ = nullptr;//蒙皮Mesh对象
	VertexRelateBoneInfo* vertex_relate_bone_infos_ = nullptr;//顶点关联骨骼信息(4个骨骼索引、权重)，长度为顶点数
};
