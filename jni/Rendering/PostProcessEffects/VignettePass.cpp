#include "VignettePass.h"

VignettePass::VignettePass(int width, int height) : RenderPass(width, height){
	SetShader(ShaderManager::GetInstance()->LoadShader("Vignette.vsh", "Vignette.fsh"));
}

void VignettePass::UpdateExtraUniforms(){

}

VignettePass::~VignettePass(){}
