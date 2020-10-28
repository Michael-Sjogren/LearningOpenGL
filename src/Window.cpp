#include "../includes/Window.h"

void Window::Init(const char* windowTitle, int width, int height)
{
    if(glfwInit() == GLFW_FALSE)
    {
        throw std::runtime_error("Failed to initalize glfw");
    }
    window = glfwCreateWindow(width , height , windowTitle, nullptr,nullptr);

    if(window == nullptr){
        throw std::runtime_error("Failed to create window");
    }

    glfwMakeContextCurrent(window);
    GLenum result = glewInit();
    if(GLEW_OK != result)
    {
        throw std::runtime_error("Failed to initalize glew");
    }

}

void Window::ShowWindow()
{
    std::cout << "OpenGL Version: " << glGetString(GL_VERSION) << " \n";
    while(!glfwWindowShouldClose(window))
    {
        glClearColor(0.1f , 0.1f , 0.1f , 0.1f);
        glClear(GL_COLOR_BUFFER_BIT);

        DrawTriangle();
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}

void Window::DrawTriangle()
{
    glBegin(GL_TRIANGLES);
    glVertex2f(-0.5f,-0.5f);
    glVertex2f(0.0f, 0.5f);
    glVertex2f(0.5f, -0.5f);
    glEnd();
}

void Window::CleanUp()
{
    glfwDestroyWindow(window);
    glfwTerminate();
}