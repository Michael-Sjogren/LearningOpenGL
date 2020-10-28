#include <GLFW/glfw3.h>
#include <GL/gl.h>
#include <glm/vec2.hpp>
#include <iostream>
#pragma once
class Window
{
private:
    /* data */
    GLFWwindow* window;
public:
    Window(){}
    ~Window(){}

    void Init(const char* windowTitle, int width, int height);
    void CleanUp();
    void ShowWindow();
};
