#pragma once
#include <string>
#include <unordered_map>
class Shader
{
public:
	void CreateGPUProgram(const char * vertex_shader_text, const char* fragment_shader_text);  
	void Parse(std::string shader_name);
	unsigned int GetProgramId(){ return gl_program_id_;}
	void Active();
private:
	unsigned int gl_program_id_;
	std::string shader_name_;
public:
	static Shader* Find(std::string shader_name);//查找或创建Shader
private:
	static std::unordered_map<std::string, Shader*> kShaderMap;//已经创建的Shader
};	

