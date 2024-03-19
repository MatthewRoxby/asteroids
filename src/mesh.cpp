#include "mesh.h"

Mesh::Mesh(std::vector<float> vertices, std::vector<float> uvs, std::vector<unsigned int> indices, int mode){
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    drawMode = mode;
    LoadAttribute(0, vertices, 3);
    attributeNum = 1;

    if(!uvs.empty()){
        std::cout << "valid uv" << std::endl;
        LoadAttribute(1, uvs, 2);
        attributeNum = 2;
    }

    if(!indices.empty()){
        std::cout << "valid indices: " << indices.size() << std::endl;
        unsigned int ebo;
        glGenBuffers(1, &ebo);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);
        glBindVertexArray(0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        //glDeleteBuffers(1, &ebo);
        buffers.emplace_back(ebo);

        drawCount = indices.size();
        elements = true;
    }
    else{
        drawCount = vertices.size() / 3;
        elements = false;
    }

    std::cout << "drawcount: " << drawCount << std::endl;
}

void Mesh::LoadAttribute(int index, std::vector<float> data, int elementsPerItem, bool normalised){
    unsigned int vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    
    std::cout << "elements in index " << index << ": " << data.size() / elementsPerItem << std::endl;

    glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(float), &data[0], GL_STATIC_DRAW);

    glVertexAttribPointer(index, elementsPerItem, GL_FLOAT, normalised, elementsPerItem * sizeof(float), (void*)0);
    
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    //glDeleteBuffers(1, &vbo);
    buffers.emplace_back(vbo);
}

void Mesh::CleanUp(){
   std::cout << "Cleaning up mesh..." << std::endl;
    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(buffers.size(), &buffers[0]);
}

void Mesh::Bind(){
    std::cout << "binding..." << std::endl;

    glBindVertexArray(vao);
    for(int i = 0; i < attributeNum; i++){
        std::cout << "enabling: " << i << "..." << std::endl;
        glEnableVertexAttribArray(i);
    }
}

void Mesh::Draw(){
    if(elements){
        glDrawElements(drawMode, drawCount, GL_UNSIGNED_INT, 0);
    std::cout << "drawing " << drawCount << " things, here we go." << std::endl;
    }
    else{
        glDrawArrays(drawMode, 0, drawCount);
    }
}

