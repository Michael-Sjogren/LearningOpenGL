#include <GL/glew.h>
#include <GLFW/glfw3.h>
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
    void DrawTriangle();
    void Init(const char* windowTitle, int width, int height);
    void CleanUp();
    void ShowWindow();
};
