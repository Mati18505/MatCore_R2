#pragma once
#include "Cameras/SceneCamera.h"

namespace MatCore {
	struct CameraComponent {
		CameraComponent() = default;
		SceneCamera camera;
		bool primary = true;	//TODO: przenie�� to do Scene
	};
}