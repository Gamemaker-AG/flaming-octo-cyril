#ifndef SHADERUTILITIES_HPP
#define SHADERUTILITIES_HPP

#include <string>
#include <GL/glew.h>

namespace Shaders{
    std::string read_src(std::string path);
    GLuint compile_shader(GLenum type,std::string src);
    GLuint link_program(GLuint *shaders, int shader_count);
}


#endif //SHADERUTILITIES_HPP
