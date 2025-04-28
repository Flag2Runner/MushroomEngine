#include "Framework/Application.h"
#include <iostream>
#include "Rendering/Shader.h"

namespace mr
{
    Application::Application(int windowWidth, int windowHeight, const std::string& windowTitle)
    {
        InitWindow(windowWidth, windowHeight, windowTitle);    
    }

    Application::~Application()
    {
		std::cout << "terminating glfw" << std::endl;
        glfwTerminate();
    }

    void Application::Run()
    {
        float triangleVertexData[]
        {
            -0.5, -0.5, 0.0,
            0, 0.5, 0.0,
            0.5, -0.5, 0.0
        };

        unsigned int vertexArrayObjectId;
        glGenVertexArrays(1, &vertexArrayObjectId);

        unsigned int vertexBufferObjectid;
        glGenBuffers(1, &vertexBufferObjectid);

        glBindVertexArray(vertexArrayObjectId);
        glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObjectid);
        glBufferData(GL_ARRAY_BUFFER, sizeof(triangleVertexData), triangleVertexData,GL_STATIC_DRAW);

        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

        //Shader...
        Shader shader = Shader("vertex", "fragment");
        shader.UserShaderProgram();


        while(!glfwWindowShouldClose(mWindow))
	    {
		    ProcessInput(mWindow);
		    glfwPollEvents();		
		    glClear(GL_COLOR_BUFFER_BIT);
            glDrawArrays(GL_TRIANGLES, 0, 3);
		    glfwSwapBuffers(mWindow);
	    }
    }

    void Application::InitWindow(int windowWidth, int windowHeight, const std::string &windowTitle)
    {
        glfwInit();

	    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	    mWindow = glfwCreateWindow(windowWidth, windowHeight, windowTitle.c_str(), NULL, NULL);
	    glfwMakeContextCurrent(mWindow);

	    if(mWindow == NULL)
	    {
		    std::cout << "Failed to create the GLFW window"	 << std::endl;
		    return;
	    }

	    int Loaded = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
	    if(Loaded == 0)	
	    {
		    std::cout << "Failed to initialize OpenGL context" << std::endl;
		    return;
	    }

	    glViewport(0,0,windowWidth,windowHeight);
	    glfwSetFramebufferSizeCallback(mWindow, 
            [](GLFWwindow* window, int width, int height)->void
            {
                glViewport(0, 0, width, height);
            }
        );

	    glClearColor(0.2f, .3f, 0.f, 1.f);
	    std::cout << "Load OpenGL successfully!" << std::endl;
    }
    void Application::ProcessInput(GLFWwindow *window)
    {
        if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	    {
		    glfwSetWindowShouldClose(window, GLFW_TRUE);
	    }
    }
}
