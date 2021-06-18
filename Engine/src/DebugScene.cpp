#include "DebugScene.h"

namespace gip{

    void DebugScene::load(){
        //_shader.loadShader(GIP_INTERNAL_SHADER("passthrough.vert"), GIP_INTERNAL_SHADER("RayMarching_orig.glsl"));
        _shader.loadShader(GIP_INTERNAL_SHADER("passthrough.vert"), GIP_INTERNAL_SHADER("RayMarching_incl.glsl"));
        float ext = 0.95f;
        float vertices[] = {
            -ext, -ext, 1, 1.0f,    1.0f, 0.0f, 1.0f, 1.0f,    
            -ext, ext, 1,1.0f,     1.0f, 0.0f, 1.0f, 1.0f,
            ext, ext, 1, 1.0f,     1.0f, 0.0f, 1.0f, 1.0f,
            
            -ext, -ext, 1, 1.0f,    1.0f, 0.0f, 1.0f, 1.0f,    
            ext, -ext, 1,1.0f,     1.0f, 0.0f, 1.0f, 1.0f,
            ext, ext, 1, 1.0f,     1.0f, 0.0f, 1.0f, 1.0f
        };  
        unsigned int VBO;
        unsigned int VAO;
        glGenVertexArrays(1, &VAO);  
        glBindVertexArray(VAO);

        glGenBuffers(1, &VBO);  
        glBindBuffer(GL_ARRAY_BUFFER, VBO);  
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);


        glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
        glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(4 * sizeof(float)));
        glEnableVertexAttribArray(0);  
        glEnableVertexAttribArray(1);  
    }
    void DebugScene::update(){}
    void DebugScene::render(){
        _shader.use();
        _shader.uniform_set1Float("u_time", glfwGetTime());
        glDrawArrays(GL_TRIANGLES, 0, 6);
    }
    void DebugScene::unload(){}

}