#pragma once

#ifndef UNTITLED_GPU_RESOURCE_MAPPER_H
#define UNTITLED_GPU_RESOURCE_MAPPER_H

#include <unordered_map>
#include <glad/glad.h>
class GPUResourceMapper
{
public:
    /// ����Shader������
/// \return
    static unsigned int GenerateShaderProgramHandle() {
        return ++shader_program_index_;
    }

    /// ����VAO���
    /// \return
    static unsigned int GenerateVAOHandle() {
        return ++vao_index_;
    }

    /// ӳ��Shader����
    /// \param shader_program_handle
    /// \param shader_program_id
    static void MapShaderProgram(unsigned int shader_program_handle, GLuint shader_program_id) {
        shader_program_map_[shader_program_handle] = shader_program_id;
    }

    /// ӳ��VAO
    /// \param vao_handle
    /// \param vao_id
    static void MapVAO(unsigned int vao_handle, GLuint vao_id) {
        vao_map_[vao_handle] = vao_id;
    }

    /// ��ȡShader����
    /// \param shader_program_handle
    /// \return
    static GLuint GetShaderProgram(unsigned int shader_program_handle) {
        return shader_program_map_[shader_program_handle];
    }

    /// ��ȡVAO
    /// \param vao_handle
    /// \return
    static GLuint GetVAO(unsigned int vao_handle) {
        return vao_map_[vao_handle];
    }
private:
    static unsigned int shader_program_index_;//Shader��������
    static unsigned int vao_index_;//VAO����

    static std::unordered_map<unsigned int, GLuint> shader_program_map_;//Shader����ӳ���
    static std::unordered_map<unsigned int, GLuint> vao_map_;//VAOӳ���
};


#endif