#include "GPUResourceMapper.h"
unsigned int GPUResourceMapper::shader_program_index_ = 0;//Shader��������
unsigned int GPUResourceMapper::vao_index_;//VAO����
unsigned int GPUResourceMapper::vbo_index_;//VBO����
unsigned int GPUResourceMapper::texture_index_;//Texture����
std::unordered_map<unsigned int, GLuint> GPUResourceMapper::shader_program_map_;//Shader����ӳ���
std::unordered_map<unsigned int, GLuint> GPUResourceMapper::vao_map_;//VAOӳ���
std::unordered_map<unsigned int, GLuint> GPUResourceMapper::vbo_map_;//VBOӳ���
std::unordered_map<unsigned int, GLuint> GPUResourceMapper::texture_map_;//Textureӳ���