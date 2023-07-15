#pragma once
#include "Resource.h"
#include "OpenGL/MeshBuffer.h"
#include "Factory.h"
#include "Mesh.h"

namespace MatCore
{
	struct MeshComponent
	{
		MeshComponent(Resource<MeshBuffer> meshAsset, const Mesh& mesh)
			: meshAsset(meshAsset), mesh(mesh)
		{}
		explicit MeshComponent(Mesh& mesh)
			: meshAsset(Factory::Get().CreateMeshBufferAssetFromMesh(mesh)),
			mesh(mesh)
		{}
		Resource<MeshBuffer> meshAsset;
		Mesh mesh;
	};
}
