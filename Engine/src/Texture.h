#pragma once
#include "glad/glad.h"
#include "NonCopyable.h"
#include <utility>
#include <array>


/*enum class TextureType
{
	Diffuse,
	SpecularRough,
	SpecularMetallic,
	SpecularBoth,
	Emissive,
	Normal
};*/

class Texture 
{
public:
	MAKE_NO_COPY(Texture)
	MAKE_SIMPLE_MOVE(Texture)
	Texture() = default;
	Texture(const std::string& filename);
	Texture static LoadTexture(const std::string& filename);
	Texture(GLuint width, GLuint height, GLenum internalFormat, GLenum format, GLenum type, const void* data);
	Texture(GLuint width, GLuint height, GLenum internalFormat, GLenum format, GLenum type, const void* data,
		GLenum minFilter, GLenum magFilter, GLenum wrapS, GLenum wrapT);
	Texture(GLuint width, GLuint height, GLuint depth, GLenum internalFormat, GLenum format, GLenum type, const void* data);
	Texture(GLuint width, GLuint height, GLuint depth, GLenum internalFormat, GLenum format, GLenum type, const void* data,
		GLenum minFilter, GLenum magFilter, GLenum wrapS, GLenum wrapT);
	Texture(GLuint width, GLuint height, GLenum internalFormat, GLuint amountLevels);
	Texture(GLuint width, GLuint height, GLuint depth, GLenum internalFormat, GLuint amountLevels);
	void GenerateMipMaps() const;
	void SetTexParameter(GLenum minFilter = GL_NEAREST, GLenum magFilter = GL_NEAREST, GLenum wrapS = GL_CLAMP_TO_BORDER, GLenum wrapT = GL_CLAMP_TO_BORDER, GLenum wrapR = GL_CLAMP_TO_BORDER) const;
	void Fill(const std::array<unsigned char,4>& vals) const;
	/*Texture(GLuint width, GLuint height, GLuint depth, GLenum internalFormat, GLenum format, GLenum type, const void* data,
	        GLenum magFilter, GLenum minFilter, GLenum wrapS, GLenum wrapT);*/
	~Texture();
    void Bind() const
    {
        glBindTexture(textureType,id);
    }

	void Bind(GLuint location, GLenum access = GL_READ_WRITE, GLint level = 0) const
    {
		glBindImageTexture(location, id, level, GL_FALSE, 0, access, internalFormat);
    }

	GLuint GetID() const
    {
		return id;
    }

	void Use(GLenum p_i) const;

private:
	GLuint id = 0;
	GLenum textureType;
	GLenum internalFormat;
	void move(Texture&& other);
};