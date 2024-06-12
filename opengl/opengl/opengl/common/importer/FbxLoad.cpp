#include "FbxLoad.h"


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
