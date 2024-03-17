#pragma once
#include <glad/glad.h>
#include <fstream>
#include <glm/glm.hpp>
#include <string>
#include <iostream>

class Shader{
private:
	int program;
public:
	Shader(const char* vertexPath, const char* fragmentPath);
	
	void CleanUp();
	
	void Use();
	
	int GetUniformLocation(const char* name);

	void SetUniform1(const char* name, float value);
	void SetUniform1(const char* name, int value);
	void SetUniform1(const char* name, bool value);

	void SetUniform2(const char* name, glm::vec2 value);

	void SetUniform3(const char* name, glm::vec3 value);

	void SetUniform4(const char* name, glm::vec4 value);
	
	void SetUniformMatrix(const char* name, bool transpose, glm::mat4 value);
};
