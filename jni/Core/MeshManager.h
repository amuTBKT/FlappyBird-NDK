#ifndef MESH_MANAGER_H_
#define MESH_MANAGER_H_

#include <vector>
#include "../Rendering/Mesh.h"

class MeshManager{
private:
	std::vector<Mesh *> meshes;
public:
	static MeshManager* GetInstance();
	
	Mesh* CreateMesh(Vertex *vertices, int numVertices, const Vector2 &scale);
	Mesh* CreateQuad(const Vector2& scale);
	void Dispose();

};

#endif
