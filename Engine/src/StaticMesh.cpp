#include "StaticMesh.h"

StaticMesh::StaticMesh(const std::vector<Vertex>& verts, const std::vector<u32>& indices, const std::string& name_) : name(name_)
{
	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);
	glGenBuffers(1, &ebo);

	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, verts.size() * sizeof(Vertex), verts.data(), GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(u32), indices.data(), GL_STATIC_DRAW);
	glEnableVertexAttribArray(0); //On layout = 0
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, Normal));

	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, Tangent));

	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, Bitangent));
	
	glEnableVertexAttribArray(4);
	glVertexAttribPointer(4, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, Coord));

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	sizeBytesVertex = verts.size() * sizeof(Vertex);
	sizeBytesIndex = indices.size() * sizeof(u32);
}

std::string StaticMesh::GetName() const 
{
    return name;
}


StaticMesh::StaticMesh(StaticMesh&& other) noexcept
{
    this->move(std::move(other));
}

void StaticMesh::move(StaticMesh&& other)
{
    vao = other.vao;
    vbo = other.vbo;
    ebo = other.ebo;
    sizeBytesIndex = other.sizeBytesIndex;
    sizeBytesVertex = other.sizeBytesVertex;
    other.vao = 0;
    other.vbo = 0;
    other.ebo = 0;
	this->name = std::move(other.name);
}

StaticMesh& StaticMesh::operator=(StaticMesh&& other) noexcept
{
    if (this != &other)
    {
        this->move(std::move(other));
    }
    return *this;
}

void StaticMesh::Draw() const
{
	glBindVertexArray(vao);
	glDrawElements(GL_TRIANGLES, sizeBytesIndex / sizeof(u32), GL_UNSIGNED_INT, 0);
}


StaticMesh::~StaticMesh()
{
    glDeleteBuffers(1,&vbo);
    glDeleteBuffers(1,&ebo);
    glDeleteVertexArrays(1,&vao);
}
