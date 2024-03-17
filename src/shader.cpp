#include "shader.h"

Shader::Shader(const char* vertexPath, const char* fragmentPath){
	unsigned int vertex, fragment, program;
	int success;
	char infoLog[512];
	std::ifstream vertexFile, fragmentFile;
	std::string vertexCode, fragmentCode;
	const char *vertexSource = "", *fragmentSource = "";

	vertex = glCreateShader(GL_VERTEX_SHADER);
	
	vertexFile = std::ifstream(vertexPath);

	if(vertexFile.is_open()){
		std::string s;
		while(std::getline(vertexFile, s)){
			vertexCode += s + "\n";
		}

		vertexFile.close();
	}
	else{
		std::cout << "VERTEX SHADER FILE NOT FOUND" << std::endl;
	}

	vertexSource = vertexCode.c_str();
	
	glShaderSource(vertex, 1, &vertexSource, NULL);
	glCompileShader(vertex);

	glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);

	if(!success){
		glGetShaderInfoLog(vertex, 512, NULL, infoLog);
		std::cout << "VERTEX SHADER ERROR::" << infoLog << std::endl;
	}

	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	
	fragmentFile = std::ifstream(fragmentPath);

	if(fragmentFile.is_open()){
		std::string s;
		while(std::getline(fragmentFile, s)){
			fragmentCode += s + "\n";
		}

		fragmentFile.close();
	}
	else{
		std::cout << "FRAGMENT SHADER FILE NOT FOUND" << std::endl;
	}

	fragmentSource = fragmentCode.c_str();
	
	glShaderSource(fragment, 1, &fragmentSource, NULL);
	glCompileShader(fragment);

	glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);

	if(!success){
		glGetShaderInfoLog(fragment, 512, NULL, infoLog);
		std::cout << "FRAGMENT SHADER ERROR::" << infoLog << std::endl;
	}
	
	program = glCreateProgram();
	glAttachShader(program, vertex);
	glAttachShader(program, fragment);
	glLinkProgram(program);

	glGetProgramiv(program, GL_LINK_STATUS, &success);

	if(!success){
		glGetProgramInfoLog(program, 512, NULL, infoLog);
		std::cout << "PROGRAM LINK ERROR::" << infoLog << std::endl;
	}

	glDeleteShader(vertex);
	glDeleteShader(fragment);

	this->program = program;

}

void Shader::CleanUp(){
	glDeleteProgram(this->program);
}

void Shader::Use(){
	glUseProgram(this->program);
}

int Shader::GetUniformLocation(const char* name){
	return glGetUniformLocation(this->program, name);
}

void Shader::SetUniform1(const char* name, float value){
	glUniform1f(GetUniformLocation(name), value);
}

void Shader::SetUniform1(const char* name, int value){
	glUniform1i(GetUniformLocation(name), value);
}

void Shader::SetUniform1(const char* name, bool value){
	glUniform1i(GetUniformLocation(name), value);
}

void Shader::SetUniform2(const char* name, glm::vec2 value){
	glUniform2f(GetUniformLocation(name), value.x, value.y);
}


void Shader::SetUniform3(const char* name, glm::vec3 value){
	glUniform3f(GetUniformLocation(name), value.x, value.y, value.z);
}


void Shader::SetUniform4(const char* name, glm::vec4 value){
	glUniform4f(GetUniformLocation(name), value.x, value.y, value.z, value.w);
}

void Shader::SetUniformMatrix(const char* name, bool transpose, glm::mat4 value){
	glUniformMatrix4fv(GetUniformLocation(name), 1, transpose, &value[0][0]);
}
