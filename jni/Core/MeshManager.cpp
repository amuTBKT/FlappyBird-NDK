#include "MeshManager.h"

MeshManager *MeshManager::GetInstance(){
	static MeshManager *instance;

	if (instance == NULL){
		instance = new MeshManager();
	}

	return instance;
}

Mesh* MeshManager::CreateMesh(Vertex *vertices, int numVertices, const Vector2 &scale){
	Mesh* mesh = new Mesh();
	mesh->SetVertices(vertices, numVertices, scale);
	meshes.push_back(mesh);
	return mesh;
}

Mesh* MeshManager::CreateQuad(const Vector2& scale){
	// for better performance
	static Vertex *quadVertices;

	if (quadVertices == NULL){
		quadVertices = new Vertex[6];

		quadVertices[0] = Vertex(Vector2(-0.5, 0.5), Vector2(0, 1));
		quadVertices[1] = Vertex(Vector2(0.5, 0.5), Vector2(1, 1));
		quadVertices[2] = Vertex(Vector2(0.5, -0.5), Vector2(1, 0));

		quadVertices[3] = Vertex(Vector2(0.5, -0.5), Vector2(1, 0));
		quadVertices[4] = Vertex(Vector2(-0.5, -0.5), Vector2(0, 0));
		quadVertices[5] = Vertex(Vector2(-0.5, 0.5), Vector2(0, 1));

	}

	Mesh *mesh = CreateMesh(&quadVertices[0], 6, scale);
	return mesh;
}

void MeshManager::Dispose(){
	// dispose models
	for (int i = 0; i < meshes.size(); i++){
		delete meshes.at(i);
	}
	meshes.clear();
}
