#pragma once
#include "Resource.h"
#include "MeshBuffer.h"
#include "Shader.h"
#include "ShaderProgram.h"
#include "TextureBuffer.h"

namespace MatCore 
{
	class Factory {
	public:
		static Factory& Get()
		{
			static Factory factory;
			return factory;
		}

		Resource<MeshBuffer> CreateMeshBufferAssetFromMesh(Mesh& mesh) const
		{
			auto asset = Resource<MeshBuffer>{ std::make_shared<MeshBuffer>() };
			asset.GetBuffer()->Update(mesh);
			return asset;
		}

		Resource<Shader> CreateShaderAssetFromFile(const std::string& filePath, Shader::ShaderType type) const
		{
			return Resource<Shader>{std::make_shared<Shader>(filePath, type) };
		}

		Resource<ShaderProgram> CreateShaderProgramAssetFromShaders(Resource<Shader> vertex, Resource<Shader> fragment) const
		{
			return Resource<ShaderProgram>{std::make_shared<ShaderProgram>(vertex, fragment) };
		}

		Resource<Texture2D> CreateTextureAssetFromFile(const std::string& path) const
		{
			return Resource<Texture2D>{std::make_shared<Texture2D>(path) };
		}
	};
}
