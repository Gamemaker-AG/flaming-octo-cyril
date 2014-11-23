#include "ShaderUtilities.hpp"
#include <GL/glew.h>
#include <iostream>
#include <fstream>

namespace Shaders{
    std::string read_src(std::string path){
        std::ifstream ifs(path.c_str());
        std::string source((std::istreambuf_iterator<char>(ifs)),
          (std::istreambuf_iterator<char>()));
        ifs.close();
        return source;
    }

    GLuint compile_shader(GLenum type,std::string src){
        GLuint shader = glCreateShader(type);

        //make source usable by OpenGL
        const GLchar* c_src = src.c_str();
        const GLint len = src.length();
        glShaderSource(shader, 1, &c_src, &len);

        glCompileShader(shader);

        //print compilation log
        GLint log_length;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &log_length);
        GLchar log[log_length];
        glGetShaderInfoLog(shader, log_length, NULL, log);

        if(log_length > 1){
          std::cout << "Compiling Shader:\n" << log;
          std::cout.flush();
        }


        return shader;
    }

    GLuint link_program(GLuint *shaders, int shader_count){

        GLuint program = glCreateProgram();

        for(int i = 0; i < shader_count; i++){
            glAttachShader(program, shaders[i]);
        }

        glLinkProgram(program);

        //print log
        GLint log_length;
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &log_length);
        GLchar log[log_length];
        glGetProgramInfoLog(program, log_length, NULL, log);

        if(log_length > 1){
          std::cout << "Linking Program:\n" << log;;
          std::cout.flush();
        }

        return program;
    }
}

