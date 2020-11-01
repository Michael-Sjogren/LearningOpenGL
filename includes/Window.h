#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <cassert>
#pragma once
class Window
{
private:
    /* data */
    GLFWwindow* window;
    int width, height;
public:
    Window(){}
    ~Window(){}
    void DrawTriangle();
    void Init(const char* windowTitle, int width, int height);
    void CleanUp();
    void ShowWindow();
    void ReSize(int w , int h);

    static void GLClearError()
    {
        while (glGetError() != GL_NO_ERROR);
    }

    static bool GLLogCall(const char* function, const char* file , int line)
    {
        while (GLenum error = glGetError())
        {
            std::cout << "[OpenGL ERROR]:" << "\t( " << std::hex << error << " ): " << function << " " << file << ": " << line << std::endl;
            return false;
        }
        
        return true;
    }
};
