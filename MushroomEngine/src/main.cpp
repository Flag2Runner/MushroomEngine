#include <iostream>
#include "Framework/Application.h"

int main()
{
	mr::Application* app = new mr::Application(1280, 720, "Mushroom Engine");
	app->Run();
	delete app;
	return 0;
}