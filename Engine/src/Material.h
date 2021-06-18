#pragma once
#include "glad/glad.h"
#include <string>
#include <memory>



// TODO: Make sure that if shader is destroy, all corresponding instances are also destroyed / marked invalid.

class Texture;

class Material
{
public:
	Material() = default;
	Material(std::shared_ptr<Texture>&& diffuseTex, std::shared_ptr<Texture>&& specularTex,
		std::shared_ptr<Texture>&& emissiveTex, std::shared_ptr<Texture>&& normalTex)
		: diffuse(std::move(diffuseTex)), specular(std::move(specularTex)), normal(std::move(normalTex)), emissive(std::move(emissiveTex))
	{}

	const std::shared_ptr<Texture>& GetTextureDiffuse() const { return diffuse; }
	const std::shared_ptr<Texture>& GetTextureSpecular() const { return specular; }
	const std::shared_ptr<Texture>& GetTextureNormal() const { return normal; }
	const std::shared_ptr<Texture>& GetTextureEmissive() const { return emissive; }

private:
    std::shared_ptr<Texture> diffuse;
	std::shared_ptr<Texture> specular;
	std::shared_ptr<Texture> normal;
	std::shared_ptr<Texture> emissive;
};
