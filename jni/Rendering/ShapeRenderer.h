#ifndef SHAPE_RENDERER_H_
#define SHAPE_RENDERER_H_

#include <GLES2/gl2.h>
#include <vector>
#include "../Core/Vector2.h"
#include "../Core/ShaderManager.h"

class ShapeRenderer {
private:
	std::vector<GLfloat> vertices;
	Shader *shader;
	int draws;
	bool pointMoved;

public:
	ShapeRenderer();

	void MoveTo(const Vector2& point);
	void LineTo(const Vector2& point);
	void Render(Matrix4 *cameraMatrix);
	void Dispose();
};

#endif
