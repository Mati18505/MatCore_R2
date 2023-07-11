#pragma once
#include <vector>
#include <memory>
#include <iostream>
#include <filesystem>
#include "Entity.h"
#include "OpenGL/Resource.h"
#include "OpenGL/TextureBuffer.h"

struct aiScene;
struct aiNode;
struct aiMesh;
struct aiMaterial;
enum aiTextureType;

namespace MatCore {
	class Mesh;
	class Scene;
	class Entity;
	class Material;
	class Model { //TODO: umo�liwi� bezpieczne �adowanie modelu na oddzielnym w�tku
	public:
		Model(const char* modelFilePath, Scene* scene)
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
	};
}
