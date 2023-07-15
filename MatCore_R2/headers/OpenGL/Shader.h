#pragma once
#include <string>
#include "ShaderLoader.h"
#include "GPUResource.h"

namespace MatCore {
	class Shader : public GPUResource {
	public:
		using ShaderType = ShaderLoader::ShaderType;

		Shader(const std::string& filePath, ShaderType type)
			: GPUResource()
		{
			std::string shaderCode = ShaderLoader::LoadFileToShaderCode(filePath);
			shader = ShaderLoader::CompileShader(shaderCode, type);
		}

		~Shader() override;

		uint32_t GetHandle() const { return shader; }
	private:
		uint32_t shader;
	};
}
