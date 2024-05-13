#pragma once
#ifndef UNTITLED_UI_IMAGE_H
#define UNTITLED_UI_IMAGE_H
#include "../../component/Component.h"
#include "../../render/textures/Texture2D.h";
#include "../../component/GameObject.h"
class UIImage : public Component
{
public:
	UIImage();
	~UIImage() override;
	void Update() override;
	/// ��Ⱦ֮ǰ
	void OnPreRender() override;

	void OnPostRender() override;
private:
	Texture2D* texture2D_ = nullptr;

};

#endif
