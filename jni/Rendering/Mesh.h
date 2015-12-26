#ifndef MESH_H_
#define MESH_H_

#include <GLES2/gl2.h>
#include "Material.h"

struct Vertex{
	Vector2 position;
	Vector2 texCoords;

	Vertex(){}
	Vertex(const Vector2& pos){
		position = pos;
	}
	Vertex(const Vector2& pos, const Vector2& texcoord){
		position = pos;
		texCoords = texcoord;
	}
};

class Mesh {
public:
	// vertex buffer
	GLuint vbo;
	// draw calls, stride
	int draws, stride;
	// material
	Material *material;

	Mesh();
	virtual ~Mesh();

	void SetVertices(Vertex *, int, const Vector2&);
	void SetMaterial(Material *mat);
	Material *GetMaterial();
	void Render(Shader*, int);
};

#endif
