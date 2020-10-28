#define GLEW_STATIC
#include "includes/Window.h"
#include <stdexcept>
#include <iostream>
int main(int argc, char const *argv[])
{
    Window window = Window();
    try
    {
        window.Init("Learning OpenGL" , 800 , 600 );
        window.ShowWindow();
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    window.CleanUp();
    return 0;
}
