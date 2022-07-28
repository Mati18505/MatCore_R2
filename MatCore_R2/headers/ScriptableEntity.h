#pragma once
#include "Entity.h"

namespace MatCore {
	//Klasa po której dziedzicz¹ wszystkie skrypty natywne
	class ScriptableEntity {
	public:
		template<typename T>
		T& GetComponent(){
			return entity.GetComponent<T>();
		}
		template<typename T>
		bool HasComponent() {
			return entity.HasComponent<T>();
		}
		template<typename T>
		void RemoveComponent() {
			return entity.RemoveComponent<T>();
		}
		template<typename T, typename... Args>
		T& AddComponent(Args&&... args) {
			return entity.AddComponent<T>(std::forward<Args>(args)...);
		}

	protected:
		virtual void Create() {}
		virtual void Update() {}
		virtual void Destroy() {}
	private:
		Entity entity;
		friend class Scene;
	};
}
