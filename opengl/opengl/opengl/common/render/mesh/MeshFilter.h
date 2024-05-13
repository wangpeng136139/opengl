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
private:
	Mesh* mesh_;//Mesh∂‘œÛ
};
