#pragma once
#include "Mesh.h"
#include "Bindable.h"
#include "GPUResource.h"

namespace MatCore {
	struct MeshBuffer : public Bindable, public GPUResource {
	public:
		MeshBuffer();
		~MeshBuffer() override;
		MeshBuffer(const MeshBuffer& other) = delete;
		MeshBuffer(MeshBuffer&& other) noexcept = delete;
		/* {
			VAO = other.VAO;
			VBO = other.VBO;
			EBO = other.EBO;

			other.VAO = 0;
			other.VBO = 0;
			other.EBO = 0;
		}*/

		MeshBuffer& operator=(const MeshBuffer& other) = delete;

		MeshBuffer& operator=(MeshBuffer&& other) noexcept = delete;
		/* {
			if (this != &other)
			{
				MeshRenderer::DeInit(*this);
				VAO = other.VAO;
				VBO = other.VBO;
				EBO = other.EBO;
				other.VAO = 0;
				other.VBO = 0;
				other.EBO = 0;
			}
			return *this;
		}
		*/
		void Bind() const override;
		void Update(Mesh& mesh);

	private:
		unsigned int VAO, VBO, EBO;
	};
}