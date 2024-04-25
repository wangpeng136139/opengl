#include "MeshRenderer.h"


MeshRenderer::MeshRenderer() {

}

MeshRenderer::~MeshRenderer() {

}

void MeshRenderer::SetMaterial(Material* material) {
    material_ = material;
}

void MeshRenderer::SetMeshFilter(MeshFilter* mesh_filter) {
    mesh_filter_ = mesh_filter;
}

void MeshRenderer::SetMVP(glm::mat4 mvp) {
    mvp_ = mvp;
}

void MeshRenderer::Render() {
    //��ȡ`Shader`��`gl_program_id`��ָ��ΪĿ��Shader����
    GLuint gl_program_id = material_->shader()->GetProgramId();

    if (vertex_array_object_ == 0) {
        GLint vpos_location = glGetAttribLocation(gl_program_id, "a_pos");
        GLint vcol_location = glGetAttribLocation(gl_program_id, "a_color");
        GLint a_uv_location = glGetAttribLocation(gl_program_id, "a_uv");

        //��GPU�ϴ�������������
        glGenBuffers(1, &vertex_buffer_object_);
        //������������ָ��Ϊ���㻺��������
        glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_object_);
        //�ϴ��������ݵ�����������
        glBufferData(GL_ARRAY_BUFFER, mesh_filter_->GetMesh()->vertex_num_ * sizeof(Vertex), mesh_filter_->GetMesh()->vertex_data_, GL_STATIC_DRAW);

        //��GPU�ϴ�������������
        glGenBuffers(1, &element_buffer_object_);
        //������������ָ��Ϊ������������������
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, element_buffer_object_);
        //�ϴ������������ݵ�����������
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, mesh_filter_->GetMesh()->vertex_index_num_ * sizeof(unsigned short), mesh_filter_->GetMesh()->vertex_index_data_, GL_STATIC_DRAW);

        glGenVertexArrays(1, &vertex_array_object_);

        //����VAO
        glBindVertexArray(vertex_array_object_);
        {
            //ָ����ǰʹ�õ�VBO
            glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_object_);
            //��Shader����(a_pos)�Ͷ�������VBO������й���������0��ʾ����ƫ������
            glVertexAttribPointer(vpos_location, 3, GL_FLOAT, false, sizeof(Vertex), 0);
            //���ö���Shader����(a_color)��ָ���붥����ɫ���ݽ��й���
            glVertexAttribPointer(vcol_location, 4, GL_FLOAT, false, sizeof(Vertex), (void*)(sizeof(float) * 3));
            //��Shader����(a_uv)�Ͷ���UV����VBO������й���������0��ʾ����ƫ������
            glVertexAttribPointer(a_uv_location, 2, GL_FLOAT, false, sizeof(Vertex), (void*)(sizeof(float) * (3 + 4)));

            glEnableVertexAttribArray(vpos_location);
            glEnableVertexAttribArray(vcol_location);
            glEnableVertexAttribArray(a_uv_location);

            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, element_buffer_object_);
        }
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    glUseProgram(gl_program_id);
    {
        glEnable(GL_DEPTH_TEST);
        glEnable(GL_CULL_FACE);//���������޳�
        //�ϴ�mvp����
        glUniformMatrix4fv(glGetUniformLocation(gl_program_id, "u_mvp"), 1, GL_FALSE, &mvp_[0][0]);

        //��Pass�ڵ��õ������Texture
        std::vector<std::pair<std::string, Texture2D*>> textures = material_->textures();
        for (int texture_index = 0; texture_index < textures.size(); ++texture_index) {
            GLint u_texture_location = glGetUniformLocation(gl_program_id, textures[texture_index].first.c_str());
            //��������Ԫ0
            glActiveTexture(GL_TEXTURE0 + texture_index);
            //�����ص�ͼƬ���������󶨵�����Ԫ0��Texture2D�ϡ�
            glBindTexture(GL_TEXTURE_2D, textures[texture_index].second->gl_texture_id_);
            //����Shader���������Ԫ0��ȡ��ɫ����
            glUniform1i(u_texture_location, texture_index);
        }

        glBindVertexArray(vertex_array_object_);
        {
            glDrawElements(GL_TRIANGLES, mesh_filter_->GetMesh()->vertex_index_num_, GL_UNSIGNED_SHORT, 0);//ʹ�ö����������л��ƣ�����0��ʾ����ƫ������
        }
        glBindVertexArray(0);
    }
}