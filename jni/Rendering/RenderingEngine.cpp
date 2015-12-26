#include "RenderingEngine.h"

RenderingEngine::RenderingEngine(){
	screenFrameBuffer = 0;
	screenQuad = 0;
	screenTexture = 0;
	screenQuadModelMatrix = 0;
	orthographicProjectionMatrix = 0;
	cameraMatrix = 0;
	screenShader = 0;
}

RenderingEngine* RenderingEngine::GetInstance(){
	static RenderingEngine *instance;

	if (instance == 0){
		instance = new RenderingEngine();
	}

	return instance;
}

void RenderingEngine::Initialize(int width, int height){
	SCREEN_WIDTH = width;
	SCREEN_HEIGHT = height;

	Texture *texture = TextureManager::GetInstance()->CreateTexture(SCREEN_WIDTH, SCREEN_HEIGHT, GL_LINEAR, GL_REPEAT);
	screenFrameBuffer = new FrameBuffer(SCREEN_WIDTH, SCREEN_HEIGHT, texture);

	cameraMatrix = new Matrix4();

	orthographicProjectionMatrix = new Matrix4();
	orthographicProjectionMatrix->InitOrthographic(0, SCREEN_WIDTH, 0, SCREEN_HEIGHT, 0, 10);

	screenTexture = TextureManager::GetInstance()->CreateTexture(SCREEN_WIDTH, SCREEN_HEIGHT, GL_LINEAR, GL_REPEAT);
	screenShader = ShaderManager::GetInstance()->LoadShader("ScreenShader.vsh", "ScreenShader.fsh");

	screenQuadModelMatrix = new Matrix4();
	screenQuadModelMatrix->InitTranslation(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
}

void RenderingEngine::SetCameraMatrix(Matrix4 *matrix){
	*cameraMatrix = *matrix;
}

Mesh* RenderingEngine::GetScreenQuad(){
	return screenQuad;
}

void RenderingEngine::StartBlending(int blendSrc, int blendDst){
	glEnable(GL_BLEND);
	glBlendFunc(blendSrc, blendDst);
}

void RenderingEngine::StopBlending(){
	glDisable(GL_BLEND);
}

void RenderingEngine::RenderGameObject(GameObject *gameObj){
	gameObj->mesh->GetMaterial()->UpdateShader(cameraMatrix, gameObj->GetModelMatrix());
	gameObj->mesh->Render(gameObj->mesh->GetMaterial()->GetShader(), GL_TRIANGLES);
	gameObj->mesh->GetMaterial()->GetShader()->End();
}

FrameBuffer *RenderingEngine::GetScreenFrameBuffer(){
	return screenFrameBuffer;
}

void RenderingEngine::AddRenderPass(RenderPass *pass){
	renderPasses.push_back(pass);
}

void RenderingEngine::BindFrameBufferToScreen(FrameBuffer *frameBuffer){
	if (frameBuffer == 0){
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
		return;
	}
	glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer->GetFrameBufferId());
	glViewport(0, 0, frameBuffer->textureWidth, frameBuffer->textureHeight);
}

void RenderingEngine::RenderAdditionalPasses(){
	screenTexture->SetTextureId(screenFrameBuffer->GetTexture()->GetTextureId());

	// check for additional passes
	RenderPass *pass;
	for (int i = 0; i < renderPasses.size(); i++){
		pass = renderPasses[i];
		
		// bind framebuffer for rendering
		BindFrameBufferToScreen(pass->GetFrameBuffer());
		
		// clear framebuffer
		pass->GetFrameBuffer()->Clear(0, 0, 0, 1);
		
		// begin and update passe's shader
		pass->UpdateShader(screenTexture->GetTextureId(), orthographicProjectionMatrix, screenQuadModelMatrix);
		pass->GetShader()->SetUniform2f("u_resolution", SCREEN_WIDTH, SCREEN_HEIGHT);
		pass->UpdateExtraUniforms();

		// render screen sized quad (render pass effects apply to screen texture)
		screenQuad->Render(pass->GetShader(), GL_TRIANGLES);
		pass->EndShader();

		// set screen texture to current pass's texture
		screenTexture->SetTextureId(pass->GetFrameBuffer()->GetTexture()->GetTextureId());
	}

	// render final image to screen
	RenderToScreen();
}

void RenderingEngine::RenderToScreen(){
	// render to screen
	BindFrameBufferToScreen(0);

	screenQuad->GetMaterial()->UpdateShader(orthographicProjectionMatrix, screenQuadModelMatrix);
	screenQuad->GetMaterial()->GetShader()->SetUniform2f("u_resolution", SCREEN_WIDTH, SCREEN_HEIGHT);
	screenQuad->Render(screenQuad->GetMaterial()->GetShader(), GL_TRIANGLES);
	screenQuad->GetMaterial()->GetShader()->End();
}

void RenderingEngine::Reset(){
	if (screenQuad != NULL){
		screenQuad = 0;
	}
	screenQuad = MeshManager::GetInstance()->CreateQuad(Vector2(SCREEN_WIDTH, SCREEN_HEIGHT));
	screenQuad->GetMaterial()->SetShader(screenShader);
	screenQuad->GetMaterial()->SetDiffuseTexture(screenTexture);

	// dispose render passes
	for (int i = 0; i < renderPasses.size(); i++){
		delete renderPasses.at(i);
	}
	renderPasses.clear();
}

void RenderingEngine::Dispose(){
	delete cameraMatrix;
	delete screenQuadModelMatrix;
	delete orthographicProjectionMatrix;

	delete screenFrameBuffer;
	delete screenTexture;

	for (int i = 0; i < renderPasses.size(); i++){
		delete renderPasses.at(i);
	}
	renderPasses.clear();
}
