#include "NumberRenderer.h"

NumberRenderer::NumberRenderer(char *name) : GameObjectGroup(name){
	Texture *texture = TextureManager::GetInstance()->LoadTexture("numbers_atlas1.png", GL_NEAREST, GL_REPEAT);
	Sprite *score1 = new Sprite(texture, "units_place");
	score1->SetNumFrames(10, 1);
	score1->Scale(1.0 / 10.0, 1.0);
	score1->SetPosition(score1->GetWidth() / 2.0, 0);

	Sprite *score2 = new Sprite(texture, "tens_place");
	score2->SetNumFrames(10, 1);
	score2->Scale(1.0 / 10.0, 1.0);
	score2->SetPosition(-score2->GetWidth() / 2.0, 0);

	AddGameObject(score1);
	AddGameObject(score2);

	width = score1->GetWidth() * 2;
	height = score1->GetHeight();
}

void NumberRenderer::UpdateNumber(int number){
	GetGameObjectAtIndex(0)->GetMesh()->GetMaterial()->SetDiffuseTextureOffset(number / 10.0, 0);
	GetGameObjectAtIndex(1)->GetMesh()->GetMaterial()->SetDiffuseTextureOffset((number / 10) / 10.0, 0);
}

NumberRenderer::~NumberRenderer(){

}
