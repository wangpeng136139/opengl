#pragma once
#ifndef UNTITLED_FbxLoad_H
#define UNTITLED_FbxLoad_H

#include <fbxsdk.h>
#include "../../common/common/Debug.h"

class FbxLoad
{
public:
	int Initialization();
	void InitializeSdkObjects(FbxManager*& pManager, FbxScene*& pScene);
	int LogSceneCheckError(FbxImporter* mImporter, FbxArray<FbxString*>& details);
	void ParseNode(FbxNode* pNode, std::string mFileName);
	void ParseMesh(const FbxMesh* pMesh,std::string mFileName);
};
#endif