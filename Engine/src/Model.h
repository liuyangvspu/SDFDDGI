#pragma once
#include "Material.h"
#include "StaticMesh.h"
#include "NonCopyable.h"

class Model
{
public:
    MAKE_NO_COPY(Model)
    MAKE_SIMPLE_MOVE(Model)
    Model(StaticMesh&& mesh,const Material& material);
	const StaticMesh& GetMesh() const;
	const Material& GetMaterial() const;
    void Draw() const;
private:
    StaticMesh mesh;
    Material material;
    void move(Model&& other);
};