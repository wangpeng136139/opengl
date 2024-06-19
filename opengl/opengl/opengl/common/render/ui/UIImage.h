#pragma once
#ifndef UNTITLED_UI_IMAGE_H
#define UNTITLED_UI_IMAGE_H
#include "../../render_base_head.h"
#include "../../component_head.h"
#include "../../render/textures/render_textures_head.h"
class UIImage : public Component
{
public:
	UIImage();
	~UIImage() override;
	void Update() override;
	/// äÖÈ¾Ö®Ç°
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
