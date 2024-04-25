#include "Texture2D.h"
#include "stb/stb_image.h"
#include <fstream>
#include <iostream>
#include "timetool/stopwatch.h"

using namespace std;
using namespace timetool;

void Texture2D::CompressImageFile(std::string& image_file_path, std::string& save_image_file_path) {
    Texture2D* texture2d = LoadFromFile(image_file_path);
    //1. ��ȡѹ���Ƿ�ɹ�
    GLint compress_success = 0;

    glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_COMPRESSED, &compress_success);
    //2. ��ȡѹ���õ��������ݳߴ�
    GLint compress_size = 0;
    glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_COMPRESSED_IMAGE_SIZE, &compress_size);
    //3. ��ȡ���������ѹ����ʽ
    GLint compress_format = 0;
    glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_INTERNAL_FORMAT, &compress_format);
    //4. ��GPU�У����Դ��б����ѹ���õ��������ݣ����ص��ڴ�
    void* img = malloc(compress_size);
    glGetCompressedTexImage(GL_TEXTURE_2D, 0, img);

    std::ofstream output_file_stream(save_image_file_path, std::ios::out | std::ios::binary);

    TpcFileHead tcp_file_head;
    tcp_file_head.type_[0] = 'c';
    tcp_file_head.type_[1] = 'p';
    tcp_file_head.type_[2] = 't';
    tcp_file_head.mipmap_level_ =0;
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
* 	������ʱ(ms)	�ϴ���ʱ(ms)
jpg	1571	960
cpt	4	16
*/
    Texture2D* texture2d = new Texture2D();
    StopWatch stopwatch;
    stopwatch.start();
    //��ȡ cpt ѹ�������ļ�
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

    //1. ֪ͨ�Կ�����������󣬷��ؾ��;
    glGenTextures(1, &(texture2d->gl_texture_id_));
    //2. ������󶨵��ض�����Ŀ��;
    glBindTexture(GL_TEXTURE_2D, texture2d->gl_texture_id_);
    stopwatch.restart();
    {
        //3. ��ѹ�����������ϴ���GPU;
        glCompressedTexImage2D(GL_TEXTURE_2D, 0, texture2d->gl_texture_format_, texture2d->width_, texture2d->height_, 0, tpc_file_head.compress_size_, data);
    }
    stopwatch.stop();
    std::int64_t upload_cpt_cost = stopwatch.milliseconds();
    //4. ָ���Ŵ���С�˲���ʽ�������˲������Ŵ���С�Ĳ�ֵ��ʽ;
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    delete (data);
    return texture2d;
}

Texture2D* Texture2D::LoadFromFile(std::string& image_file_path)
{
    Texture2D* texture2d = new Texture2D();

    stbi_set_flip_vertically_on_load(true);//��תͼƬ������������ͼƬ���ݴ����½ǿ�ʼ��������ΪOpenGL������������ʼ��Ϊ���½ǡ�
    int channels_in_file;//ͨ����

    StopWatch stopwatch;
    stopwatch.start();
    unsigned char* data = stbi_load(image_file_path.c_str(), &(texture2d->width_), &(texture2d->height_), &channels_in_file, 0);
    stopwatch.stop();
    std::int64_t decompress_jpg_cost = stopwatch.milliseconds();

    int image_data_format = GL_RGB;
    if (data != nullptr)
    {
        //������ɫͨ�������ж���ɫ��ʽ��
        switch (channels_in_file) {
        case 1:
        {
            image_data_format = GL_ALPHA;
            break;
        }
        case 3:
        {
            image_data_format = GL_RGB;
            texture2d->gl_texture_format_ = GL_COMPRESSED_RGB;
            break;
        }
        case 4:
        {
            image_data_format = GL_RGBA;
            texture2d->gl_texture_format_ = GL_COMPRESSED_RGBA;
            break;
        }
        }
    }


    //1. ֪ͨ�Կ�����������󣬷��ؾ��;
    glGenTextures(1, &(texture2d->gl_texture_id_));

    //2. ������󶨵��ض�����Ŀ��;
    glBindTexture(GL_TEXTURE_2D, texture2d->gl_texture_id_);

    stopwatch.restart();

    //3. ��ͼƬrgb�����ϴ���GPU;������ѹ����
    glTexImage2D(GL_TEXTURE_2D, texture2d->mipmap_level_, texture2d->gl_texture_format_, texture2d->width_, texture2d->height_, 0, image_data_format, GL_UNSIGNED_BYTE, data);
    stopwatch.stop();
    std::int64_t upload_and_compress_cost = stopwatch.milliseconds();

    //4. ָ���Ŵ���С�˲���ʽ�������˲������Ŵ���С�Ĳ�ֵ��ʽ;
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    //�ͷ�ͼƬ�ļ��ڴ�
    stbi_image_free(data);

    return texture2d;
}
