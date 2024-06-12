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
	/// ��ȡ�������������Ϣ(4����������������Ȩ��)������Ϊ�������
	VertexRelateBoneInfo* vertex_relate_bone_infos() { return vertex_relate_bone_infos_; };
	/// ����Ȩ���ļ�
	/// \param weight_file_path Ȩ���ļ�·��
	void LoadWeight(string weight_file_path);


	/// ��ȡ��ƤMesh����ָ��
	Mesh* skinned_mesh() { return skinned_mesh_; };
	void set_skinned_mesh(Mesh* skinned_mesh) { skinned_mesh_ = skinned_mesh; };
private:
	Mesh* mesh_;//Mesh����
	Mesh* skinned_mesh_ = nullptr;//��ƤMesh����
	VertexRelateBoneInfo* vertex_relate_bone_infos_ = nullptr;//�������������Ϣ(4������������Ȩ��)������Ϊ������
};
