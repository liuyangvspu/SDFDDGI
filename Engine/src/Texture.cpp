#include "Texture.h"
#include <algorithm>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"


Texture::Texture(GLuint width, GLuint height, GLenum internalFormat, GLenum format, GLenum type, const void* data,
	GLenum minFilter, GLenum magFilter, GLenum wrapS, GLenum wrapT) : Texture(width,height,internalFormat,format,type,data)
{
	SetTexParameter(minFilter, magFilter, wrapS, wrapT);
}

Texture::Texture(GLuint width, GLuint height, GLuint depth, GLenum internalFormat, GLenum format, GLenum type,
	const void* data, GLenum minFilter, GLenum magFilter, GLenum wrapS, GLenum wrapT) : Texture(width, height, width, internalFormat, format, type, data)
{
	SetTexParameter(minFilter, magFilter, wrapS, wrapT);
}

Texture::Texture(GLuint width, GLuint height, GLenum internalFormat, GLuint amountLevels)
{
	glGenTextures(1, &id);
	glBindTexture(GL_TEXTURE_2D, id);
	glTexStorage2D(GL_TEXTURE_2D, amountLevels, internalFormat, width, height);
	textureType = GL_TEXTURE_2D;
	this->internalFormat = internalFormat;
}

Texture::Texture(GLuint width, GLuint height, GLuint depth, GLenum internalFormat, GLuint amountLevels)
{
	glGenTextures(1, &id);
	glBindTexture(GL_TEXTURE_3D, id);
	glTexStorage3D(GL_TEXTURE_3D, amountLevels, internalFormat, width, height,depth);
	textureType = GL_TEXTURE_3D;
	this->internalFormat = internalFormat;
}

Texture::Texture(GLuint width, GLuint height, GLuint depth, GLenum internalFormat, GLenum format, GLenum type,
	const void* data)
{
	glGenTextures(1, &id);
	glBindTexture(GL_TEXTURE_3D, id);
	glTexImage3D(GL_TEXTURE_3D, 0, internalFormat, width, height, depth, 0, format, type, data);
	textureType = GL_TEXTURE_3D;
	this->internalFormat = internalFormat;
}


void Texture::GenerateMipMaps() const
{
	glBindTexture(textureType, id);
	glGenerateMipmap(textureType);
}

Texture Texture::LoadTexture(const std::string& filename)
{
	int x, y = 0;
	int cif = 0;
	unsigned char* data = stbi_load(filename.c_str(), &x, &y, &cif, 4);
	if (data == nullptr) throw std::runtime_error("Reading the image file: \"" + filename + "\" went wrong");
	Texture out(x, y, GL_RGBA8, GL_RGBA, GL_UNSIGNED_BYTE, data);
	out.SetTexParameter(GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR, GL_REPEAT, GL_REPEAT, GL_REPEAT);
	out.GenerateMipMaps();
	return out;
}

Texture::Texture(GLuint width, GLuint height, GLenum internalFormat, GLenum format, GLenum type, const void* data)
{
	glGenTextures(1, &id);
	glBindTexture(GL_TEXTURE_2D, id);
	glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, format, type, data);
	textureType = GL_TEXTURE_2D;
	this->internalFormat = internalFormat;

}

void Texture::SetTexParameter(GLenum minFilter, GLenum magFilter, GLenum wrapS, GLenum wrapT, GLenum wrapR) const
{
	Bind();
	glTexParameteri(textureType, GL_TEXTURE_MAG_FILTER, magFilter);
	glTexParameteri(textureType, GL_TEXTURE_MIN_FILTER, minFilter);
	glTexParameteri(textureType, GL_TEXTURE_WRAP_S, wrapS);
	glTexParameteri(textureType, GL_TEXTURE_WRAP_T, wrapT);
	glTexParameteri(textureType, GL_TEXTURE_WRAP_R, wrapR);
}

void Texture::Fill(const std::array<unsigned char,4>& vals) const
{
	Bind();
	glClearTexImage(id, 0, GL_RGBA, GL_UNSIGNED_BYTE, vals.data());
	// Not implemented right now.
}

Texture::~Texture()
{
	glDeleteTextures(1, &id);
}

void Texture::Use(GLenum p_i) const
{
	glActiveTexture(GL_TEXTURE0 + p_i);
	Bind();
	glUniform1i(p_i, p_i);
}

void Texture::move(Texture&& other)
{
	this->id = other.id;
	this->textureType = other.textureType;
	this->internalFormat = other.internalFormat;
	other.id = 0;
}
