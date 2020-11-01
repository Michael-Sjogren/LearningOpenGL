#include "../includes/Window.h"
#include "../includes/MyGraphics.h"


    #ifdef _MSC_VER
    #define ASSERT(x) if ((!x)) __debugbreak();
    #else
    #define ASSERT(x) if ((!x)) assert(false);
    #define GLCall(x) Window::GLClearError();\
        x;\
        ASSERT(Window::GLLogCall(#x, __FILE__, __LINE__))
    #endif

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
    GLCall(glGenBuffers(1, &bufferId));
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, bufferId));
    GLCall(glBufferData(GL_ARRAY_BUFFER, 4 * 2 * sizeof(float) , &verticies ,  GL_STATIC_DRAW));
    GLCall(glEnableVertexAttribArray(0));
    GLCall(glVertexAttribPointer(0, 2 , GL_FLOAT, GL_FALSE , sizeof(float) * 2 , 0));

    unsigned int ibo;
    GLCall(glGenBuffers(1, &ibo));
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo));
    GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(unsigned int) , &indices ,  GL_STATIC_DRAW));
    

    auto shaderSrc = MyGraphics::ParseShader("../resources/shaders/Basic.shader");
    uint32_t program = MyGraphics::CreateShader(shaderSrc.VertexSource , shaderSrc.FragmentSource);
    GLCall(glUseProgram(program));
    while (!glfwWindowShouldClose(window))
    {
        GLCall(glClearColor(0.1f, 0.1f, 0.1f, 0.1f));
        GLCall(glClear(GL_COLOR_BUFFER_BIT));
        GLCall(glDrawElements(GL_TRIANGLES , 6 , GL_UNSIGNED_INT, nullptr));
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
    GLCall(glBegin(GL_TRIANGLES));
    GLCall(glVertex2f(-0.5f, -0.5f));
    GLCall(glVertex2f(0.0f, 0.5f));
    GLCall(glVertex2f(0.5f, -0.5f));
    GLCall(glEnd());
}

void Window::CleanUp()
{
    glfwDestroyWindow(window);
    glfwTerminate();
}