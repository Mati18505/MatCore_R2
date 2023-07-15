#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <memory>
#include "OpenGL/Shader.h"
#include "OpenGL/ShaderProgram.h"
#include "Resource.h"
#include "OpenGL/TextureBuffer.h"
#include "Factory.h"

namespace MatCore {
	struct Material {
	public:
		Material(Resource<ShaderProgram>& shader)
			: shader(shader)
		{}
		
		Resource<ShaderProgram> shader;
		Resource<Texture2D> albedo = Factory::Get().CreateTextureAssetFromFile("Resources/Textures/NoTexture.png");
		glm::mat4 mvpMatrix = glm::mat4(1.f);
	};
}