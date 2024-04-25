#pragma once
#include "Mesh.h"
#include "Vertex.h";
#include <string>
#include <vector>;

using namespace std;

class MeshFilter
{
public:
	static void ExportMesh(string save_path, vector<Vertex> kVertexRemoveDumplicateVector, vector<unsigned short> kVertexIndexVector);
	void LoadMesh(std::string mesh_file_path);
	Mesh *GetMesh(){return mesh_;}
private:
	Mesh* mesh_;//Mesh∂‘œÛ
};
