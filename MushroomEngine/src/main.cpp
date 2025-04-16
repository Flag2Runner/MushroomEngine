#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

void FrameBufferSizeCalback(GLFWwindow* window,int width, int height )
{
	glViewport(0, 0, width, height);
}

void ProcessInput(GLFWwindow* window)
{
	if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, 1);
	}
}

int main()
{
	glfwInit();
	int windowWidth = 1280;
	int windowHeight = 720;

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(windowWidth, windowHeight, "Mushroom", NULL, NULL);
	glfwMakeContextCurrent(window);

	if(window == NULL)
	{
		std::cout << "Failed to create the GLFW Window" << std::endl;
		return -1;
	}

	int Loaded = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
	if(Loaded == 0)
	{
		std::cout << "Failed to initialize OpenGl context" << std::endl;
		return -1;
	}

	glViewport(0,0,windowWidth, windowHeight);

	glfwSetFramebufferSizeCallback(window, FrameBufferSizeCalback);

	glClearColor(1.f, .3f, 0.f, 1.f);
	std::cout<<"Load OpenGL Successfully" << std::endl;

	while (!glfwWindowShouldClose(window))
	{
		ProcessInput(window);
		glfwPollEvents();
		glClear(GL_COLOR_BUFFER_BIT);
		glfwSwapBuffers(window);
	}

	glfwTerminate();
	return 0;
	
}