#include "Texture2D.h"
#define STB_IMAGE_IMPLEMENTATION	
#include "stb/stb_image.h"

#include "../../renderqueue/GPUResourceMapper.h";
#include "../../renderqueue/RenderTaskProducer.h"

using namespace std;
using namespace timetool;

Texture2D* Texture2D::LoadFromFile(std::string& image_file_path)
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
    texture2d->texture_handle_ = GPUResourceMapper::GenerateTextureHandle();

    // 发出任务：创建压缩纹理
    RenderTaskProducer::ProduceRenderTaskCreateCompressedTexImage2D(texture2d->texture_handle_, texture2d->width_,
        texture2d->height_, texture2d->gl_texture_format_,
        tpc_file_head.compress_size_, data);

    free(data);
    return texture2d;
}

Texture2D* Texture2D::Create(unsigned short width, unsigned short height, unsigned int server_format, unsigned int client_format,
    unsigned int data_type, unsigned char* data) {
    Texture2D* texture2d = new Texture2D();
    texture2d->gl_texture_format_ = server_format;
    texture2d->width_ = width;
    texture2d->height_ = height;

    // 发出任务：创建纹理
    RenderTaskProducer::ProduceRenderTaskCreateTexImage2D(texture2d->texture_handle_, texture2d->width_, texture2d->height_, texture2d->gl_texture_format_, client_format, data_type, data_size, data);

    return texture2d;
}



