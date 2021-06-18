#include "Model.h"
#include <utility>

Model::Model(StaticMesh&& mesh_, const Material& mat)
:mesh(std::move(mesh_)), material(mat)
{
    
}

const StaticMesh& Model::GetMesh() const
{
	return mesh;
}

const Material& Model::GetMaterial() const
{
	return material;
}

void Model::Draw() const
{
    mesh.Draw();
}

void Model::move(Model&& other)
{
    mesh = std::move(other.mesh);
    material = std::move(other.material);
}