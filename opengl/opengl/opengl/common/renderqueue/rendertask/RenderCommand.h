#ifndef UNTITLED_RENDER_COMMAND_H
#define UNTITLED_RENDER_COMMAND_H
/// ��Ⱦ����
enum RenderCommand {
    NONE,
    UPDATE_SCREEN_SIZE,//������Ϸ����ߴ�
    COMPILE_SHADER,//������ɫ��
    USE_SHADER_PROGRAM,//ʹ����ɫ������
    CREATE_VAO,//����VAO
    UPDATE_VBO_SUB_DATA,//����VBO����
    CREATE_COMPRESSED_TEX_IMAGE2D,//����ѹ������
    CREATE_TEX_IMAGE2D,//��������
    DELETE_TEXTURES,//ɾ������
    UPDATE_TEXTURE_SUB_IMAGE2D,//�ֲ�����Texture
    SET_ENABLE_STATE,//����״̬,������ر�
    SET_BLENDER_FUNC,//���û�Ϻ���
    SET_UNIFORM_MATRIX_4FV,//�ϴ�4x4����
    ACTIVE_AND_BIND_TEXTURE,//���������
    SET_UNIFORM_1I,//�ϴ�1��intֵ
    BIND_VAO_AND_DRAW_ELEMENTS,//��VAO������
    SET_CLEAR_FLAG_AND_CLEAR_COLOR_BUFFER,//����clear_flag���������ɫ����
    SET_STENCIL_FUNC,//����ģ����Ժ���
    SET_STENCIL_OP,//����ģ�����
    SET_STENCIL_BUFFER_CLEAR_VALUE,//�������ģ�建��ֵ
    END_FRAME,//֡����
};

#endif //UNTITLED_RENDER_COMMAND_H