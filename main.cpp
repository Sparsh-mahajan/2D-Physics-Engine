
#include <GLFW/glfw3.h>
#include <iostream>

// I just have a few comments.

// Also you will need to have the main.cpp in the root dir for this build task to work. When I fix it in my own project I will send the fix.
// Make sure you have glfw3.dll and glew32.dll in root dir as well. Any questions about the building just ask. 

// First I wouldn't use using namespace std if you want to know why there is a cherno video on it but it basically is for readability and there are a few other reasons.
using namespace std;

int main()
{
    cout<<"A nondescript C++ program using the GLFW library, coded and built using VSCode"<<endl;
    cout<<"Initializing Graphics Library FramWork (GLFW)"<<endl;
    
    // Also if you are error checking this you best out a comment telling you why it failed instead of just returning
    if(!glfwInit())
    {
        return -1;
    }

    auto gameWindow = glfwCreateWindow(640, 480, "GLFW Test App", NULL, NULL);
    if(!gameWindow)
    {
        glfwTerminate();
        return -1;
    }

    // I'd have this up at the start as it makes it easier for readability
    glfwMakeContextCurrent(gameWindow);

    // Application (Game) loop
    while(!glfwWindowShouldClose(gameWindow))
    {
        glClear(GL_COLOR_BUFFER_BIT);


        glfwSwapBuffers(gameWindow);
        glfwPollEvents();
    }

    glfwTerminate();    
    return 0;
}
