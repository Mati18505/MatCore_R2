#pragma once
#include "ScriptableEntity.h"

namespace MatCore {
	struct NativeScriptComponent {
		ScriptableEntity* instance = nullptr;

		template <typename T>
		void Bind() {
			InstantiateScript = []() {return static_cast<ScriptableEntity*>(new T()); };
			DestroyScript = [](NativeScriptComponent* nsc) {delete nsc->instance; nsc->instance = nullptr; };
		}

	private:
		ScriptableEntity* (*InstantiateScript)();
		void(*DestroyScript)(NativeScriptComponent*);
		friend class Scene;
	};
}
