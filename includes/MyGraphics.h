#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <sstream>

class MyGraphics
{
private:
    
public:
    MyGraphics(/* args */) {}
    ~MyGraphics() {}

    struct ShaderProgramSource 
    {
        std::string VertexSource;
        std::string FragmentSource;
    };
    enum class ShaderType {
        NONE = -1,
        VERTEX = 0,
        FRAGMENT = 1
    };

    static ShaderProgramSource ParseShader(const std::string& filePath) 
    {
        std::ifstream stream(filePath);
        std::string line;
        std::stringstream ss[2];
        ShaderType type = ShaderType::NONE;
        while(std::getline(stream, line )){
            if(line.find("#shader") != std::string::npos)
            {
                if(line.find("vertex") != std::string::npos)
                {
                    type = ShaderType::VERTEX;
                }
                else if(line.find("fragment") != std::string::npos)
                {
                    type = ShaderType::FRAGMENT;
                }
            }
            else 
            {
                ss[(int)type] << line << "\n";
            }
        }
        return { 
            ss[(int)ShaderType::VERTEX].str(), 
            ss[(int)ShaderType::FRAGMENT].str()
        };
    }
    static int CompileShader(GLenum type, const std::string& shader)
    {
        uint32_t id = glCreateShader(type);
        const char* src = shader.c_str();
        glShaderSource(id , 1 , &src , nullptr);
        glCompileShader(id);

        int result;
        glGetShaderiv(id, GL_COMPILE_STATUS , &result);
        if(result == GL_FALSE) 
        {
            int length;
            glGetShaderiv(id , GL_INFO_LOG_LENGTH, &length);
            char* message = (char* ) alloca(length * sizeof(char));
            glGetShaderInfoLog(id , length ,&length, message);
            std::cout<< "Failed to compile shader." << std::endl;
            std::cout<< message << std::endl;
            glDeleteShader(id);
            return 0;
        }
        return id;
    }

    static int CreateShader(const std::string& vertexShader, const std::string& fragmentShader) 
    {
        uint32_t program = glCreateProgram();
        uint32_t vs = MyGraphics::CompileShader(GL_VERTEX_SHADER, vertexShader);
        uint32_t fs = MyGraphics::CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

        glAttachShader(program , vs);
        glAttachShader(program , fs);
        glLinkProgram(program);
        glValidateProgram(program);

        glDeleteShader(vs);
        glDeleteShader(fs);
        return program;
    }
};
