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
		Material(Resource<Shader>& vs, Resource<Shader>& ps)
			: shader(Factory::Get().CreateShaderProgramAssetFromShaders(vs, ps))
		{}
		
		Resource<ShaderProgram> shader;
		Resource<Texture2D> albedo = Factory::Get().CreateTextureAssetFromFile("Resources/Textures/NoTexture.png");
		glm::mat4 mvpMatrix = glm::mat4(1.f);
	};
}