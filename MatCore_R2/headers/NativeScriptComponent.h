#pragma once
#include "ScriptableEntity.h"

namespace MatCore {
	struct NativeScriptComponent {
		template <typename T>
		void Bind() {
			InstantiateScript = []() {return static_cast<ScriptableEntity*>(new T()); };
			DestroyScript = [](NativeScriptComponent* nsc) {delete nsc->instance; nsc->instance = nullptr; };
		}
		template <typename T>
		T* Get() {
			return static_cast<T*>(instance);
		}

	private:
		ScriptableEntity* instance = nullptr;
		ScriptableEntity* (*InstantiateScript)();
		void(*DestroyScript)(NativeScriptComponent*);
		friend class Scene;
	};
}
