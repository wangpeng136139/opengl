#include "Texture2D.h"
#include "stb/stb_image.h"
#include <fstream>
#include <iostream>
#include "timetool/stopwatch.h"

using namespace std;
using namespace timetool;

void Texture2D::CompressImageFile(std::string& image_file_path, std::string& save_image_file_path) {
    Texture2D* texture2d = LoadFromFile(image_file_path);
    //1. 获取压缩是否成功
    GLint compress_success = 0;

    glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_COMPRESSED, &compress_success);
    //2. 获取压缩好的纹理数据尺寸
    GLint compress_size = 0;
    glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_COMPRESSED_IMAGE_SIZE, &compress_size);
    //3. 获取具体的纹理压缩格式
    GLint compress_format = 0;
    glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_INTERNAL_FORMAT, &compress_format);
    //4. 从GPU中，将显存中保存的压缩好的纹理数据，下载到内存
    void* img = malloc(compress_size);
    glGetCompressedTexImage(GL_TEXTURE_2D, 0, img);

    std::ofstream output_file_stream(save_image_file_path, std::ios::out | std::ios::binary);

    TpcFileHead tcp_file_head;
    tcp_file_head.type_[0] = 'c';
    tcp_file_head.type_[1] = 'p';
    tcp_file_head.type_[2] = 't';
    tcp_file_head.mipmap_level_ = texture2d->mipmap_level_;
    tcp_file_head.width_ = texture2d->width_;
    tcp_file_head.height_ = texture2d->height_;
    tcp_file_head.gl_texture_format_ = compress_format;
    tcp_file_head.compress_size_ = compress_size;
    output_file_stream.write((char*)&tcp_file_head, sizeof(TpcFileHead));
    output_file_stream.write((char*)img, compress_size);
    output_file_stream.close();
}


Texture2D* Texture2D::LoadFromFileTpc(std::string& image_file_path)
{
/*
* 	解析耗时(ms)	上传耗时(ms)
jpg	1571	960
cpt	4	16
*/
    Texture2D* texture2d = new Texture2D();
    StopWatch stopwatch;
    stopwatch.start();
    //读取 cpt 压缩纹理文件
    ifstream input_file_stream(image_file_path, ios::in | ios::binary);
    TpcFileHead tpc_file_head;
    input_file_stream.read((char*)&tpc_file_head, sizeof(TpcFileHead));
    unsigned char* data = (unsigned char*)malloc(tpc_file_head.compress_size_);
    input_file_stream.read((char*)data, tpc_file_head.compress_size_);
    input_file_stream.close();
    stopwatch.stop();
    std::int64_t decompress_jpg_cost = stopwatch.milliseconds();
    texture2d->gl_texture_format_ = tpc_file_head.gl_texture_format_;
    texture2d->width_ = tpc_file_head.width_;
    texture2d->height_ = tpc_file_head.height_;
    texture2d->mipmap_level_ = tpc_file_head.mipmap_level_;

    //1. 通知显卡创建纹理对象，返回句柄;
    glGenTextures(1, &(texture2d->gl_texture_id_));
    //2. 将纹理绑定到特定纹理目标;
    glBindTexture(GL_TEXTURE_2D, texture2d->gl_texture_id_);
    stopwatch.restart();
    {
        //3. 将压缩纹理数据上传到GPU;
        glCompressedTexImage2D(GL_TEXTURE_2D, 0, texture2d->gl_texture_format_, texture2d->width_, texture2d->height_, 0, tpc_file_head.compress_size_, data);
    }
    stopwatch.stop();
    std::int64_t upload_cpt_cost = stopwatch.milliseconds();
    //4. 指定放大，缩小滤波方式，线性滤波，即放大缩小的插值方式;
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    delete (data);
    return texture2d;
}

Texture2D* Texture2D::LoadFromFile(std::string& image_file_path)
{
    Texture2D* texture2d = new Texture2D();

    stbi_set_flip_vertically_on_load(true);//翻转图片，解析出来的图片数据从左下角开始，这是因为OpenGL的纹理坐标起始点为左下角。
    int channels_in_file;//通道数
    unsigned char* data = stbi_load(image_file_path.c_str(), &(texture2d->width_), &(texture2d->height_), &channels_in_file, 0);
    if (data != nullptr)
    {
        //根据颜色通道数，判断颜色格式。
        switch (channels_in_file) {
        case 1:
        {
            texture2d->gl_texture_format_ = GL_ALPHA;
            break;
        }
        case 3:
        {
            texture2d->gl_texture_format_ = GL_RGB;
            break;
        }
        case 4:
        {
            texture2d->gl_texture_format_ = GL_RGBA;
            break;
        }
        }
    }

      //1. 通知显卡创建纹理对象，返回句柄;
    glGenTextures(1, &(texture2d->gl_texture_id_));
    //2. 将纹理绑定到特定纹理目标;
    glBindTexture(GL_TEXTURE_2D, texture2d->gl_texture_id_);
    //3. 将图片rgb数据上传到GPU;
    /**
 * @brief 将图片数据上传到GPU;
 * @param target    目标纹理，GL_TEXTURE_2D(2D纹理)
 * @param level     当图片数据是包含多个mipmap层级时，指定使用mipmap层级。
 * @param internalformat 图片数据上传到GPU后，在显存中保存为哪种格式？
 * @param width
 * @param height
 * @param border
 * @param format 上传的图片数据格式，RGB、RGBA、Alpha等
 * @param type 图片数据变量格式，一般都是GL_UNSIGNED_BYTE(0-255范围)
 * @param pixels 图片数据
 * @return
 */
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, texture2d->width_, texture2d->height_, 0, texture2d->gl_texture_format_, GL_UNSIGNED_BYTE, data);
    //4. 指定放大，缩小滤波方式，线性滤波，即放大缩小的插值方式;
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    //释放图片文件内存
    stbi_image_free(data);

    return texture2d;
}
