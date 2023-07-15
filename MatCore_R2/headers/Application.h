#pragma once
struct GLFWwindow;
#undef CreateWindow //windows
namespace MatCore {
	class Renderer;
	class Scene;
	class Event;
	class WindowResizeEvent;
	class Application {
	public:
		void RunApp();
		GLFWwindow* window;
		Renderer* renderer;
		Scene* scene;
		double deltaTime = 0;
		
		Application();
		~Application();

		int WindowWidth() { return windowWidth; }
		int WindowHeight() { return windowHeight; }
	private:
		friend class Renderer;

		int windowWidth{ 1366 };
		int windowHeight{ 768 };

		double lastFrameAppTime = 0;

		void InitializeApp();
		void MainLoop();

		void CreateWindow();
		void CloseWindow();
		bool WindowShouldClose();
		void OnEvent(Event& e);
		bool WindowResizeCallback(WindowResizeEvent& e);

		void InitGL();

		Scene* ApplicationStart(); // zdefiniowane przez klienta
	};
}