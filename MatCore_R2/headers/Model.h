#pragma once
#include <vector>
#include <memory>
#include <iostream>
#include <filesystem>
#include "Entity.h"
#include "OpenGL/Resource.h"
#include "OpenGL/TextureBuffer.h"
#include "OpenGL/ShaderProgram.h"
#include "Scene.h"
#include "ShaderLibrary.h"

struct aiScene;
struct aiNode;
struct aiMesh;
struct aiMaterial;
enum aiTextureType;

namespace MatCore {
	class Mesh;
	class Entity;
	class Material;
	class Model { //TODO: umo¿liwiæ bezpieczne ³adowanie modelu na oddzielnym w¹tku
	public:
		Model(const char* modelFilePath, Scene* scene, const std::string& shaderName)
			: shader(scene->shaderLibrary.Get(shaderName))
		{
			LoadModel(modelFilePath, scene);
		}
		
		Entity GetEntity() const { return entity; }
		operator Entity() const { return entity; }

	private:
		void LoadModel(const char* path, Scene* mcScene);
		Entity ProcessNode(aiNode* node, const aiScene* scene, Scene*mScene, Entity parentEntity);
		Mesh ProcessMesh(aiMesh* mesh, const aiScene* scene);
		Material ProcessMaterial(aiMesh* mesh, const aiScene* scene);
		std::vector<Resource<Texture2D>> LoadMaterialTextures(aiMaterial* mat, aiTextureType type);

		Entity entity;
		std::filesystem::path modelParentPath;
		Resource<ShaderProgram> shader;
	};
}
