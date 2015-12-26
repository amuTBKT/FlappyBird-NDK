#include "ShaderManager.h"

ShaderManager *ShaderManager::GetInstance(){
	static ShaderManager *instance;

	if (instance == NULL){
		instance = new ShaderManager();
	}

	return instance;
}

void ShaderManager::Initialize(){
//	string vert_default_shader, frag_default_shader;
//
//	vert_default_shader = "";
//	vert_default_shader.append("attribute vec2 a_position; \n");
//	vert_default_shader.append("attribute vec2 a_texCoord; \n");
//	vert_default_shader.append("uniform mat4 u_modelMatrix;  	\n");
//	vert_default_shader.append("uniform mat4 u_cameraMatrix;  	\n");
//	vert_default_shader.append("varying vec2 v_texCoord;  	\n");
//	vert_default_shader.append("void main(){               \n");
//	vert_default_shader.append("v_texCoord = a_texCoord;					\n");
//	vert_default_shader.append("gl_Position = u_cameraMatrix * u_modelMatrix * vec4(a_position, 0.0, 1.0);  	\n");
//	vert_default_shader.append("}                          					\n");
//
//	frag_default_shader = "";
//	frag_default_shader.append("precision mediump float;    	\n");
//	frag_default_shader.append("varying vec2 v_texCoord;  		\n");
//	frag_default_shader.append("uniform vec4 u_tintColor;  	\n");
//	frag_default_shader.append("uniform vec4 u_tiling_offset;  	\n");
//	frag_default_shader.append("uniform float u_transparency;  	\n");
//	frag_default_shader.append("uniform sampler2D u_diffuseTexture;  	\n");
//	frag_default_shader.append("void main(){                	\n");
//	frag_default_shader.append("vec2 texCoord = vec2(v_texCoord.x, 1.0 - v_texCoord.y) * u_tiling_offset.xy + u_tiling_offset.zw;   \n");
//	frag_default_shader.append("gl_FragColor = texture2D(u_diffuseTexture, texCoord) * u_tintColor * u_transparency;	\n");
//	frag_default_shader.append("}                           	\n");
//
//	defaultShader = CreateShader(vert_default_shader, frag_default_shader);

	defaultShader = LoadShader("DefaultShader.vsh", "DefaultShader.fsh");
}

Shader* ShaderManager::GetDefaultShader(){
	return defaultShader;
}

Shader* ShaderManager::LoadShader(const char *vertFile, const char *fragFile){
	// absolute path to shader file
	string absolutePathForVertexShader = "Shaders/";
	string absolutePathForFragmentShader = "Shaders/";

	absolutePathForVertexShader.append(vertFile);
	absolutePathForFragmentShader.append(fragFile);

	// char pointers to hold shader file data
	char *vertData;
	char *fragData;

	// shader file size
	long vertDataSize;
	long fragDataSize;

	// load shader file
	FileLoader::GetInstance()->LoadFile(&vertData, vertDataSize, absolutePathForVertexShader.c_str());
	FileLoader::GetInstance()->LoadFile(&fragData, fragDataSize, absolutePathForFragmentShader.c_str());

	string vertSrc(vertData, vertDataSize);
	string fragSrc(fragData, fragDataSize);

	return CreateShader(vertSrc, fragSrc);
}

Shader* ShaderManager::CreateShader(string &vert, string &frag){
	Shader *shader = new Shader();
	loadedShaders.push_back(shader);

	// create vertex shader
	GLuint vertShader = CreateGLShader(vert, GL_VERTEX_SHADER);
	
	// create fragment shader
	GLuint fragShader = CreateGLShader(frag, GL_FRAGMENT_SHADER);
	
	// link vertex and fragmet shader to create shader program
	CreateGLProgram(shader->GetProgram(), vertShader, fragShader);
	
	// store attribute location in shader member variables
	shader->GetAttribAndUniformLocations();

	// dispose vertex and fragment shader
	glDeleteShader(vertShader);
	glDeleteShader(fragShader);

	return shader;
}

GLuint ShaderManager::CreateGLShader(string &src, GLenum type){
	GLchar const* files[] = { src.c_str() };
	GLint const size[] = { src.length() };

	GLuint shader = glCreateShader(type);
	glShaderSource(shader, 1, files, size);
	glCompileShader(shader);

	//// check for compilation error ////
	GLint isCompiled = 0;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);
	if (isCompiled == GL_FALSE) {
		GLint maxLength = 0;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

		char* errorLog = new char[maxLength];
		glGetShaderInfoLog(shader, maxLength, &maxLength, &errorLog[0]);

//		ALOG("Shader Compilation Error: %s", errorLog);

		// dispose the shader
		glDeleteShader(shader);
	}
	/////////////////////////////////////

	return shader;
}

void ShaderManager::CreateGLProgram(GLuint &programId, GLuint vertShader, GLuint fragShader){
	programId = glCreateProgram();
	glAttachShader(programId, vertShader);
	glAttachShader(programId, fragShader);

	glBindAttribLocation(programId, 0, "a_position");
	glBindAttribLocation(programId, 1, "a_texCoord");
	
	glLinkProgram(programId);
}

void ShaderManager::Dispose(){
	for (int i = 0; i < loadedShaders.size(); i++){
		delete loadedShaders[i];
	}
	loadedShaders.clear();
}
