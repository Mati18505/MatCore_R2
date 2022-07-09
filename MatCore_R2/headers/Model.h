#pragma once
#include <vector>
#include <memory>
#include <iostream>

struct aiScene;
struct aiNode;
struct aiMesh;
struct aiMaterial;
enum aiTextureType;

namespace MatCore {
	class Mesh;
	class Texture2D;
	class Model {
	public:
		Model(const char* modelFilePath)
		{
			LoadModel(modelFilePath);
		}
		const std::vector<Mesh>& GetMeshes();
		const std::vector<std::shared_ptr<Texture2D>>& GetTextures();

	private:
		std::vector<Mesh> meshes;
		std::vector<std::shared_ptr<Texture2D>> diffuseTextures;

		void LoadModel(const char* path);
		void ProcessNode(aiNode* node, const aiScene* scene);
		Mesh ProcessMesh(aiMesh* mesh, const aiScene* scene);
		std::vector<std::shared_ptr<Texture2D>> LoadMaterialTextures(aiMaterial* mat, aiTextureType type);

		std::string modelFileDirectory;
	};
}
