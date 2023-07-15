#pragma once
#include "Bindable.h"
#include "GPUResource.h"

namespace MatCore {
	struct BufferLayout;
	class MeshBuffer : public Bindable, public GPUResource {
	public:
		MeshBuffer();
		~MeshBuffer() override;

		void Bind() const override;
		
		template <typename TVertex, typename TIndex>
		void UpdateT(const std::vector<TVertex>& vertices, const std::vector<TIndex>& indices)
		{
			Update(vertices.size() * sizeof(TVertex), vertices.data(), indices.size() * sizeof(TIndex), indices.data());
		}

		void Update(size_t verticesByteSize, const void* verticesData, size_t indicesByteSize, const void* indicesData);
		void SetVertices(size_t verticesByteSize, const void* verticesData);
		void SetIndices(size_t indicesByteSize, const void* indicesData);

		void SetLayout(BufferLayout layout);
	private:
		unsigned int VAO, VBO, EBO;
		bool layoutSet = false;
	};

	struct BufferLayoutElement
	{
		enum class Type {
			Float,
			Unsigned_int
		};
		Type type;
		uint32_t count;
		uint32_t size;
		bool normalized;
	};

	struct BufferLayout
	{
		using Type = BufferLayoutElement::Type;

		void Push(Type type, uint32_t count, bool normalized = false);
		const std::vector<BufferLayoutElement>& GetElements() const;

		typedef unsigned int GLenum;
		GLenum GetGLType(Type type) const;
		uint32_t GetStride() { return stride; }
	private:
		std::vector<BufferLayoutElement> elements;
		uint32_t GetSizeOfType(Type type) const;
		uint32_t stride = 0;
	};
}