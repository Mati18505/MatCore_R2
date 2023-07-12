#pragma once

namespace MatCore {
	class Input {
	public:
		static bool IsKeyPressed(int keyCode) { return instance->IsKeyPressedImpl(keyCode); }
		static bool IsMouseButtonPressed(int button) { return instance->IsMouseButtonPressedImpl(button); }
		static std::pair<float, float> GetMousePosition() { return instance->GetMousePositionImpl(); }
		static float GetMouseX() { return instance->GetMouseXImpl(); }
		static float GetMouseY() { return instance->GetMouseYImpl(); }

	protected:
		virtual bool IsKeyPressedImpl(int keyCode) = 0;

		virtual bool IsMouseButtonPressedImpl(int button) = 0;
		virtual std::pair<float, float> GetMousePositionImpl() = 0;
		virtual float GetMouseXImpl() = 0;
		virtual float GetMouseYImpl() = 0;

	private:
		friend class Application;
		static std::unique_ptr<Input> instance;
	};
}
