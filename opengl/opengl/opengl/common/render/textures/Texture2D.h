//
// Created by captain on 2021/4/5.
// 图片加载与解析
//

#ifndef UNTITLED_TEXTURE2D_H
#define UNTITLED_TEXTURE2D_H

#define STB_IMAGE_IMPLEMENTATION
#include <iostream>

#include <glad/glad.h>


//tcp文件头
struct TpcFileHead
{
    char type_[3];
    int mipmap_level_;
    int width_;
    int height_;
    int gl_texture_format_;
    int compress_size_;
};

class Texture2D
{
private:
    Texture2D() {};
    ~Texture2D() {};

public:
    static Texture2D* LoadFromFile(std::string& image_file_path);//加载一个图片文件
    static Texture2D* LoadFromFileTpc(std::string& image_file_path);
    static void CompressImageFile(std::string& image_file_path, std::string& save_image_file_path);
public:
    int width_;
    int height_;
    GLuint gl_texture_id_;//纹理ID
    GLenum gl_texture_format_;//纹理ID
    int mipmap_level_ = 0;
};

#endif //UNTITLED_TEXTURE2D_H
