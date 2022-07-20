#pragma once

#include "MatCore.h"

namespace EditorUtils {
	Entity LoadModel(EditorScene* editor, const char* path) {
		return Model(path, editor);
	}
}