#include "FbxLoad.h"
#include "../render/mesh/Mesh.h"
#include "../render/mesh/MeshFilter.h"
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <iostream>
#include <fstream>
//#include <filesystem>

int FbxLoad::Initialization()
{
    std::string mFileName;
    FbxManager* mSdkManager;
    FbxScene* mScene;
    FbxImporter* mImporter;
    // ��ʼ��FBX SDKManager��������һ��Scene���������ɴ�FBX�н��������ж���
    InitializeSdkObjects(mSdkManager, mScene);
    if (!mSdkManager) {
        DEBUG_LOG_ERROR("Failed to create FBX SDK manager.");
        return -1;
    }

    int lFileFormat = -1;
    mImporter = FbxImporter::Create(mSdkManager, "");
    if (!mSdkManager->GetIOPluginRegistry()->DetectReaderFileFormat(mFileName.c_str(), lFileFormat)) {
        // δ��ʶ���ļ���ʽ
        DEBUG_LOG_ERROR("Unrecognizable file format.");
        return -1;
    }

    // ��ʼ��Importer�������ļ�·��
    if (mImporter->Initialize(mFileName.c_str(), lFileFormat) == false) {
        DEBUG_LOG_ERROR("Call to FbxImporter::Initialize() failed.Error reported: {}", mImporter->GetStatus().GetErrorString());
        return -1;
    }

    // ��FBX�ļ��������뵽Scene��
    bool lResult = mImporter->Import(mScene);
    if (!lResult) {
        DEBUG_LOG_ERROR("Call to FbxImporter::Import() failed.Error reported: {}", mImporter->GetStatus().GetErrorString());
    }

    // ���Scene������
    FbxStatus status;
    FbxArray<FbxString*> details;
    FbxSceneCheckUtility sceneCheck(FbxCast<FbxScene>(mScene), &status, &details);
    bool lNotify = (!sceneCheck.Validate(FbxSceneCheckUtility::eCkeckData) && details.GetCount() > 0) ||
        (mImporter->GetStatus().GetCode() != FbxStatus::eSuccess);
    //���������Ϣ
      if (lNotify) {
        return LogSceneCheckError(mImporter, details);
    }

      // ת������ϵΪ��������ϵ��
      FbxAxisSystem SceneAxisSystem = mScene->GetGlobalSettings().GetAxisSystem();
      FbxAxisSystem OurAxisSystem(FbxAxisSystem::eYAxis, FbxAxisSystem::eParityOdd, FbxAxisSystem::eRightHanded);
      if (SceneAxisSystem != OurAxisSystem) {
          OurAxisSystem.ConvertScene(mScene);
      }

      // ת����Ԫ����
      FbxSystemUnit SceneSystemUnit = mScene->GetGlobalSettings().GetSystemUnit();
      if (SceneSystemUnit.GetScaleFactor() != 1.0) {
          // �������õ������ף���������ҲҪת��
          FbxSystemUnit::cm.ConvertScene(mScene);
      }

      // ת�����浽������
      FbxGeometryConverter lGeomConverter(mSdkManager);
      try {
          lGeomConverter.Triangulate(mScene, /*replace*/true);
      }
      catch (std::runtime_error) {
          DEBUG_LOG_ERROR("Scene integrity verification failed.\n");
          return -1;
      }

      // �ݹ�����ڵ�
      ParseNode(mScene->GetRootNode());

      DEBUG_LOG_INFO("extra mesh success.press any key exit.");
      getchar();
      return 0;
}

/// �ݹ�����ڵ�
/// @param pNode �ڵ�
void FbxLoad::ParseNode(FbxNode* pNode) {
    // ��ȡ�ڵ�����
    FbxNodeAttribute* lNodeAttribute = pNode->GetNodeAttribute();
    if (lNodeAttribute) {
        // �ڵ���Mesh
        if (lNodeAttribute->GetAttributeType() == FbxNodeAttribute::eMesh) {
            FbxMesh* lMesh = pNode->GetMesh();
            if (lMesh && !lMesh->GetUserDataPtr()) {
                ParseMesh(lMesh);
            }
        }
    }

    // �ݹ�����ӽڵ�
    const int lChildCount = pNode->GetChildCount();
    for (int lChildIndex = 0; lChildIndex < lChildCount; ++lChildIndex) {
        ParseNode(pNode->GetChild(lChildIndex));
    }
}

/// ����Mesh
/// @param pMesh Mesh ����
void  FbxLoad::ParseMesh(const FbxMesh* pMesh) {
    FbxNode* lNode = pMesh->GetNode();
    if (!lNode) {
        DEBUG_LOG_ERROR("Mesh has no node.");
        return;
    }
    DEBUG_LOG_INFO("Mesh name: {}", lNode->GetName());

    // ��ȡMesh����θ���������Ϸ��˵����������������
    const int lPolygonCount = pMesh->GetPolygonCount();
    // �Ƿ���UV���ݣ�
    bool mHasUV = pMesh->GetElementUVCount() > 0;
    // �Ƿ��з������ݣ�
    bool mHasNormal = pMesh->GetElementNormalCount() > 0;

    bool mAllByControlPoint = true;
    FbxGeometryElement::EMappingMode lUVMappingMode = FbxGeometryElement::eNone;
    if (mHasUV) {
        lUVMappingMode = pMesh->GetElementUV(0)->GetMappingMode();
        if (lUVMappingMode == FbxGeometryElement::eNone) {
            mHasUV = false;
        }
        if (mHasUV && lUVMappingMode != FbxGeometryElement::eByControlPoint) {
            mAllByControlPoint = false;
        }
    }

    // ���ն�����������Ƕ��٣�
    // ���ֻ��һ��UV����UVӳ�䷽ʽ�ǰ�ʵ�ʶ������(FbxGeometryElement::eByControlPoint)����ô����ʵ�ʶ��������
    // ����ж���UV����ôһ�������ڲ�ͬ�Ķ��������Ӧ��ͬ��UV���꣬��UVӳ�䷽ʽ�ǰ������(eByPolygonVertex)����ô��������Ƕ������*3.
    int lPolygonVertexCount = mAllByControlPoint ? pMesh->GetControlPointsCount() : lPolygonCount * 3;
    // �������������ж������ꡣ
    float* lVertices = new float[lPolygonVertexCount * 3];
    // �����������������ݣ����鳤��=����*3.
    unsigned short* lIndices = new unsigned short[lPolygonCount * 3];
    // ��ȡ����UV����
    float* lUVs = NULL;
    FbxStringList lUVNames;
    pMesh->GetUVSetNames(lUVNames);
    const char* lUVName = NULL;
    if (mHasUV && lUVNames.GetCount()) {
        // ����������UV����
        lUVs = new float[lPolygonVertexCount * 2];
        // ��ʱֻʹ�õ�һ��UV��
        lUVName = lUVNames[0];
    }

    // ��ȡ��������
    float* lNormals = NULL;
    if (mHasNormal) {
        // ���������ŷ�������
        lNormals = new float[lPolygonVertexCount * 3];
    }



    // ʵ�ʶ������ݡ�
    const FbxVector4* lControlPoints = pMesh->GetControlPoints();

    // �������������棬����ÿ������������㣬�����������ꡢUV�������ݡ�
    int lVertexCount = 0;
    for (int lPolygonIndex = 0; lPolygonIndex < lPolygonCount; ++lPolygonIndex) {
        // �����棬3������
        for (int lVerticeIndex = 0; lVerticeIndex < 3; ++lVerticeIndex) {
            // �������������Լ���ǰ��ĵڼ������㣬��ȡ����������
            const int lControlPointIndex = pMesh->GetPolygonVertex(lPolygonIndex, lVerticeIndex);
            if (lControlPointIndex >= 0) {
                // ��Ϊ�趨һ�������ж���UV������ÿ�������������������ڵĹ���Ķ��㣬����ʵ������ͬһ����(ControlPoint),��Ϊ�в�ͬ��UV�����Ի����㲻ͬ�Ķ��㡣
                lIndices[lVertexCount] = static_cast<unsigned short>(lVertexCount);
                // ��ȡ��ǰ����������Ӧ��ʵ�ʶ��㡣
                FbxVector4 lCurrentVertex = lControlPoints[lControlPointIndex];
                // �����������FbxVector4תΪfloat����
                lVertices[lVertexCount * 3] = static_cast<float>(lCurrentVertex[0]);
                lVertices[lVertexCount * 3 + 1] = static_cast<float>(lCurrentVertex[1]);
                lVertices[lVertexCount * 3 + 2] = static_cast<float>(lCurrentVertex[2]);

                if (mHasUV) {
                    // ��ȡ��ǰ������ָ��UV���UV���꣬ǰ��˵����һ����������ж���UV��
                    bool lUnmappedUV;
                    FbxVector2 lCurrentUV;
                    pMesh->GetPolygonVertexUV(lPolygonIndex, lVerticeIndex, lUVName, lCurrentUV, lUnmappedUV);
                    // ��UV�����FbxVector2תΪfloat����
                    lUVs[lVertexCount * 2] = static_cast<float>(lCurrentUV[0]);
                    lUVs[lVertexCount * 2 + 1] = static_cast<float>(lCurrentUV[1]);
                }

                // ������������
                if (mHasNormal) {
                    // ��ȡ��ǰ������ָ�����߲�ķ������꣬ǰ��˵����һ����������ж��׷��ߡ�
                    bool lUnmappedNormal;
                    FbxVector4 lCurrentNormal;
                    pMesh->GetPolygonVertexNormal(lPolygonIndex, lVerticeIndex, lCurrentNormal);
                    // �����������FbxVector4תΪfloat����
                    lNormals[lVertexCount * 3] = static_cast<float>(lCurrentNormal[0]);
                    lNormals[lVertexCount * 3 + 1] = static_cast<float>(lCurrentNormal[1]);
                    lNormals[lVertexCount * 3 + 2] = static_cast<float>(lCurrentNormal[2]);
                }
            }
            ++lVertexCount;
        }
    }


    // ��������Mesh�ļ�����FBX�н���������䵽���档
    MeshFile mesh_file;
    // ��������Mesh�ṹ�������ļ�ͷ
    std::strcpy(mesh_file.head_.type_, "Mesh");
    std::strcpy(mesh_file.head_.name_, lNode->GetName());
    mesh_file.head_.vertex_num_ = lVertexCount;
    mesh_file.head_.vertex_index_num_ = lVertexCount;
    mesh_file.vertex_ = new Vertex[mesh_file.head_.vertex_num_];
    mesh_file.index_ = new unsigned short[mesh_file.head_.vertex_index_num_];
    // ��䶥�����ꡢcolor��UV���ꡣ
    for (int i = 0; i < lVertexCount; ++i) {
        mesh_file.vertex_[i].pos_ = glm::vec3(lVertices[i * 3], lVertices[i * 3 + 1], lVertices[i * 3 + 2]);
        mesh_file.vertex_[i].color_ = glm::vec4(1.0f);
        mesh_file.vertex_[i].uv_ = glm::vec2(lUVs[i * 2], lUVs[i * 2 + 1]);
        mesh_file.vertex_[i].normal_ = glm::vec3(lNormals[i * 3], lNormals[i * 3 + 1], lNormals[i * 3 + 2]);
    }
    // �������
    //mesh_file.index_ = lIndices;
    //// д���ļ�
    //std::filesystem::path path(src_file_path);
    //std::string src_file_name = path.filename().stem().string();
    //std::string dst_file_name = fmt::format("{}_{}.mesh", src_file_name, mesh_file.head_.name_);
    //path.replace_filename(dst_file_name);
    //mesh_file.Write(path.string());
}


int FbxLoad::LogSceneCheckError(FbxImporter* mImporter, FbxArray<FbxString*>& details) {

    ("\n");
    ("********************************************************************************\n");
    if (details.GetCount()) {
        DEBUG_LOG_ERROR("Scene integrity verification failed with the following errors:\n");

        for (int i = 0; i < details.GetCount(); i++)
            DEBUG_LOG_ERROR("   %s\n", details[i]->Buffer());

        FbxArrayDelete<FbxString*>(details);
    }

    if (mImporter->GetStatus().GetCode() != FbxStatus::eSuccess) {
        DEBUG_LOG_ERROR("\n");
        DEBUG_LOG_ERROR("WARNING:\n");
        DEBUG_LOG_ERROR("   The importer was able to read the file but with errors.\n");
        DEBUG_LOG_ERROR("   Loaded scene may be incomplete.\n\n");
        DEBUG_LOG_ERROR("   Last error message:'%s'\n", mImporter->GetStatus().GetErrorString());
    }

    ("********************************************************************************\n");
    ("\n");
    return -1;
}

void FbxLoad::InitializeSdkObjects(FbxManager*& pManager, FbxScene*& pScene)
{
    //The first thing to do is to create the FBX Manager which is the object allocator for almost all the classes in the SDK
    pManager = FbxManager::Create();
    if (!pManager)
    {
        FBXSDK_printf("Error: Unable to create FBX Manager!\n");
        exit(1);
    }
    else FBXSDK_printf("Autodesk FBX SDK version %s\n", pManager->GetVersion());

    //Create an IOSettings object. This object holds all import/export settings.
    FbxIOSettings* ios = FbxIOSettings::Create(pManager, IOSROOT);
    pManager->SetIOSettings(ios);

    //Load plugins from the executable directory (optional)
    FbxString lPath = FbxGetApplicationDirectory();
    pManager->LoadPluginsDirectory(lPath.Buffer());

    //Create an FBX scene. This object holds most objects imported/exported from/to files.
    pScene = FbxScene::Create(pManager, "My Scene");
    if (!pScene)
    {
        FBXSDK_printf("Error: Unable to create FBX scene!\n");
        exit(1);
    }
}
