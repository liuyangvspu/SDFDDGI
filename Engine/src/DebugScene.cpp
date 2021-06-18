#include "DebugScene.h"

namespace gip{

    void DebugScene::load(){
        _shader.loadShader(GIP_INTERNAL_SHADER("passthrough.vert"), GIP_INTERNAL_SHADER("passthrough.frag"));
        float vertices[] = {
            -0.5f, -0.5f, 0.0f,
            0.5f, -0.5f, 0.0f,
            0.0f,  0.5f, 0.0f
        };  
        unsigned int VBO;
        unsigned int VAO;
        glGenVertexArrays(1, &VAO);  
        glBindVertexArray(VAO);

        glGenBuffers(1, &VBO);  
        glBindBuffer(GL_ARRAY_BUFFER, VBO);  
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);


        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);  
    }
    void DebugScene::update(){}
    void DebugScene::render(){
        _shader.use();
        glDrawArrays(GL_TRIANGLES, 0, 3);
    }
    void DebugScene::unload(){}

}