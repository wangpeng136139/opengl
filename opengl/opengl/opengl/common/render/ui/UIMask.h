#pragma once
#ifndef UNTITLED_UI_MASK_H
#define UNTITLED_UI_MASK_H

#include "../../component/Component.h"
#include "../mesh/MeshFilter.h"

class Texture2D;
class UIMask : public Component {
public:
    UIMask();
    ~UIMask() override;

    Texture2D* texture2D() { return texture2D_; }
    void set_texture(Texture2D* texture2D) { texture2D_ = texture2D; }

public:
    void OnEnable() override;

    void Update() override;
    /// ��Ⱦ֮ǰ
    void OnPreRender() override;
    /// ��Ⱦ֮��
    void OnPostRender() override;

    void OnDisable() override;
private:
    Texture2D* texture2D_ = nullptr;//Texture
};


#endif //UNTITLED_UI_MASK_H