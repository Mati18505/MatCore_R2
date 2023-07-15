#pragma once
#include "Resource.h"
#include "OpenGL/MeshBuffer.h"
#include "Mesh.h"
#include "OpenGL/Shader.h"
#include "OpenGL/ShaderProgram.h"
#include "OpenGL/TextureBuffer.h"

namespace MatCore 
{
	class Factory {
	public:
		static Factory& Get()
		{
			static Factory factory;
			return factory;
		}

		Factory(const Factory&) = delete;
		Factory& operator=(const Factory& other) = delete;

		Resource<MeshBuffer> CreateMeshBufferAssetFromMesh(Mesh& mesh) const
		{
			auto asset = Resource<MeshBuffer>{ std::make_shared<MeshBuffer>() };
			
			BufferLayout layout;
			layout.Push(BufferLayout::Type::Float, 3); //pos
			layout.Push(BufferLayout::Type::Float, 2); //uv
			layout.Push(BufferLayout::Type::Float, 3); //col
			layout.Push(BufferLayout::Type::Float, 3); //normal
			asset.GetBuffer()->SetLayout(layout);

			asset.GetBuffer()->UpdateT(*mesh.GetVertices(), *mesh.GetTriangles());
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

		Resource<Texture2D> CreateTextureAssetFromFile(const std::string& path) const;
	private:
		Factory() = default;
	};
}
