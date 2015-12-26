#include "Shader.h"

Shader::Shader(){}

void Shader::GetAttribAndUniformLocations(){
	positionAttribLocation = glGetAttribLocation(programId, "a_position");
	texcoordAttribLocation = glGetAttribLocation(programId, "a_texCoord");
	modelMatrixUniformLocation = glGetUniformLocation(programId, "u_modelMatrix");
	cameraProjViewMatrixLocation = glGetUniformLocation(programId, "u_cameraMatrix");
}

void Shader::SetUniform1f(const char* uniform_name, float u){
	glUniform1f(glGetUniformLocation(programId, uniform_name), u);
}

void Shader::SetUniform1i(const char* uniform_name, int u){
	glUniform1i(glGetUniformLocation(programId, uniform_name), u);
}

void Shader::SetUniform2f(const char* uniform_name, float u, float v){
	glUniform2f(glGetUniformLocation(programId, uniform_name), u, v);
}

void Shader::SetUniform2i(const char* uniform_name, int u, int v){
	glUniform2i(glGetUniformLocation(programId, uniform_name), u, v);
}

void Shader::SetUniform3f(const char* uniform_name, float u, float v, float w){
	glUniform3f(glGetUniformLocation(programId, uniform_name), u, v, w);
}

void Shader::SetUniform3i(const char* uniform_name, int u, int v, int w){
	glUniform3i(glGetUniformLocation(programId, uniform_name), u, v, w);
}

void Shader::SetUniform4f(const char* uniform_name, float u, float v, float w, float x){
	glUniform4f(glGetUniformLocation(programId, uniform_name), u, v, w, x);
}

void Shader::SetUniform4i(const char* uniform_name, int u, int v, int w, int x){
	glUniform4i(glGetUniformLocation(programId, uniform_name), u, v, w, x);
}

void Shader::SetUniformMatrix(const char* uniform_name, Matrix4& matrix){
	glUniformMatrix4fv(glGetUniformLocation(programId, uniform_name), 1, false, matrix.GetData());
}

void Shader::SetUniformMatrix(int uniformIndex, Matrix4& matrix){
	glUniformMatrix4fv(uniformIndex, 1, false, matrix.GetData());
}

void Shader::Begin(){
	glUseProgram(programId);
}

void Shader::End(){
	glUseProgram(0);
}

GLuint &Shader::GetProgram(){
	return programId;
}

Shader::~Shader() {
	glDeleteProgram(programId);
}
