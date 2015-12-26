#ifndef SHADER_MANAGER_H_
#define SHADER_MANAGER_H_

#include <string>
#include <vector>
#include "FileLoader.h"
#include "../Rendering/Shader.h"

using namespace std;

class ShaderManager{
private:
	Shader *defaultShader;
	std::vector<Shader *> loadedShaders;

	GLuint CreateGLShader(string &src, GLenum type);
	void CreateGLProgram(GLuint &programId, GLuint vertShader, GLuint fragShader);

public:
	static ShaderManager* GetInstance();

	void Initialize();
	Shader* LoadShader(const char* vertSrc, const char* fragSrc);
	Shader* CreateShader(string &vertSrc, string &fragSrc);
	void Dispose();
	Shader* GetDefaultShader();
};

#endif
