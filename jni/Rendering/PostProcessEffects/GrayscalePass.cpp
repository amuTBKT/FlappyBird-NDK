#include "GrayscalePass.h"

GrayscalePass::GrayscalePass(int width, int height) : RenderPass(width, height){
	SetShader(ShaderManager::GetInstance()->LoadShader("GrayScale.vsh", "GrayScale.fsh"));
}

void GrayscalePass::UpdateExtraUniforms(){

}

GrayscalePass::~GrayscalePass(){}
