#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <memory>
#include "OpenGL/Shader.h"
#include "OpenGL/ShaderProgram.h"
#include "OpenGL/Resource.h"
#include "OpenGL/TextureBuffer.h"
#include "OpenGL/Factory.h"

namespace MatCore {
	struct Material {
	public:
		Material(Resource<Shader>& vs, Resource<Shader>& ps);

		Resource<Texture2D> albedo = Factory::Get().CreateTextureAssetFromFile("Resources/Textures/NoTexture.png");

		/// Ustawia uniformy specyficzne dla entity (np. macierze)
		void SetSelfUniforms();
		/// Ustawia uniformy dla ca³ego materia³u (np. œwiat³a, tekstury)
		void SetUniforms();

		void SetMVPMatrix(glm::mat4 modelMatrix, glm::mat4 VPMatrix);

		Resource<ShaderProgram> shader;
	private:
		glm::mat4 mvpMatrix = glm::mat4(1.f);
	};
}