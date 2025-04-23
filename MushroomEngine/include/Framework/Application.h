#pragma once
#include <string>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace mr
{
    class Application
    {
    public:
        Application(int windowWidth, int windowHeight, const std::string& windowTitle);
        virtual ~Application();
        void Run();

    private:
        void InitWindow(int windowWidth, int windowHeight, const std::string& windowTitle);
        void ProcessInput(GLFWwindow* window);
        GLFWwindow* mWindow;

    };
}

