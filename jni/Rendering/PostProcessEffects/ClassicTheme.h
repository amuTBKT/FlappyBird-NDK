#ifndef PLAYER_TRACKER_PASS_H_
#define PLAYER_TRACKER_PASS_H_

#include "../RenderPass.h"
#include "../../Core/ShaderManager.h"

class ClassicTheme : public RenderPass{
private:
	Vector2 *center;
	float radius;
public:
	ClassicTheme(int width, int height);
	~ClassicTheme();

	void UpdateExtraUniforms();
	void SetCenter(Vector2* object);
	void SetRadius(float r);
};

#endif
