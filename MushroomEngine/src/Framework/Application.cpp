#include "Framework/Application.h"
#include <iostream>
#include "Rendering/Shader.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

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
        glm::mat4 trans = glm::mat4(1.0f);
        trans = glm::rotate(trans, glm::radians(40.f), glm::vec3{0.0f, 0.0f, 1.0f});

        float triangleVertexData[]
        {
            -0.5, -0.5, 0.0,  1.f, 0.f, 0.f,
            -0.5,  0.5, 0.0,  0.f, 1.f, 0.f,
             0.5,  0.5, 0.0,  0.f, 0.f, 1.f,
             0.5, -0.5, 0.0,  0.f, 1.f, 0.f,
        };

        int indexData[]
        {
            0, 1, 2, 2, 3, 0
        };

        unsigned int vertexArrayObjectId;
        glGenVertexArrays(1, &vertexArrayObjectId);

        unsigned int vertexBufferObjectId;
        glGenBuffers(1, &vertexBufferObjectId);

        glBindVertexArray(vertexArrayObjectId);
        glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObjectId);
        glBufferData(GL_ARRAY_BUFFER, sizeof(triangleVertexData), triangleVertexData, GL_STATIC_DRAW);

        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0); 

        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float))); 

        // Element array buffer
        unsigned int elementArrayObjectId;
        glGenBuffers(1, &elementArrayObjectId);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementArrayObjectId);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indexData), indexData, GL_STATIC_DRAW);

        //Shader...
        Shader shader = Shader("vertex", "fragment");
        shader.UseShaderProgram();

        
        //model
        glm::mat4 modelMat = glm::mat4(1.0f);
        modelMat = glm::translate(modelMat, glm::vec3(0.f, 0.f, -10.f));

        //view
        glm::vec3 cameraLocation = glm::vec3(0.f, 0.f, 10.f);
        
        
        while(!glfwWindowShouldClose(mWindow))
        {
            ProcessInput(mWindow);
            glfwPollEvents();		
            glClear(GL_COLOR_BUFFER_BIT);
            //matricies
            //project
            int width, height;
            glfwGetWindowSize(mWindow, &width, &height);
            glm::mat4 projectionMat = glm::perspective(50.f, (float)width/(float)height, 0.1f, 3000.f);
            cameraLocation += glm::vec3(0.f, 0.f, -.1f);
            glm::mat4 viewMat = glm::lookAt(cameraLocation, cameraLocation + glm::vec3(0.f, 0.f, -1.f), glm::vec3(0.f, 1.f, 0.f));
            
            modelMat = glm::rotate(modelMat, glm::radians(2.f), glm::vec3(0.f, 1.f, 0.f));
            shader.SetUniformMat4("modelMat", modelMat);
            shader.SetUniformMat4("viewMat", viewMat);
            shader.SetUniformMat4("projectionMat", projectionMat);
            // glDrawArrays(GL_TRIANGLES, 0, 6);
            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
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

        glClearColor(1.f, .3f, 0.f, 1.f);
        std::cout << "Load OpenGL successfully!" << std::endl;       
    }

    void Application::ProcessInput(GLFWwindow *window)
    {
        if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        {
            glfwSetWindowShouldClose(window, 1);
        }
    }
}