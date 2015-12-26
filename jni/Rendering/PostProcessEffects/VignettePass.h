#ifndef VIGNETTE_PASS_H_
#define VIGNETTE_PASS_H_

#include "../RenderPass.h"
#include "../../Core/ShaderManager.h"

class VignettePass : public RenderPass{
public:
	VignettePass(int width, int height);
	~VignettePass();

	void UpdateExtraUniforms();
};

#endif