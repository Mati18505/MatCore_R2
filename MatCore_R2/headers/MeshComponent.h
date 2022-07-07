#pragma once
#include "Mesh.h"
#include "Renderer.h"
namespace MatCore {
	struct MeshComponent {
	public:
		MeshComponent(Mesh mesh) : VAO(0), VBO(0), EBO(0), mesh(mesh) {}
		~MeshComponent() = default;
		MeshComponent(const MeshComponent& other) = delete;
		MeshComponent(MeshComponent&& other) noexcept {
			VAO = other.VAO;
			VBO = other.VBO;
			EBO = other.EBO;
			mesh = other.mesh;

			other.VAO = 0;
			other.VBO = 0;
			other.EBO = 0;
		}

		MeshComponent& operator=(const MeshComponent& other) = delete;

		MeshComponent& operator=(MeshComponent&& other) noexcept {
			if (this != &other)
			{
				MeshRenderer::DeInit(*this);
				VAO = other.VAO;
				VBO = other.VBO;
				EBO = other.EBO;
				mesh = other.mesh;
				other.VAO = 0;
				other.VBO = 0;
				other.EBO = 0;
			}
			return *this;
		}

		unsigned int VAO, VBO, EBO;
		Mesh mesh;
	};
}