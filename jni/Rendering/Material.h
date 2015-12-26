#ifndef MATERIAL_H_
#define MATERIAL_H_

#include "../Core/ShaderManager.h"
#include "Texture.h"

struct COLOR{
	float r, g, b, a;

	COLOR(){
		r = g = b = a = 1; 
	}

	COLOR(float _r, float _g, float _b, float _a){
		r = _r;
		g = _g;
		b = _b;
		a = _a;
	}
};

class Material
{
private:
	/*
	* diffseTexture	: base color
	* diffuseTiling	: to scale texture (using shader)
	* diffuseOffset : to pan texture (using shader)
	* shader		: shader to render the mesh
	* tint			: tint for base texture
	*/
	Texture *diffuseTexture;
	Vector2 diffuseTiling;
	Vector2 diffuseOffset;
	Shader *shader;
	COLOR tint;
public:
	float transparency;

	void SetDiffuseTexture(Texture *tex);
	void SetShader(Shader *shdr);
	void SetTint(const COLOR &color);
	void SetTint(float r, float g, float b, float a);
	
	void SetDiffuseTextureTiling(const Vector2 &tiling);
	void SetDiffuseTextureTiling(float x, float y);
	void SetDiffuseTextureOffset(const Vector2 &offset);
	void SetDiffuseTextureOffset(float x, float y);

	// update shader uniforms
	void UpdateShader(Matrix4 *cameraMatrix, Matrix4 *modelMatrix);

	Shader *GetShader() const;
	Texture *GetDiffuseTexture() const;

	Material();
	~Material();
};

#endif

