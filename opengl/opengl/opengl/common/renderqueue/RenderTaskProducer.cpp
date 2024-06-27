#include "RenderTaskProducer.h"


void RenderTaskProducer::ProduceRenderTaskUpdateScreenSize()
{
    RenderTaskUpdateScreenSize* task = new RenderTaskUpdateScreenSize();
    RenderTaskQueue::Push(task);
}

void RenderTaskProducer::ProduceRenderTaskSetClearFlagAndClearColorBuffer(unsigned int clear_flag, float clear_color_r, float clear_color_g, float clear_color_b, float clear_color_a) {
    RenderTaskClear* task = new RenderTaskClear();
    task->clear_flag_ = clear_flag;
    task->clear_color_r_ = clear_color_r;
    task->clear_color_g_ = clear_color_g;
    task->clear_color_b_ = clear_color_b;
    task->clear_color_a_ = clear_color_a;
    RenderTaskQueue::Push(task);
}


void RenderTaskProducer::ProduceRenderTaskCreateVAO(unsigned int shader_program_handle, unsigned int vao_handle, unsigned int vbo_handle, unsigned int vertex_data_size, unsigned int vertex_data_stride, void* vertex_data, unsigned int vertex_index_data_size, void* vertex_index_data)
{
    RenderTaskCreateVAO* task = new RenderTaskCreateVAO();
    task->shader_program_handle_ = shader_program_handle;
    task->vao_handle_ = vao_handle;
    task->vbo_handle_ = vbo_handle;
    task->vertex_data_size_ = vertex_data_size;
    task->vertex_data_stride_ = vertex_data_stride;
    //拷贝数据
    task->vertex_data_ = (unsigned char*)malloc(vertex_data_size);
    memcpy(task->vertex_data_, vertex_data, vertex_data_size);
    task->vertex_index_data_size_ = vertex_index_data_size;
    //拷贝数据
    task->vertex_index_data_ = (unsigned char*)malloc(vertex_index_data_size);
    memcpy(task->vertex_index_data_, vertex_index_data, vertex_index_data_size);
    RenderTaskQueue::Push(task);
}

void RenderTaskProducer::ProduceRenderTaskUpdateVBOSubData(unsigned int vbo_handle, unsigned int vertex_data_size,
    void* vertex_data) {
    RenderTaskUpdateVBOSubData* task = new RenderTaskUpdateVBOSubData();
    task->vbo_handle_ = vbo_handle;
    task->vertex_data_size_ = vertex_data_size;
    //拷贝数据
    task->vertex_data_ = (unsigned char*)malloc(vertex_data_size);
    memcpy(task->vertex_data_, vertex_data, vertex_data_size);
    RenderTaskQueue::Push(task);
}

void RenderTaskProducer::ProduceRenderTaskSetEnableState(unsigned int state, bool enable) {
    RenderTaskSetEnableState* task = new RenderTaskSetEnableState();
    task->state_ = state;
    task->enable_ = enable;
    RenderTaskQueue::Push(task);
}

void RenderTaskProducer::ProduceRenderTaskSetBlenderFunc(unsigned int source_blending_factor,
    unsigned int destination_blending_factor) {
    RenderTaskSetBlenderFunc* task = new RenderTaskSetBlenderFunc();
    task->source_blending_factor_ = source_blending_factor;
    task->destination_blending_factor_ = destination_blending_factor;
    RenderTaskQueue::Push(task);
}

void RenderTaskProducer::ProduceRenderTaskSetUniformMatrix4fv(unsigned int shader_program_handle,
    const char* uniform_name, bool transpose, glm::mat4& matrix) {
    RenderTaskSetUniformMatrix4fv* task = new RenderTaskSetUniformMatrix4fv();
    task->shader_program_handle_ = shader_program_handle;
    task->uniform_name_ = static_cast<char*>(malloc(strlen(uniform_name) + 1));
    strcpy(task->uniform_name_, uniform_name);
    task->transpose_ = transpose;
    task->matrix_ = matrix;
    RenderTaskQueue::Push(task);
}

void RenderTaskProducer::ProduceRenderTaskActiveAndBindTexture(unsigned int texture_uint, unsigned int texture_handle) {
    RenderTaskActiveAndBindTexture* task = new RenderTaskActiveAndBindTexture();
    task->texture_uint_ = texture_uint;
    task->texture_handle_ = texture_handle;
    RenderTaskQueue::Push(task);
}

void RenderTaskProducer::ProduceRenderTaskSetUniform1i(unsigned int shader_program_handle, const char* uniform_name,
    int value) {
    RenderTaskSetUniform1i* task = new RenderTaskSetUniform1i();
    task->shader_program_handle_ = shader_program_handle;
    task->uniform_name_ = static_cast<char*>(malloc(strlen(uniform_name) + 1));
    strcpy(task->uniform_name_, uniform_name);
    task->value_ = value;
    RenderTaskQueue::Push(task);
}

void RenderTaskProducer::ProduceRenderTaskBindVAOAndDrawElements(unsigned int vao_handle, unsigned int vertex_index_num) {
    RenderTaskBindVAOAndDrawElements* task = new RenderTaskBindVAOAndDrawElements();
    task->vao_handle_ = vao_handle;
    task->vertex_index_num_ = vertex_index_num;
    RenderTaskQueue::Push(task);
}