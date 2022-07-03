#pragma once

struct GLFWwindow;
class Renderer;
class Scene;
class Application {
public:
	void RunApp();
	GLFWwindow* window;
	Renderer* renderer;
	Scene* scene;
	Application();
	~Application();
private:
	friend class Camera;

	int windowWidth{ 800 };
	int windowHeight{ 600 };

	void InitializeApp();
	void MainLoop();

	void CreateWindow();
	void CloseWindow();
	bool WindowShouldClose();

	void InitGL();
};