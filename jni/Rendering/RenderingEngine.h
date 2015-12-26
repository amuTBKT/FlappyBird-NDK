#ifndef RENDERING_ENGINE_H_
#define RENDERING_ENGINE_H_

#include <GLES2/gl2.h>
#include <vector>
#include "../Components/GameObject.h"
#include "../Core/TextureManager.h"
#include "../Core/MeshManager.h"
#include "RenderPass.h"

class RenderingEngine
{
private:
	Matrix4 *cameraMatrix, *orthographicProjectionMatrix, *screenQuadModelMatrix;
	FrameBuffer *screenFrameBuffer;						// initial scene is rendered into this framebuffer
	Mesh *screenQuad;									// screen sized quad (mesh to render additional passes and final render)
	Texture *screenTexture;								// contains subsequent and final rendered image
	Shader *screenShader;								// screen shader
	std::vector<RenderPass *> renderPasses;				// post process effects
public:
	static RenderingEngine* GetInstance();
	RenderingEngine();

	int SCREEN_WIDTH, SCREEN_HEIGHT;					// screen width and height

	void Initialize(int width, int height);

	// render gameObject
	void RenderGameObject(GameObject *gameObject);

	// get screen frameBuffer (initial rendered scene)
	FrameBuffer *GetScreenFrameBuffer();
	
	// add post process effect to rendering pipeline
	void AddRenderPass(RenderPass *pass);

	// apply post process effects
	void RenderAdditionalPasses();

	// bind passed framebuffer to screen
	void BindFrameBufferToScreen(FrameBuffer *frameBuffer);
	
	// render final image to screen
	void RenderToScreen();

	// set camera matrix for renderin scene (not the final render, for that we use orthographicProjectionMatrix)
	void SetCameraMatrix(Matrix4 *matrix);

	// returns a screen sized quad
	Mesh *GetScreenQuad();

	// start alpha blending
	void StartBlending(int blendSrc, int blendDst);
	// stop alpha blending
	void StopBlending();

	// reset rendering pipeline (clears renderPasses)
	void Reset();

	// dispose
	void Dispose();
};

#endif
