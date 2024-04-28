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
	static void ExportMesh(string save_path, vector<Vertex> kVertexRemoveDumplicateVector, vector<unsigned short> kVertexIndexVector);
	void LoadMesh(std::string mesh_file_path);
	Mesh *GetMesh(){return mesh_;}
private:
	Mesh* mesh_;//Mesh����
};
