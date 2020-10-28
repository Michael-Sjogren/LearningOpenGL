#include "../includes/Window.h"

void Window::Init(const char* windowTitle, int width, int height)
{
    if(glfwInit() == GLFW_FALSE){
        throw std::runtime_error("Failed to initalize glfw");
    }

    window = glfwCreateWindow(width , height , windowTitle, nullptr,nullptr);

    if(window == nullptr){
        throw std::runtime_error("Failed to create window");
    }

    glfwMakeContextCurrent(window);
}

void Window::ShowWindow()
{
    while(!glfwWindowShouldClose(window))
    {
        glClearColor(0.1f , 0.1f , 0.1f , 0.1f);
        glClear(GL_COLOR_BUFFER_BIT);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}

void Window::CleanUp()
{
    glfwDestroyWindow(window);
    glfwTerminate();
}