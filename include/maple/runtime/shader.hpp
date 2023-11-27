#pragma once

#include <glad/glad.h>


#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Shader {
public:
    // the program ID
    unsigned int ID;

    // constructor reads and builds the shader
    Shader(const char* vertexPath, const char* fragmentPath);

    void use();

    void setBool(const std::string &name, bool value) const;
    void setInt(const std::string &name, int value) const;
    void setFloat(const std::string &name, float value) const;

    void setVec3f(const std::string &name, float value1, float value2, float value3) const;

private:
    void checkCompileErrors(unsigned int shader, std::string type);

};
