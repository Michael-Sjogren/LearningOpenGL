#include "../includes/Window.h"
#include "../includes/MyGraphics.h"
void Window::Init(const char *windowTitle, int width, int height)
{
    if (glfwInit() == GLFW_FALSE)
    {
        throw std::runtime_error("Failed to initalize glfw");
    }
    window = glfwCreateWindow(width, height, windowTitle, nullptr, nullptr);

    if (window == nullptr)
    {
        throw std::runtime_error("Failed to create window");
    }
    glfwMakeContextCurrent(window);
    GLenum result = glewInit();
    if (GLEW_OK != result)
    {
        throw std::runtime_error("Failed to initalize glew");
    }
}

void Window::ShowWindow()
{
    std::cout << "OpenGL Version: " << glGetString(GL_VERSION) << " \n";
    float verticies[] = {
        -0.5f, -0.5f,
        0.5f,  -0.5f,
        0.5f, 0.5f,
        -0.5f,  0.5f,
    };

    uint32_t indices[] = {
        0,1,2,
        2,3,0
    };
    
    uint32_t bufferId;
    glGenBuffers(1, &bufferId);
    glBindBuffer(GL_ARRAY_BUFFER, bufferId);
    glBufferData(GL_ARRAY_BUFFER, 4 * 2 * sizeof(float) , &verticies ,  GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2 , GL_FLOAT, GL_FALSE , sizeof(float) * 2 , 0);
    
    unsigned int ibo;
    glGenBuffers(1, &ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(unsigned int) , &indices ,  GL_STATIC_DRAW);
    

    auto shaderSrc = MyGraphics::ParseShader("../resources/shaders/Basic.shader");
    uint32_t program = MyGraphics::CreateShader(shaderSrc.VertexSource , shaderSrc.FragmentSource);
    glUseProgram(program);
    while (!glfwWindowShouldClose(window))
    {
        glClearColor(0.1f, 0.1f, 0.1f, 0.1f);
        glClear(GL_COLOR_BUFFER_BIT);
        glDrawElements(GL_TRIANGLES , 6 , GL_UNSIGNED_INT, nullptr);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteProgram(program);
}



void Window::ReSize(int w , int h)
{
    glfwGetWindowSize(window, &width , &height);
}

void Window::DrawTriangle()
{
    glBegin(GL_TRIANGLES);
    glVertex2f(-0.5f, -0.5f);
    glVertex2f(0.0f, 0.5f);
    glVertex2f(0.5f, -0.5f);
    glEnd();
}

void Window::CleanUp()
{
    glfwDestroyWindow(window);
    glfwTerminate();
}