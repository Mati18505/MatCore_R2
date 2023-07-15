#include "pch.h"

#include "Platform/Windows/WindowsInput.h"
#include "Application.h"
#include <GLFW/glfw3.h>
#include <MeshComponent.h>
extern MatCore::Application* applicationP;

namespace MatCore {
	bool WindowsInput::IsKeyPressedImpl(int keyCode)
	{
		auto window = applicationP->window;
		auto state = glfwGetKey(window, keyCode);
		return state == GLFW_PRESS || state == GLFW_REPEAT;
	}
	bool WindowsInput::IsMouseButtonPressedImpl(int button)
	{
		auto window = applicationP->window;;
		auto state = glfwGetMouseButton(window, button);
		return state == GLFW_PRESS;
	}
	std::pair<float, float> WindowsInput::GetMousePositionImpl()
	{
		auto window = applicationP->window;
		double xpos, ypos;
		glfwGetCursorPos(window, &xpos, &ypos);
		return { (float)xpos, (float)ypos };
	}
	float WindowsInput::GetMouseXImpl()
	{
		auto [x, y] = GetMousePositionImpl();
		return x;
	}
	float WindowsInput::GetMouseYImpl()
	{
		auto [x, y] = GetMousePositionImpl();
		return y;
	}
}