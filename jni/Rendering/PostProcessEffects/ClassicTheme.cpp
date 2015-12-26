#include "ClassicTheme.h"

ClassicTheme::ClassicTheme(int width, int height) : RenderPass(width, height){
	SetShader(ShaderManager::GetInstance()->LoadShader("ClassicTheme.vsh", "ClassicTheme.fsh"));
}

void ClassicTheme::SetCenter(Vector2* object){
	center = object;
}

void ClassicTheme::SetRadius(float r){
	radius = r;
}

void ClassicTheme::UpdateExtraUniforms(){
	shader->SetUniform2f("u_trackingPosition", center->x, center->y);
	shader->SetUniform1f("u_radius", radius);
}

ClassicTheme::~ClassicTheme(){
}
