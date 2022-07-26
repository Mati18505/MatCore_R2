#pragma once

namespace MatCore {
	class Scene;
	class SceneSerializer {
	public:
		static void Serialize(Scene& scene, const char* path);
		static bool DeSerialize(Scene& scene, const char* path);
	};
}
