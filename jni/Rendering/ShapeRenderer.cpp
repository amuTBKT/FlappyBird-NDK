#include "ShapeRenderer.h"

ShapeRenderer::ShapeRenderer(){
	shader = ShaderManager::GetInstance()->LoadShader("LineShader.vsh", "LineShader.fsh");
	draws = 0;
	pointMoved = false;
}

void ShapeRenderer::MoveTo(const Vector2& point){
	if (pointMoved){
		vertices.pop_back();
		vertices.pop_back();
	}
	vertices.push_back(point.x);
	vertices.push_back(point.y);
	pointMoved = true;
}

void ShapeRenderer::LineTo(const Vector2& point){
	if (!pointMoved){
		float prevX = vertices.at(vertices.size() - 2);
		float prevY = vertices.at(vertices.size() - 1);
		vertices.push_back(prevX);
		vertices.push_back(prevY);
	}
	
	vertices.push_back(point.x);
	vertices.push_back(point.y);

	draws +=2;
	pointMoved = false;
}

void ShapeRenderer::Render(Matrix4 *cameraMatrix){
	shader->Begin();
	shader->SetUniformMatrix(shader->cameraProjViewMatrixLocation, *cameraMatrix);
	if (vertices.size() > 0){
		glEnableVertexAttribArray(shader->positionAttribLocation);
		glVertexAttribPointer(shader->positionAttribLocation, 2, GL_FLOAT, false, 0, &vertices[0]);
		glDrawArrays(GL_LINES, 0, draws);
	}
	shader->End();
}

void ShapeRenderer::Dispose(){
	vertices.clear();
	draws = 0;
}
