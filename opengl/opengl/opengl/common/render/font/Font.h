#pragma once
#include <unordered_map>;
#include <string>
#include "../textures/Texture2D.h";
#include "freetype/ftglyph.h"

class Font
{
public:
    /// freetype为字符生成bitmap
    /// \param c
    void LoadCharacter(char ch);

    Texture2D* font_texture() { return font_texture_; }

private:
    unsigned short font_size_ = 20;//默认字体大小
    char* font_file_buffer_ = nullptr;//ttf字体文件加载到内存
    FT_Library ft_library_;
    FT_Face ft_face_;
    Texture2D* font_texture_;
    unsigned short font_texture_size_ = 1024;

public:
	static Font* LoadFromFile(std::string font_file_path, unsigned short font_size);
	static Font* GetFont(std::string font_file_path);
private:
	static std::unordered_map<std::string, Font*> font_map_;
};

