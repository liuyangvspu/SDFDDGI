#pragma once
#include <string>
#include "StaticMesh.h"
#include "Model.h"

namespace Loader
{
	/// Make path platform independent.
	std::string PiPath(const std::string& path);
	std::vector<Model> LoadModels(const std::string& path, const std::string& actualFileName, glm::vec3& min, glm::vec3& max);
}