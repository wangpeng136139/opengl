#pragma once
#include <unordered_map>;
#include <string>
#include "../textures/Texture2D.h";
#include "freetype/ftglyph.h"

class Font
{
public:
    /// ��¼�����ַ���ͼ���ϵ����ꡢ��ߣ���������ͬ�ߴ�Ķ������ݣ�1��1��Ⱦ��
    struct Character {  
        float left_top_x_;
        float left_top_y_;
        float right_bottom_x_;
        float right_bottom_y_;
        Character(float left_top_x, float left_top_y, float right_bottom_x, float right_bottom_y) {
            left_top_x_ = left_top_x;
            left_top_y_ = left_top_y;
            right_bottom_x_ = right_bottom_x;
            right_bottom_y_ = right_bottom_y;
        }
    };

public:
    /// freetypeΪ�ַ�����bitmap
    /// \param c
    void LoadCharacter(char ch);

    Texture2D* font_texture() { return font_texture_; }

    std::vector<Character*> LoadStr(std::string str);
private:
    unsigned short font_size_ = 20;//Ĭ�������С
    char* font_file_buffer_ = nullptr;//ttf�����ļ����ص��ڴ�
    FT_Library ft_library_;
    FT_Face ft_face_;
    Texture2D* font_texture_;
    unsigned short font_texture_size_ = 1024;
    std::unordered_map<char, Character*> character_map_;//�Ѿ�����bitmap���ַ�
    unsigned short font_texture_fill_x = 0;//��ǰ�е���ʼ��
    unsigned short font_texture_fill_y = 0;//�µ�һ�е�������ʼ��
public:
	static Font* LoadFromFile(std::string font_file_path, unsigned short font_size);
	static Font* GetFont(std::string font_file_path);
private:
	static std::unordered_map<std::string, Font*> font_map_;
};

