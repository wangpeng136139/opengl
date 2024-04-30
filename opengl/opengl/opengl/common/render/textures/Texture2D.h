//
// Created by captain on 2021/4/5.
// ͼƬ���������
//

#ifndef UNTITLED_TEXTURE2D_H
#define UNTITLED_TEXTURE2D_H

#define STB_IMAGE_IMPLEMENTATION
#include <iostream>

#include <glad/glad.h>


//tcp�ļ�ͷ
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
    void UpdateSubImage(int x, int y, int width, int height, unsigned int client_format, unsigned int data_type, unsigned char* data);
public:
    static Texture2D* LoadFromFile(std::string& image_file_path);//����һ��ͼƬ�ļ�
    static Texture2D* LoadFromFileTpc(std::string& image_file_path);
    static void CompressImageFile(std::string& image_file_path, std::string& save_image_file_path);
    static Texture2D* Create(unsigned short width, unsigned short height, unsigned int server_format, unsigned int client_format,
        unsigned int data_type, unsigned char* data);     
public:
    int width_;
    int height_;
    GLuint gl_texture_id_;//����ID
    GLenum gl_texture_format_;//����ID
    int mipmap_level_ = 0;
};

#endif //UNTITLED_TEXTURE2D_H
