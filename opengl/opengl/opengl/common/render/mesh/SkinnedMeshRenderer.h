/// 骨骼蒙皮动画渲染器
#ifndef UNTITLED_MESH_SKINNEDMESHRENDERER_H
#define UNTITLED_MESH_SKINNEDMESHRENDERER_H

#include "MeshRenderer.h"

class SkinnedMeshRenderer : public MeshRenderer {
public:
    SkinnedMeshRenderer();
    ~SkinnedMeshRenderer();
public:
    // 刷帧，Update在Render之前，在Update里计算最新的蒙皮Mesh
    void Update() override;
};
#endif
