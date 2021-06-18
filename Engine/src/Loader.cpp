#include "Loader.h"
#include "glm/vec3.hpp"
#include "assimp/Importer.hpp"
#include "assimp/postprocess.h"
#include "assimp/matrix4x4.h"
#include "assimp/mesh.h"
#include "assimp/scene.h"
#include "assimp/camera.h"
#include "assimp/material.h"
#include <stdexcept>
#include "glm/geometric.hpp"
#include "Texture.h"
#include <unordered_map>
#include "Definitions.h"
#include <memory>

namespace
{
	std::unordered_map<std::string, std::shared_ptr<Texture>> uniqueTextureMap;

	unsigned char stdColorData[4] = { 255,255,255,255 };
	unsigned char stdEmissiveColorData[4] = { 0,0,0,255 };
	unsigned char stdNormalData[4] = { 128,128,255,255 };
	unsigned char stdSpecularData[4] = { 255,255,0,255 };


	std::shared_ptr<Texture> stdColor;
	std::shared_ptr<Texture> stdNormal;
	std::shared_ptr<Texture> stdSpecular;
	std::shared_ptr<Texture> stdEmissive;

	std::unordered_map<aiTextureType, std::shared_ptr<Texture>> stdTexMap;


	void createVertices(std::vector<Vertex>& p_vertices, aiMesh* p_assMesh, const aiMatrix4x4& trans)
	{
		for (u32 i = 0; i < p_assMesh->mNumVertices; i++)
		{
			Vertex v;

			aiVector3D assPos = trans * p_assMesh->mVertices[i];

			if (!p_assMesh->HasTextureCoords(0)) throw std::runtime_error("ERROR OCCURED: Imported mesh " + std::string(p_assMesh->mName.C_Str()) + " has no texture coordinates");

			glm::vec3 pos{ assPos.x, assPos.y, assPos.z };
			v.Position = pos;

			auto normalMatrix = trans;
			normalMatrix.Inverse();
			normalMatrix.Transpose();

			aiVector3D assNormal = normalMatrix * p_assMesh->mNormals[i];
			aiVector3D assTangent = trans * p_assMesh->mTangents[i];
			aiVector3D assBitangent = trans * p_assMesh->mBitangents[i];
			glm::vec3 normal{ assNormal.x, assNormal.y, assNormal.z };
			glm::vec3 tangent{ assTangent.x, assTangent.y, assTangent.z };
			glm::vec3 bitangent{ assBitangent.x,assBitangent.y,assBitangent.z };


			v.Normal = glm::normalize(normal);
			v.Tangent = glm::normalize(tangent);
			v.Bitangent = glm::normalize(bitangent);

			auto assUV = p_assMesh->mTextureCoords[0][i];
			glm::vec2 uvMap{ assUV.x,1 - assUV.y };
			v.Coord = uvMap;

			p_vertices.push_back(v);
		}
	}
	void createIndices(std::vector<u32>& p_indices, aiMesh* p_assMesh)
	{
		for (u32 i = 0; i < p_assMesh->mNumFaces; i++)
		{
			aiFace& face = p_assMesh->mFaces[i];

			for (u32 j = 0; j < face.mNumIndices; j++)
			{
				p_indices.push_back(face.mIndices[j]);
			}
		}
	}


	const aiScene* loadScene(const char* p_filename, Assimp::Importer& p_importer, u32 p_steps = aiProcess_Triangulate)
	{
		p_importer.SetExtraVerbose(true);
		const aiScene* scene = p_importer.ReadFile(p_filename, p_steps);
		if (!scene) throw std::runtime_error("Couldn't load or read file: " + std::string(p_importer.GetErrorString()));
		if (!scene->HasMeshes()) throw std::runtime_error("Specified file contains no meshes.");
		return scene;


	}

	void getMinMax(const std::vector<Vertex>& vertices, glm::vec3& min, glm::vec3& max)
	{
		for (const Vertex& v : vertices)
		{
			if (v.Position.x > max.x) max.x = v.Position.x;
			if (v.Position.x < min.x) min.x = v.Position.x;
			if (v.Position.y > max.y) max.y = v.Position.y;
			if (v.Position.y < min.y) min.y = v.Position.y;
			if (v.Position.z > max.z) max.z = v.Position.z;
			if (v.Position.z < min.z) min.z = v.Position.z;
		}
	}


	std::shared_ptr<Texture> loadTex(aiMaterial* assMat, aiTextureType type, const std::string& texturePath)
	{
		aiString path;
		if (assMat->GetTextureCount(type) == 0) return stdTexMap[type];
		if (AI_SUCCESS == assMat->GetTexture(type, 0, &path))
		{
			std::string p = texturePath + path.C_Str();
			auto it = uniqueTextureMap.find(p);
			if (it != uniqueTextureMap.end()) return it->second;
			else
			{
				auto tex = std::make_shared<Texture>(Texture::LoadTexture(p));
				uniqueTextureMap[p] = tex;
				return tex;
			}
		}
		return nullptr;
	}

	void createMaterial(aiMaterial* assMat, Material& mat, const std::string& texturePath)
	{
		auto sTexDiffuse = loadTex(assMat, aiTextureType_DIFFUSE, texturePath);
		auto sTexSpecular = loadTex(assMat, aiTextureType_UNKNOWN, texturePath);
		auto sTexEmissive = loadTex(assMat, aiTextureType_EMISSIVE, texturePath);
		auto sTexNormal = loadTex(assMat, aiTextureType_NORMALS, texturePath);


		mat = Material(std::move(sTexDiffuse), std::move(sTexSpecular), std::move(sTexEmissive), std::move(sTexNormal));
	}

	void preTransformNode(aiNode& node, const aiScene& scene, glm::vec3& min, glm::vec3& max, std::vector<Model>& models, const std::string& texturePath)
	{
		for (u32 i = 0; i < node.mNumChildren; i++)
		{
			aiNode& child = *node.mChildren[i];
			child.mTransformation = node.mTransformation * child.mTransformation;
			preTransformNode(child, scene, min, max, models, texturePath);
			for (u32 j = 0; j < child.mNumMeshes; j++)
			{
				std::vector<Vertex> vertices;
				std::vector<u32> indices;
				auto* mesh = scene.mMeshes[child.mMeshes[j]];
				createVertices(vertices, mesh, child.mTransformation);
				getMinMax(vertices, min, max);
				createIndices(indices, mesh);
				Material mat;
				createMaterial(scene.mMaterials[mesh->mMaterialIndex], mat, texturePath);
				std::string name = mesh->mName.C_Str();
				StaticMesh smesh(vertices, indices, name);
				models.push_back(Model(std::move(smesh), mat));
			}
		}
	}

	void initStdTextures()
	{
		stdColor = std::make_shared<Texture>(1, 1, GL_RGBA8, GL_RGBA, GL_UNSIGNED_BYTE, stdColorData);
		stdEmissive = std::make_shared<Texture>(1, 1, GL_RGBA8, GL_RGBA, GL_UNSIGNED_BYTE, stdEmissiveColorData);
		stdNormal = std::make_shared<Texture>(1, 1, GL_RGBA8, GL_RGBA, GL_UNSIGNED_BYTE, stdNormalData);
		stdSpecular = std::make_shared<Texture>(1, 1, GL_RGBA8, GL_RGBA, GL_UNSIGNED_BYTE, stdSpecularData);
		stdTexMap = { {aiTextureType_DIFFUSE, stdColor}, { aiTextureType_NORMALS, stdNormal }, { aiTextureType_EMISSIVE, stdEmissive }, { aiTextureType_UNKNOWN,stdSpecular } };
	}

};


std::vector<Model> Loader::LoadModels(const std::string& path, const std::string& actualFileName, glm::vec3& min, glm::vec3& max)
{

	initStdTextures();
	Assimp::Importer importer;
	std::string filename = path + actualFileName;
	const aiScene* scene = loadScene(filename.c_str(), importer, aiProcessPreset_TargetRealtime_MaxQuality);
	std::vector<Model> out;
	max.x = std::numeric_limits<float>::min(), max.y = std::numeric_limits<float>::min(), max.z = std::numeric_limits<float>::min(),
		min.x = std::numeric_limits<float>::max(), min.y = std::numeric_limits<float>::max(), min.z = std::numeric_limits<float>::max();
	preTransformNode(*scene->mRootNode,*scene,min,max,out,path);

	return out;
}


std::string Loader::PiPath(const std::string& path)
{
	return path; // For now just return it.
}
