#include "Model.h"
#include "Mesh.h"
#include "Texture.h"
#include "Scene.h"
#include "MeshComponent.h"
#include "Material.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "Log.h"
#include <filesystem>

namespace MatCore {
	void Model::LoadModel(const char* path, Scene* mScene) {
		Assimp::Importer importer;
		const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FindInvalidData 
			| aiProcess_JoinIdenticalVertices | aiProcess_OptimizeMeshes);

		if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
		{
			LOG_CORE_ERROR("Load model: " + std::string(importer.GetErrorString()) + "\n");
			return;
		}
		//œcie¿ka do folderu zawieraj¹cego plik modelu
		modelFileDirectory = std::string(path).substr(0, std::string(path).find_last_of('/'));

		LOG_CORE_TRACE("Scene materials: {0}", scene->mNumMaterials);
		entity = ProcessNode(scene->mRootNode, scene, mScene, Entity::Null());
	}

	Entity Model::ProcessNode(aiNode* node, const aiScene* scene, Scene* mScene, Entity parentEntity)
	{
		// przetwórz wszystkie wêz³y siatki (jeœli istniej¹)
		LOG_CORE_TRACE("node meshes: {0}", node->mNumMeshes);
		LOG_CORE_TRACE("node chlidrens: {0}", node->mNumChildren);

		Entity nodeEntity = mScene->CreateEntity(node->mName.C_Str(), parentEntity);

		for (uint32_t i = 0; i < node->mNumMeshes; i++)
		{
			Entity meshEntity = mScene->CreateEntity(node->mName.C_Str(), nodeEntity);
			aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];

			meshEntity.AddComponent<MeshComponent>(ProcessMesh(mesh, scene));
			meshEntity.AddComponent<Material>(std::move(ProcessMaterial(mesh, scene)));
		}
		// nastêpnie wykonaj to samo dla ka¿dego z jego dzieci
		for (uint32_t i = 0; i < node->mNumChildren; i++)
		{
			ProcessNode(node->mChildren[i], scene, mScene, nodeEntity);
		}
		return nodeEntity;
	}

	Mesh Model::ProcessMesh(aiMesh* mesh, const aiScene* scene)
	{
		std::vector<Mesh::Vertex> vertices;
		std::vector<unsigned int> indices;
		LOG_CORE_TRACE("Mesh");
		LOG_CORE_TRACE("Vertices: {0}", mesh->mNumVertices);
		LOG_CORE_TRACE("Faces: {0}", mesh->mNumFaces);

		//wierzcho³ki
		for (uint32_t i = 0; i < mesh->mNumVertices; i++)
		{
			Mesh::Vertex vertex;

			//pozycja
			glm::vec3 vertexPosition;
			glm::vec3 vertexNormal;

			vertexPosition.x = mesh->mVertices[i].x;
			vertexPosition.y = mesh->mVertices[i].y;
			vertexPosition.z = mesh->mVertices[i].z;
			vertex.position = vertexPosition;

			//normalna
			if (mesh->HasNormals()) {
				vertexNormal.x = mesh->mNormals[i].x;
				vertexNormal.y = mesh->mNormals[i].y;
				vertexNormal.z = mesh->mNormals[i].z;
				vertex.normal = vertexNormal;
			}
			
			//UV TODO: u¿ywaæ wszystkich 8 map UV
			if (mesh->HasTextureCoords(0))
			{
				glm::vec2 vertexUV;
				vertexUV.x = mesh->mTextureCoords[0][i].x;
				vertexUV.y = mesh->mTextureCoords[0][i].y;
				vertex.uv = vertexUV;
			}
			else
				vertex.uv = glm::vec2(0.0f, 0.0f);

			//TODO: u¿ywaæ kolorów

			vertices.push_back(vertex);
		}

		//indeksy
		for (uint32_t i = 0; i < mesh->mNumFaces; i++)
		{
			aiFace face = mesh->mFaces[i];
			for (uint32_t j = 0; j < face.mNumIndices; j++)
				indices.push_back(face.mIndices[j]);
		}

		Mesh newMesh = Mesh();
		newMesh.SetVertices(vertices);
		newMesh.SetTriangles(indices);
		return newMesh;
	}

	Material Model::ProcessMaterial(aiMesh* mesh, const aiScene* scene)
	{
		//TODO: u¿ywaæ parametrów materia³ów
		aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];

		std::vector<std::shared_ptr<Texture2D>> diffuseMaps = LoadMaterialTextures(material, aiTextureType_DIFFUSE);
		Material mMaterial;

		if (diffuseMaps.size() > 0)
			mMaterial.albedo = diffuseMaps[0];

		return mMaterial;
	}

	std::vector<std::shared_ptr<Texture2D>> Model::LoadMaterialTextures(aiMaterial* mat, aiTextureType type)
	{
		LOG_CORE_TRACE("Material textures: {0}", mat->GetTextureCount(type));
		std::vector<std::shared_ptr<Texture2D>> filesDirs;
		for (unsigned int i = 0; i < mat->GetTextureCount(type); i++)
		{
			aiString str;
			mat->GetTexture(type, i, &str);

			std::string fileDir = str.C_Str(); //œcie¿ka absolutna
			if (!std::filesystem::exists(fileDir))
			{
				fileDir = std::string(modelFileDirectory.c_str()) + '/' + std::string(str.C_Str()); //œcie¿ka relatywna
				if (!std::filesystem::exists(fileDir)) {
					fileDir = str.C_Str();
					LOG_CORE_ERROR("Failed to load model texture: {0}", fileDir);
				}
			}
			filesDirs.push_back(std::make_shared<Texture2D>(fileDir.c_str()));
		}

		return filesDirs;
	}
}