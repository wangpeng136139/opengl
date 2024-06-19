
#ifndef UNTITLED_MATERIAL_MATERIAL_H
#define UNTITLED_MATERIAL_MATERIAL_H
#include "../shader/render_shader_head.h"
#include "../textures/render_textures_head.h"

class Material
{
public:
	void Parse(std::string material_path);
	void SetUniformMatrix4fv(std::string shader_property_name, float* pointer);
	void SetUniform1i(std::string shader_property_name, int value);
	Shader* shader() { return shader_; }
	std::vector<std::pair<std::string, Texture2D*>>& textures() { return textures_; }
	void SetTexture(std::string property, Texture2D* texture2D);
private:
	Shader * shader_ = nullptr;
	std::vector<std::pair<std::string, Texture2D*>> textures_;
	std::vector<std::pair<std::string, float*>> uniform_matrix4fv_vec;
	std::vector<std::pair<std::string, int>> uniform_1i_vec;
};
#endif
