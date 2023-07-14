#pragma once
#include "Bindable.h"
#include "ShaderLoader.h"
#include "Shader.h"
#include "Resource.h"
#include "GPUResource.h"
#include <glm/glm.hpp>

namespace MatCore {
	class ShaderProgram : public Bindable, public GPUResource
	{
	public:
		ShaderProgram(Resource<Shader> vertex, Resource<Shader> fragment) {
			handle = ShaderLoader::CreateShaderProgram(vertex.GetBuffer()->GetHandle(), fragment.GetBuffer()->GetHandle());
		}
		~ShaderProgram() override;
		ShaderProgram(const ShaderProgram&) = delete;
		ShaderProgram& operator= (const ShaderProgram&) = delete;
		ShaderProgram(const ShaderProgram&&) = delete;
		ShaderProgram& operator= (const ShaderProgram&&) = delete;

		void Bind() const override;

		uint32_t GetHandle() const { return handle; }

		void SetUniform(const std::string& name, int value);
		void SetUniform(const std::string& name, float value);
		void SetUniform(const std::string& name, const glm::vec2& value);
		void SetUniform(const std::string& name, const glm::vec3& value);
		void SetUniform(const std::string& name, const glm::vec4& value);
		void SetUniform(const std::string& name, const glm::mat3& value);
		void SetUniform(const std::string& name, const glm::mat4& value);

		int GetUniformLocation(const std::string& name);

	private:
		uint32_t handle;
	};
}
