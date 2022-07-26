#include "SceneSerializer.h"
#include "Scene.h"
#include "Log.h"
#include "TagComponent.h"
#include "Transform.h"
#include "MeshComponent.h"
#include "Material.h"
#include "CameraComponent.h"
#include "Entity.h"

#include "yaml-cpp/yaml.h"
#include <iostream>
#include <fstream>
#include <functional>
#include <glm/glm.hpp>

namespace YAML {
	template<>
	struct convert<glm::vec3>
	{
		static Node encode(const glm::vec3& rhs)
		{
			Node node;
			node.push_back(rhs.x);
			node.push_back(rhs.y);
			node.push_back(rhs.z);
			return node;
		}

		static bool decode(const Node& node, glm::vec3& rhs)
		{
			if (!node.IsSequence() || node.size() != 3)
				return false;

			rhs.x = node[0].as<float>();
			rhs.y = node[1].as<float>();
			rhs.z = node[2].as<float>();
			return true;
		}
	};
}

namespace MatCore {
	YAML::Emitter& operator<<(YAML::Emitter& out, const glm::vec3& v) {
		out << YAML::Flow;
		out << YAML::BeginSeq << v.x << v.y << v.z << YAML::EndSeq;
		return out;
	}
	YAML::Emitter& operator<<(YAML::Emitter& out, const glm::vec4& v) {
		out << YAML::Flow;
		out << YAML::BeginSeq << v.x << v.y << v.z << v.w << YAML::EndSeq;
		return out;
	}

	template<typename T>
	static void SerializeComponent(YAML::Emitter& out, Entity entity, const char* componentName, std::function<void(T& component)> elements) {
		if (entity.HasComponent<T>())
		{
			out << YAML::Key << componentName;
			out << YAML::BeginMap;

			elements(entity.GetComponent<T>());

			out << YAML::EndMap;
		}
	}

	template <typename T>
	static void KeyValue(YAML::Emitter& out, const char* key, T value) {
		out << YAML::Key << key << YAML::Value << value;
	}

	//TODO: klasa API dla out? aby nie pisaæ wszêdzie out
	static void SerializeEntity(YAML::Emitter& out, Entity entity) {
		out << YAML::BeginMap;

		KeyValue(out, "ID", 0);
		SerializeComponent<TagComponent>(out, entity, "TagComponent", [&](TagComponent& tag) {
			KeyValue(out, "tag", tag.tag);
		});
		SerializeComponent<Transform>(out, entity, "Transform", [&](Transform& transform) {
			KeyValue(out, "position", transform.position);
			KeyValue(out, "rotation", transform.rotation);
			KeyValue(out, "scale", transform.scale);
		});
		SerializeComponent<CameraComponent>(out, entity, "CameraComponent", [&](CameraComponent& cameraComponent) {
			KeyValue(out, "primary", cameraComponent.primary);
			SceneCamera& camera = cameraComponent.camera;

			out << YAML::Key << "Camera" << YAML::BeginMap;

			KeyValue(out, "Camera type", (int)camera.cameraType);
			KeyValue(out, "fov", camera.fov);
			KeyValue(out, "size2D", camera.size2D);
			KeyValue(out, "near clip", camera.nearClip);
			KeyValue(out, "far clip", camera.farClip);

			out << YAML::EndMap;
		});

		out << YAML::EndMap;
	}
	   
	void SceneSerializer::Serialize(Scene& scene, const char* path) {
		YAML::Emitter out;
		out << YAML::BeginMap;
		KeyValue(out, "Scene", "Untitled");
		KeyValue(out, "Entities", YAML::BeginSeq);

		scene.entitiesRegistry.each([&](auto entityHandler)
		{
			Entity entity(entityHandler, &scene);
			SerializeEntity(out, entity);
		});
		out << YAML::EndSeq;
		out << YAML::EndMap;

		std::ofstream outFile(path);
		outFile << out.c_str();
	}

	bool SceneSerializer::DeSerialize(Scene& scene, const char* path)
	{
		std::ifstream input(path);
		std::stringstream strStream;
		strStream << input.rdbuf();

		YAML::Node data = YAML::Load(strStream.str());
		if (!data["Scene"])
			return false;
		std::string sceneName = data["Scene"].as<std::string>();
		LOG_CORE_INFO("Deserializing scene {0}", sceneName);

		auto entities = data["Entities"];
		if (entities) {
			for (auto entity : entities) {
				uint64_t id = entity["ID"].as<uint64_t>(); //TODO: zamieniæ na uuid

				std::string name;
				auto tagComponent = entity["TagComponent"];
				if (tagComponent)
				{
					name = tagComponent["tag"].as<std::string>();
				}
				LOG_CORE_TRACE("Deserialized entity with name = {0}", name);
				Entity deserializedEntity = scene.CreateEntity(name);

				auto transformComponent = entity["Transform"];
				if (transformComponent)
				{
					auto& tc = deserializedEntity.GetComponent<Transform>();
					tc.position = transformComponent["position"].as<glm::vec3>();
					tc.rotation = transformComponent["rotation"].as<glm::vec3>();
					tc.scale = transformComponent["scale"].as<glm::vec3>();
				}
				
				auto cameraComponentNode = entity["CameraComponent"];
				if (cameraComponentNode)
				{
					auto& cameraComponent = deserializedEntity.AddComponent<CameraComponent>();
					auto& camera = cameraComponent.camera;

					cameraComponent.primary = cameraComponentNode["primary"].as<bool>();

					auto cameraNode = cameraComponentNode["Camera"];

					camera.cameraType = (SceneCamera::CameraType)cameraNode["Camera type"].as<int>();
					camera.fov = cameraNode["fov"].as<float>();
					camera.size2D = cameraNode["size2D"].as<float>();
					camera.nearClip = cameraNode["near clip"].as<float>();
					camera.nearClip = cameraNode["far clip"].as<float>();
				}


			}
		}

		input.close();
	}
}
