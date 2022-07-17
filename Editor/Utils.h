#pragma once

#include "MatCore.h"
#include <optional>

namespace EditorUtils {
	std::optional<Entity> LoadModel(EditorScene* editor, const char* path) {
		Model model(path);
		if (model) {
			Entity modelEntity = editor->CreateEntity("User model");
			for (size_t i = 0; i < model.GetMeshes().size(); i++)
			{
				Entity child = editor->CreateEntity("ModelChild", modelEntity);
				child.AddComponent<MeshComponent>(model.GetMeshes()[i]);
				child.AddComponent<Material>();
				if (!model.GetTextures().empty())
					child.GetComponent<Material>().albedo = model.GetTextures()[i];
			}
			return modelEntity;
		}
		return {};
	}
}