#include "Mesh.h"

Mesh::Mesh() {
	draws = 0;
	stride = 0;
	vbo = 0;
	material = new Material();
}

void Mesh::SetVertices(Vertex* vertices, int numVertices, const Vector2& scale){
	float *verts = new float[numVertices * 4];
	for (int i = 0; i < numVertices; i++){
		verts[i * 4 + 0] = vertices[i].position.x * scale.x;
		verts[i * 4 + 1] = vertices[i].position.y * scale.y;
		verts[i * 4 + 2] = vertices[i].texCoords.x;
		verts[i * 4 + 3] = vertices[i].texCoords.y;
	}

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, numVertices * 4 * sizeof(float), verts, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	
	// release verts
	delete[] verts;

	draws = numVertices;
	stride = 4 * sizeof(float);
}

void Mesh::SetMaterial(Material *mat){
	material = mat;
}

Material* Mesh::GetMaterial(){
	return material;
}

void Mesh::Render(Shader *shader, int renderMode){
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	
	glEnableVertexAttribArray(shader->positionAttribLocation);
	glEnableVertexAttribArray(shader->texcoordAttribLocation);
	
	glVertexAttribPointer(shader->positionAttribLocation, 2, GL_FLOAT, false, stride, 0);
	glVertexAttribPointer(shader->texcoordAttribLocation, 2, GL_FLOAT, false, stride, (void*)(stride / 2));

	glDrawArrays(renderMode, 0, draws);
	
	glDisableVertexAttribArray(shader->positionAttribLocation);
	glDisableVertexAttribArray(shader->texcoordAttribLocation);
	
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

Mesh::~Mesh() {
	glDeleteBuffers(1, &vbo);
	delete material;
}

