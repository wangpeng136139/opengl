/// ������Ƥ������Ⱦ��
#ifndef UNTITLED_MESH_SKINNEDMESHRENDERER_H
#define UNTITLED_MESH_SKINNEDMESHRENDERER_H

#include "MeshRenderer.h"

class SkinnedMeshRenderer : public MeshRenderer {
public:
    SkinnedMeshRenderer();
    ~SkinnedMeshRenderer();
public:
    // ˢ֡��Update��Render֮ǰ����Update��������µ���ƤMesh
    void Update() override;
};
#endif
