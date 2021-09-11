#include <malloc.h>
#include<GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>


// I just have a few comments.

// Also you will need to have the main.cpp in the root dir for this build task to work. When I fix it in my own project I will send the fix.
// Make sure you have glfw3.dll and glew32.dll in root dir as well. Any questions about the building just ask. 

// First I wouldn't use using namespace std if you want to know why there is a cherno video on it but it basically is for readability and there are a few other reasons.

static unsigned int CompileShader( unsigned int type,std::string& Source )
{
    unsigned int id = glCreateShader(type);
    const char* src = Source.c_str();
    glShaderSource(id, 1, &src, NULL);
    glCompileShader(id);

    int Result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &Result);
    if(Result == GL_FALSE)
    {
        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        char* message = (char*)(_alloca(length * sizeof(char)));
        glGetShaderInfoLog(id, length, &length, message);
        
        std::cout<<"Failed to compile"<<
        (type == GL_VERTEX_SHADER ? "Vertex" : "Fragment") <<"shader\n";
        std::cout<<message<<"\n";

        glDeleteShader(id);

        return 0;
    }
    return id;           
}
static unsigned int CreateShader(std::string& VertexShader, std::string& FragmentShader)
{
    unsigned int program =  glCreateProgram(); 
    unsigned int vs = CompileShader(GL_VERTEX_SHADER, VertexShader);
    unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, FragmentShader);

    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);
    glValidateProgram(program);

    glDeleteShader(vs);
    glDeleteShader(fs);
    
    return program;
}

int main()
{
    std::cout<<"A nondescript C++ program using the GLFW library, coded and built using VSCode"<<std::endl;
    std::cout<<"Initializing Graphics Library FramWork (GLFW)"<<std::endl;
    
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

    if(glewInit() != GLEW_OK)
    {
        std::cout<<"\nerror!";
    }

    float positions[] = {
        -0.5f, -0.5f,
         0.0f,  0.5f,
         0.5f, -0.5f
    };
    unsigned int Buffer;
    glGenBuffers(1, &Buffer);
    glBindBuffer(GL_ARRAY_BUFFER, Buffer);
    glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(float), positions, GL_DYNAMIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);

    std::string VertexShader = 
    "#version 330 core\n"
    "\n"
    "layout(location = 0) in vec4 Position;"
    "\n"
    "void main()\n"
    "{\n"
    "   gl_Position = Position;"
    "}\n";


    std::string FragmentShader = 
    "#version 330 core\n"
    "\n"
    "layout(location = 0) out vec4 Color;"
    "\n"
    "void main()\n"
    "{\n"
    "   Color = vec4(1.0, 0.0, 0.0, 1.0);\n"
    "}\n";

    unsigned int Shader = CreateShader(VertexShader, FragmentShader);
    glUseProgram(Shader);

    // Application (Game) loop
    while(!glfwWindowShouldClose(gameWindow))
    {
        glClear(GL_COLOR_BUFFER_BIT);

        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(gameWindow);
        glfwPollEvents();
    }

    glfwTerminate();    
    return 0;
}
