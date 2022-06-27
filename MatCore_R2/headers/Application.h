#pragma once

struct GLFWwindow;
class Renderer;
class Application {
public:
	void RunApp();
	GLFWwindow* window;
	Renderer* renderer;
private:
	int windowWidth{ 800 };
	int windowHeight{ 600 };

	void CreateWindow();
	void CloseWindow();
	bool WindowShouldClose();
	void MainLoop();
	void InitGL();
};