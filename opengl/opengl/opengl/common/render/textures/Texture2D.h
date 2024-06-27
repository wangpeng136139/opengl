#ifndef UNTITLED_TEXTURE2D_H
#define UNTITLED_TEXTURE2D_H

#include "../../render_base_head.h"

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
public:
    ~Texture2D() {};
public:
    void UpdateSubImage(int x, int y, int width, int height, unsigned int client_format, unsigned int data_type, unsigned char* data);
    int width(){ return width_;}
    int height(){return height_;}

public:
    static Texture2D* LoadFromFile(std::string& image_file_path);
    static void CompressImageFile(std::string& image_file_path  , std::string& save_image_file_path);
    static Texture2D* Create(unsigned short width, unsigned short height, unsigned int server_format, unsigned int client_format,
        unsigned int data_type, unsigned char* data);     
public:
    int mipmap_level_;
    int width_;
    int height_;
    GLenum gl_texture_format_;
    unsigned int texture_handle_;//纹理ID
};

#endif //UNTITLED_TEXTURE2D_H
