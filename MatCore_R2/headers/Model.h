#pragma once
#include <filesystem>
#include "Entity.h"

struct aiScene;
struct aiNode;
struct aiMesh;
struct aiMaterial;
enum aiTextureType;

namespace MatCore {
	class Mesh;
	class Texture2D;
	class Scene;
	class Entity;
	class Material;
	class Model { //TODO: umo¿liwiæ bezpieczne ³adowanie modelu na oddzielnym w¹tku
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
		std::vector<std::shared_ptr<Texture2D>> LoadMaterialTextures(aiMaterial* mat, aiTextureType type);

		Entity entity;
		std::filesystem::path modelParentPath;
	};
}
