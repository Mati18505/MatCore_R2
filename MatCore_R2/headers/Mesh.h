#pragma once
#include <iostream>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Mesh {
public:
	struct Vertex {
		glm::vec3 position;
		glm::vec2 uv;
		glm::vec3 color;
		glm::vec3 normal;

		Vertex()
		{
			this->position = glm::vec3(0.f, 0.f, 0.f);
			this->uv = glm::vec2(0.f, 0.f);
			this->color = glm::vec3(0, 0, 0);
			this->normal = glm::vec3(0, 1, 0);
		}

		Vertex(glm::vec3 position, glm::vec2 uv)
		{
			this->position = position;
			this->uv = uv;
			this->color = glm::vec3(0, 0, 0);
			this->normal = glm::vec3(0, 1, 0);
		}
	};
private:
	std::vector<Vertex> vertices;
	std::vector<unsigned int> triangles;

	std::vector<glm::vec3> coliderAABB;
	bool iscoliderAABBEditingNow = false;

	void CreateAABB() {
		while (iscoliderAABBEditingNow)
			continue;
		iscoliderAABBEditingNow = true;

		glm::vec3 minVertex = glm::vec3(FLT_MAX, FLT_MAX, FLT_MAX);
		glm::vec3 maxVertex = glm::vec3(-FLT_MAX, -FLT_MAX, -FLT_MAX);

		for (unsigned int i = 0; i < vertices.size(); i++)
		{
			//Get the smallest vertex 
			if (vertices[i].position.x < minVertex.x)
				minVertex.x = vertices[i].position.x;
			if (vertices[i].position.y < minVertex.y)
				minVertex.y = vertices[i].position.y;
			if (vertices[i].position.z < minVertex.z)
				minVertex.z = vertices[i].position.z;

			//Get the largest vertex
			if (vertices[i].position.x > maxVertex.x)
				maxVertex.x = vertices[i].position.x;
			if (vertices[i].position.y > maxVertex.y)
				maxVertex.y = vertices[i].position.y;
			if (vertices[i].position.z > maxVertex.z)
				maxVertex.z = vertices[i].position.z;
		}

		coliderAABB.clear();
		// Our AABB [0] is the min vertex and [1] is the max
		//minVertex = glm::vec3(10, 10, 10);
		//maxVertex = glm::vec3(10, 10, 10);
		coliderAABB.push_back(minVertex);
		coliderAABB.push_back(maxVertex);
		iscoliderAABBEditingNow = false;
	}

	bool isVerticesChanged;
	bool isTrianglesChanged;
public:
	Mesh() {
		isVerticesChanged = false;
		isTrianglesChanged = false;
		coliderAABB = std::vector<glm::vec3>();
		coliderAABB.push_back(glm::vec3(0, 0, 0));
		coliderAABB.push_back(glm::vec3(0, 0, 0));
	}
	Mesh(const Mesh& meshCopy)
	{
		this->triangles = meshCopy.triangles;
		this->vertices = meshCopy.vertices;
		isVerticesChanged = meshCopy.isVerticesChanged;
		isTrianglesChanged = meshCopy.isTrianglesChanged;
		coliderAABB = meshCopy.coliderAABB;
	}

	void SetVertices(Vertex* verticesArray, unsigned int arrayLenght) {
		vertices = std::vector<Vertex>(verticesArray, verticesArray + arrayLenght);
		CreateAABB();
		isVerticesChanged = true;
	}
	void SetVertices(std::vector<Vertex> verticesArray) {
		vertices = verticesArray;
		CreateAABB();
		isVerticesChanged = true;
	}

	void SetTriangles(unsigned int* trianglesArray, unsigned int arrayLenght) {
		triangles = std::vector<unsigned int>(trianglesArray, trianglesArray + arrayLenght);
		CreateAABB();
		isTrianglesChanged = true;
	}
	void SetTriangles(const unsigned int* trianglesArray, unsigned int arrayLenght) {
		triangles = std::vector<unsigned int>(trianglesArray, trianglesArray + arrayLenght);
		CreateAABB();
		isTrianglesChanged = true;
	}
	void SetTriangles(std::vector<unsigned int> trianglesArray) {
		triangles = std::vector<unsigned int>(trianglesArray);
		CreateAABB();
		isTrianglesChanged = true;
	}

	std::vector<Vertex>* GetVertices() {
		return &vertices;
	}
	std::vector<unsigned int>* GetTriangles() {
		return &triangles;
	}
	std::vector<glm::vec3> GetAABBCollider() {
		//CreateAABB();
		while (iscoliderAABBEditingNow)
			continue;
		return coliderAABB;
	}

	void CombineMeshes(Mesh* meshes, unsigned int arrayLenght, bool isDeleteReapetedVertices = false) {
		unsigned int thisVerticesSize = vertices.size();

		//Obliczanie wielkoœci tablicy newVertices
		unsigned int newVerticesArrayLenght = thisVerticesSize;
		for (int i = 0; i < arrayLenght; i++)
		{
			newVerticesArrayLenght += meshes[i].vertices.size();
		}

		//Tworzenie tablicy newVertices i wpisywanie do niej wartoœci z tablic vertices meshy
		Vertex* newVertices = new Vertex[newVerticesArrayLenght];

		for (int i = 0; i < thisVerticesSize; i++)
		{
			newVertices[i] = vertices[i];
		}

		for (int index = thisVerticesSize, i = 0; i < arrayLenght; i++)
		{
			for (int j = 0; j < meshes[i].vertices.size(); j++)
			{
				newVertices[index + j] = meshes[i].vertices[j];
			}
			index += meshes[i].vertices.size();
		}


		//Obliczanie nowych wartoœci triangles meshy
		for (int index = thisVerticesSize, i = 0; i < arrayLenght; i++)
		{
			for (int j = 0; j < meshes[i].triangles.size(); j++)
			{
				meshes[i].triangles[j] += index;
			}
			index += meshes[i].vertices.size();
		}

		//Obliczanie wielkoœci tablicy newTriangles
		unsigned int newTrianglesArrayLenght = triangles.size();
		for (int i = 0; i < arrayLenght; i++)
		{
			newTrianglesArrayLenght += meshes[i].triangles.size();
		}

		//Tworzenie tablicy newTriangles i wpisywanie do niej wartoœci z tablic triangles meshy
		unsigned int* newTriangles = new unsigned int[newTrianglesArrayLenght];

		for (int i = 0; i < triangles.size(); i++)
		{
			newTriangles[i] = triangles[i];
		}

		for (int index = triangles.size(), i = 0; i < arrayLenght; i++)
		{
			for (int j = 0; j < meshes[i].triangles.size(); j++)
			{
				newTriangles[index + j] = meshes[i].triangles[j];
			}
			index += meshes[i].triangles.size();
		}

		


		//Zmienianie wartoœci tablic vertices i triangles tego mesha na wartoœci tablic newVertices i newTriangles 
		SetVertices(newVertices, newVerticesArrayLenght);
		SetTriangles(newTriangles, newTrianglesArrayLenght);

		CreateAABB();
		isVerticesChanged = true;
		isTrianglesChanged = true;
		delete[] newVertices;
		delete[] newTriangles;
	}

	/// <summary>
	/// Generuje sto¿ek z podanymi parametrami
	/// </summary>
	/// <param name="vertices">iloœæ wierzcho³ków w okrêgu</param>
	/// <param name="circleRadius">szerokoœæ okrêgu</param>
	/// <param name="depth">odleg³oœæ pomiêdzy górnym wierzcho³kiem, a okrêgiem</param>
	/// <returns></returns>
	static Mesh Cone(unsigned int vertices, float circleRadius, float depth) {
		glm::vec3 origin = glm::vec3(0, 0, 0);
		glm::vec3 coneHead = glm::vec3(0, 0, depth);

		const float angleIncrease = 360.f / vertices;
		float angle = 0.f;

		const int cVC = vertices + 1 + 1;//circleOrigin, coneHead
		const int cIC = vertices * 3 * 2;
		Mesh::Vertex* circlev = new Mesh::Vertex[cVC];
		unsigned int* circlei = new unsigned int[cIC];

		circlev[0].position = origin;
		circlev[1].position = coneHead;

		int vertexIndex = 2;
		int triangleIndex = 0;
		for (int i = 0; i < vertices; i++)
		{
			//get vector from angle
			float angleRad = angle * (M_PI / 180.f);
			glm::vec3 angleVector = glm::vec3(std::cos(angleRad), std::sin(angleRad), 0.f);

			circlev[vertexIndex].position = origin + angleVector * circleRadius;

			if (i > 0) {///
				circlei[triangleIndex + 0] = 0;
				circlei[triangleIndex + 1] = vertexIndex - 1;
				circlei[triangleIndex + 2] = vertexIndex;

				triangleIndex += 3;

				circlei[triangleIndex + 0] = 1;
				circlei[triangleIndex + 1] = vertexIndex;
				circlei[triangleIndex + 2] = vertexIndex - 1;

				triangleIndex += 3;
			}
			vertexIndex++;

			angle -= angleIncrease;
		}
		circlei[triangleIndex + 0] = 0;
		circlei[triangleIndex + 1] = vertexIndex - 1;
		circlei[triangleIndex + 2] = 2;

		triangleIndex += 3;

		circlei[triangleIndex + 0] = 1;
		circlei[triangleIndex + 1] = 2;
		circlei[triangleIndex + 2] = vertexIndex - 1;

		Mesh circle = Mesh();
		circle.SetVertices(circlev, cVC);
		circle.SetTriangles(circlei, cIC);
		return circle;
	}

	static Mesh Circle(unsigned int vertices, float radius, glm::vec3 origin = glm::vec3(0, 0, 0)) {
		const float angleIncrease = 360.f / vertices;
		float angle = 0.f;

		const int cVC = vertices + 1;
		const int cIC = vertices * 3;
		Mesh::Vertex* circlev = new Mesh::Vertex[cVC];
		unsigned int* circlei = new unsigned int[cIC];

		circlev[0].position = origin;

		int vertexIndex = 1;
		int triangleIndex = 0;
		for (int i = 0; i < vertices; i++)
		{
			//get vector from angle
			float angleRad = angle * (M_PI / 180.f);
			glm::vec3 angleVector = glm::vec3(std::cos(angleRad), std::sin(angleRad), 0.f);

			circlev[vertexIndex].position = origin + angleVector * radius;

			if (i > 0) {
				circlei[triangleIndex + 0] = 0;
				circlei[triangleIndex + 1] = vertexIndex - 1;
				circlei[triangleIndex + 2] = vertexIndex;

				triangleIndex += 3;
			}
			vertexIndex++;

			angle -= angleIncrease;
		}
		circlei[triangleIndex + 0] = 0;
		circlei[triangleIndex + 1] = vertexIndex - 1;
		circlei[triangleIndex + 2] = 1;

		Mesh circle = Mesh();
		circle.SetVertices(circlev, cVC);
		circle.SetTriangles(circlei, cIC);
		return circle;
	}
};