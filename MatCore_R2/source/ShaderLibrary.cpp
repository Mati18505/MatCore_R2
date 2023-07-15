#include "pch.h"

#include "ShaderLibrary.h"
#include "Log.h"
#include "Factory.h"

namespace MatCore
{
	void ShaderLibrary::Add(const std::string& name, Resource<ShaderProgram> shader)
	{
		assert(!Exist(name) && "Shader was already in the libary!");
		shaders.try_emplace(name, shader);
	}

	Resource<ShaderProgram> ShaderLibrary::Get(const std::string& name)
	{
		assert(Exist(name) && "Shader not found in the library!");
		return shaders.at(name);
	}
	bool ShaderLibrary::Exist(const std::string& name)
	{
		return shaders.find(name) != shaders.end();
	}
}
