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


	int width() { return width_; }
	int height() { return height_; }
	void set_texture(Texture2D* texture2D) {
		texture2D_ = texture2D;
		width_ = texture2D->width();
		height_ = texture2D->height();
	}
private:
	Texture2D* texture2D_ = nullptr;
	int width_;
	int height_;

};

#endif
