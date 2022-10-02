#include "GLEW/glew.h"
#include "game/App.h"
#include <iostream>

int main(void)
{

    App app;
    app.run();

    glfwTerminate();
    
    return 0;
}
