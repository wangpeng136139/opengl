//
// Created by captain on 2022/3/4.
//

#ifndef UNTITLED_GPU_RESOURCE_MAPPER_H
#define UNTITLED_GPU_RESOURCE_MAPPER_H

#include <unordered_map>
#include <glad/glad.h>

/// GPU��Դ�����������GPU��ԴID�����������߼�ID��ӳ���ϵ��
class GPUResourceMapper {
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

    /// ����VBO���
    static unsigned int GenerateVBOHandle() {
        return ++vbo_index_;
    }

    /// ����Texture���
    static unsigned int GenerateTextureHandle() {
        return ++texture_index_;
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

    /// ӳ��VBO
    /// \param vbo_handle
    /// \param vbo_id
    static void MapVBO(unsigned int vbo_handle, GLuint vbo_id) {
        vbo_map_[vbo_handle] = vbo_id;
    }

    /// ӳ��Texture
    static void MapTexture(unsigned int texture_handle, GLuint texture_id) {
        texture_map_[texture_handle] = texture_id;
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

    /// ��ȡVBO
    /// \param vbo_handle
    /// \return
    static GLuint GetVBO(unsigned int vbo_handle) {
        return vbo_map_[vbo_handle];
    }

    /// ��ȡTexture
    static GLuint GetTexture(unsigned int texture_handle) {
        return texture_map_[texture_handle];
    }

private:
    static unsigned int shader_program_index_;//Shader��������
    static unsigned int vao_index_;//VAO����
    static unsigned int vbo_index_;//VBO����
    static unsigned int texture_index_;//Texture����

    static std::unordered_map<unsigned int, GLuint> shader_program_map_;//Shader����ӳ���
    static std::unordered_map<unsigned int, GLuint> vao_map_;//VAOӳ���
    static std::unordered_map<unsigned int, GLuint> vbo_map_;//VBOӳ���
    static std::unordered_map<unsigned int, GLuint> texture_map_;//Textureӳ���
};


#endif //UNTITLED_GPU_RESOURCE_MAPPER_H
