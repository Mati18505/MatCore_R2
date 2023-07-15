#pragma once
#include "OpenGL/ShaderProgram.h"
#include "Resource.h"

namespace MatCore
{
	class ShaderLibrary {
	public:
		void Add(const std::string& name, Resource<ShaderProgram> shader);
		Resource<ShaderProgram> Get(const std::string& name);
		bool Exist(const std::string& name);
	private:
		std::unordered_map<std::string, Resource<ShaderProgram>> shaders;
	};
}
