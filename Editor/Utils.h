#pragma once

#include "MatCore.h"

namespace EditorUtils {
	Entity LoadModel(EditorScene* editor) {
		std::string path = FileDialog::OpenFile("Model Files (*.obj, *.fbx, *.gltf, *.glb, *.dae, *.blend)\0*.obj;*.fbx;*.gltf;*.glb;*.dae;*.blend\0");
		if (path.empty())
			return Entity::Null();
		return Model(path.c_str(), editor, "default");
	}
}