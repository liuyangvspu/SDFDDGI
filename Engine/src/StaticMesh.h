#pragma once

#include "glad/glad.h"
#include "glm/vec3.hpp"
#include "glm/vec2.hpp"
#include <vector>
#include "Definitions.h"
#include <string>

struct Vertex
{
	glm::vec3 Position;
	glm::vec3 Normal;
	glm::vec3 Tangent;
	glm::vec3 Bitangent;
	glm::vec2 Coord;
	
};

/*
 * This class represents basic non animated geometry.
 */
class StaticMesh
{
public:
	StaticMesh(const std::vector<Vertex>& verts, const std::vector<u32>& indices, const std::string& name ="");
	std::string GetName() const;
	// Constructors & Copy + Move Ops.
	StaticMesh() = default;
	StaticMesh& operator=(const StaticMesh& other) = delete;
	StaticMesh(const StaticMesh& other) = delete;
	StaticMesh(StaticMesh&& other) noexcept;
	StaticMesh& operator=(StaticMesh&& other) noexcept;
	void Draw() const;
    ~StaticMesh();
private:
	GLuint vbo = 0,ebo = 0, vao=0;
    std::string name;
	u64 sizeBytesIndex = 0, sizeBytesVertex=0;
	void move(StaticMesh&& other);
};