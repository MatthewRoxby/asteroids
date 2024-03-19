#pragma once
#include <cstddef>
#include <glad/glad.h>
#include <optional>
#include <vector>
#include <iostream>

class Mesh{
private:
	int attributeNum;
	unsigned int vao;
	int drawCount;
	int drawMode;
	bool elements;
	std::vector<unsigned int> buffers;

public:
	Mesh(std::vector<float> vertices, std::vector<float> uvs, std::vector<unsigned int> indices, int drawMode = GL_LINE_LOOP);

	void LoadAttribute(int index, std::vector<float> data, int elementsPerItem, bool normalised = false);
	void CleanUp();
	void Bind();
	void Draw();
};
