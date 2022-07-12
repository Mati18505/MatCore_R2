#pragma once
struct GLFWwindow;
namespace MatCore {
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
		friend class Renderer;

		int windowWidth{ 1366 };
		int windowHeight{ 768 };

		void InitializeApp();
		void MainLoop();

		void CreateWindow();
		void CloseWindow();
		bool WindowShouldClose();
		static void WindowFramebufferSizeCallback(GLFWwindow* window, int width, int height);
		static void WindowCursorPosCallback(GLFWwindow* window, double xpos, double ypos);
		static void WindowKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
		static void WindowMouseButtonCallback(GLFWwindow* window, int button, int action, int mods);

		void InitGL();

		Scene* ApplicationStart(); // zdefiniowane przez klienta
	};
}