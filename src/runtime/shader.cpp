#include "runtime/shader.hpp"

Shader::Shader(const char* vertexPath, const char* fragmentPath) {
    std::string vertex_code;
    std::string fragment_code;
    std::ifstream vertex_file;
    std::ifstream fragment_file;

    vertex_file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    fragment_file.exceptions(std::ifstream::failbit | std::ifstream::badbit);

    try {
        vertex_file.open(vertexPath);
        fragment_file.open(fragmentPath);
        std::stringstream vertex_stream, fragment_stream;

        vertex_stream << vertex_file.rdbuf();
        fragment_stream << fragment_file.rdbuf();

        vertex_file.close();
        fragment_file.close();

        vertex_code = vertex_stream.str();
        fragment_code = fragment_stream.str();
    }catch (std::ifstream::failure e){
        std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
    }

    const char* vertex_shader_code = vertex_code.c_str();
    const char* fragment_shader_code = fragment_code.c_str();

    // compile shaders
    unsigned int vertex, fragment;
    //vertex shader
    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vertex_shader_code, NULL);
    glCompileShader(vertex);
    checkCompileErrors(vertex, "VERTEX");
    //fragment shader
    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fragment_shader_code, NULL);
    glCompileShader(fragment);
    checkCompileErrors(fragment, "FRAGMENT");

    // shader program
    ID = glCreateProgram();
    glAttachShader(ID, vertex);
    glAttachShader(ID, fragment);
    glLinkProgram(ID);
    checkCompileErrors(ID, "PROGRAM");

    // delete the shaders as they're linked into our program now and no longer necessary
    glDeleteShader(vertex);
    glDeleteShader(fragment);

}

void Shader::use() {
    glUseProgram(ID);
}

void Shader::setBool(const std::string &name, bool value) const {
    glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
}
void Shader::setInt(const std::string &name, int value) const {
    glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}
void Shader::setFloat(const std::string &name, float value) const {
    glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::setVec3f(const std::string &name, float value1, float value2, float value3) const {
    glUniform3f(glGetUniformLocation(ID, name.c_str()), value1, value2, value3);
}


void Shader::checkCompileErrors(unsigned int shader, std::string type)
    {
        int success;
        char infoLog[1024];
        if (type != "PROGRAM")
        {
            glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
            if (!success)
            {
                glGetShaderInfoLog(shader, 1024, NULL, infoLog);
                std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
            }
        }
        else
        {
            glGetProgramiv(shader, GL_LINK_STATUS, &success);
            if (!success)
            {
                glGetProgramInfoLog(shader, 1024, NULL, infoLog);
                std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
            }
        }
    }