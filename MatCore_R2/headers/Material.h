#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <memory>
namespace MatCore {
	class Texture2D;
	struct Material {
	public:
		Material(const char* vertexShaderPath, const char* fragmentShaderPath);
		Material(const Material& materialCopy);
		~Material();

		unsigned int shaderID;

		std::shared_ptr<Texture2D> albedo;

		/// Ustawia uniformy specyficzne dla entity (np. macierze)
		void SetSelfUniforms();
		/// Ustawia uniformy dla ca�ego materia�u (np. �wiat�a, tekstury)
		void SetUniforms();

		void SetMVPMatrix(glm::mat4 modelMatrix, glm::mat4 VPMatrix);
	private:
		glm::mat4 mvpMatrix;
	};
}