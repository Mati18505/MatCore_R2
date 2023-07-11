#pragma once
#include "Bindable.h"
#include "ShaderLoader.h"
#include "Shader.h"
#include "Resource.h"
#include "GPUResource.h"

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

	private:
		uint32_t handle;
	};
}
