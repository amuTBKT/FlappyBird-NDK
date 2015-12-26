#ifndef GRAY_SCALE_PASS_H_
#define GRAY_SCALE_PASS_H_

#include "../RenderPass.h"
#include "../../Core/ShaderManager.h"

class GrayscalePass : public RenderPass{
public:
	GrayscalePass(int width, int height);
	~GrayscalePass();

	void UpdateExtraUniforms();
};

#endif