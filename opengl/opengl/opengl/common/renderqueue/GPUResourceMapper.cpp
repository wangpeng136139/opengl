#include "GPUResourceMapper.h"
unsigned int GPUResourceMapper::shader_program_index_ = 0;//Shader��������
unsigned int GPUResourceMapper::vao_index_ = 0;//VAO����
std::unordered_map<unsigned int, GLuint> GPUResourceMapper::shader_program_map_;//Shader����ӳ���
std::unordered_map<unsigned int, GLuint> GPUResourceMapper::vao_map_;//VAOӳ���