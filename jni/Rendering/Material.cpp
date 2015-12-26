#include "Material.h"

Material::Material()
{
	transparency = 1;
	shader = ShaderManager::GetInstance()->GetDefaultShader();
	diffuseTexture = 0;
}

Material::~Material(){
	diffuseTexture = 0;
}

void Material::SetDiffuseTexture(Texture *tex){
	diffuseTexture = tex;
	diffuseTiling.set(1, 1);
	diffuseOffset.set(0, 0);
}

void Material::SetDiffuseTextureTiling(const Vector2 &tiling){
	diffuseTiling = tiling;
}

void Material::SetDiffuseTextureTiling(float x, float y){
	diffuseTiling.x = x;
	diffuseTiling.y = y;
}

void Material::SetDiffuseTextureOffset(const Vector2 &offset){
	diffuseOffset = offset;
}

void Material::SetDiffuseTextureOffset(float x, float y){
	diffuseOffset.x = x;
	diffuseOffset.y = y;
}

void Material::SetShader(Shader *shdr){
	shader = shdr;
}

void Material::SetTint(const COLOR &color){
	tint = color;
}

void Material::SetTint(float r, float g, float b, float a){
	tint.r = r;
	tint.g = g;
	tint.b = b;
	tint.a = a;
}

void Material::UpdateShader(Matrix4 *cameraMatrix, Matrix4 *modelMatrix){
	shader->Begin();
	shader->SetUniformMatrix(shader->cameraProjViewMatrixLocation, *cameraMatrix);
	shader->SetUniformMatrix(shader->modelMatrixUniformLocation, *modelMatrix);
	shader->SetUniform4f("u_tintColor", tint.r, tint.g, tint.b, tint.a);
	shader->SetUniform4f("u_tiling_offset", diffuseTiling.x, diffuseTiling.y, diffuseOffset.x, diffuseOffset.y);
	shader->SetUniform1f("u_transparency", transparency);

	if (diffuseTexture != 0){
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, diffuseTexture->GetTextureId());
		shader->SetUniform1i("u_diffuseTexture", 0);
	}
}

Shader* Material::GetShader() const{
	return shader;
}

Texture* Material::GetDiffuseTexture() const{
	return diffuseTexture;
}
