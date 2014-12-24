#define GLM_FORCE_RADIANS
#include <iostream>
#include <SFML/Window.hpp>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "graphics/ShaderUtilities.hpp"


//test program
int main(){
    //initialize window and GLEW
    sf::ContextSettings contextSettings;
    contextSettings.majorVersion = 3;
    contextSettings.minorVersion = 0;
    sf::Window window(sf::VideoMode(800,600,32), "TEST!", sf::Style::Default, contextSettings);
    glewInit();

    //create a triangle
    GLfloat* triangle = new GLfloat[24]{
        -1,-1,0,0,0,1,0,0,
        0,1,1,0,0,1,0.5f,1.0f,
        1,-1,-1,0,0,1,1,0
    };

    //create a vertex array object
    GLuint vaos[1] = {0};
    glGenVertexArrays(1, vaos);
    glBindVertexArray(vaos[0]);

    //create a vertex buffer object
    GLuint vbos[1]={0};
    glGenBuffers(1, vbos);
    glBindBuffer(GL_ARRAY_BUFFER, vbos[0]);
    glBufferData(GL_ARRAY_BUFFER,3*8*sizeof(GLfloat), triangle, GL_STATIC_DRAW);


    //position
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,sizeof(GLfloat) * 8, 0);
    //normal
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE,sizeof(GLfloat) * 8, (GLvoid*)12);
    //texture coordinates
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2,2,GL_FLOAT,GL_FALSE,sizeof(GLfloat) * 8, (GLvoid*)24);



    glBindVertexArray(0);

    glBindBuffer(GL_ARRAY_BUFFER,0);
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(2);



    delete[] triangle;

    glClearColor(0.0f,0.3f,0.3f,1.0f);

    std::string vss = Shaders::read_src("data/vertex.glsl");
    std::string fss = Shaders::read_src("data/fragment.glsl");

    GLuint shaders[2];
    shaders[0] = Shaders::compile_shader(GL_VERTEX_SHADER, vss);
    shaders[1] = Shaders::compile_shader(GL_FRAGMENT_SHADER, fss);

    GLuint program = Shaders::link_program(shaders, 2);

    float rotation = 0;

    while(window.isOpen()){
        rotation += 0.0001;
        sf::Event event;
        while(window.pollEvent(event)){
            if(event.type == sf::Event::Closed)
                window.close();
            if(event.type == sf::Event::Resized)
                glViewport(0,0,window.getSize().x,window.getSize().y);
        }
        GLenum i = glGetError();

        if(i != GL_NO_ERROR){
            std::cout << "GL_ERROR:" << i;
            std::cout.flush();
        }

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glUseProgram(program);
        glBindVertexArray(vaos[0]);

        glm::mat4 mvp = glm::rotate(glm::mat4(1.0f),rotation,glm::vec3(0,1,0));

        glUniformMatrix4fv(glGetUniformLocation(program,"MVP"), 1, GL_FALSE, glm::value_ptr(mvp));

        glDrawArrays(GL_TRIANGLES,0,3);

        glBindVertexArray(0);

        glUseProgram(0);

        window.display();
    }


    glDeleteVertexArrays(1, vaos);
    glDeleteBuffers(1, vbos);
    return 0;
}
