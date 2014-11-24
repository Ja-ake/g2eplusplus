/*
 * Mesh.cpp
 *
 *  Created on: Nov 19, 2014
 *      Author: Jake
 */

#include "Mesh.h"
#include <stdexcept>
#include <fstream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

GLuint createShader(GLenum eShaderType, const std::string &strShaderFile) {
	GLuint shader = glCreateShader(eShaderType);
	const char *strFileData = strShaderFile.c_str();
	glShaderSource(shader, 1, &strFileData, NULL);
	glCompileShader(shader);

	GLint status;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
	if (status == GL_FALSE) {
		GLint infoLogLength;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLogLength);

		GLchar *strInfoLog = new GLchar[infoLogLength + 1];
		glGetShaderInfoLog(shader, infoLogLength, NULL, strInfoLog);

		const char *strShaderType = NULL;
		switch (eShaderType) {
		case GL_VERTEX_SHADER:
			strShaderType = "vertex";
			break;
		case GL_GEOMETRY_SHADER:
			strShaderType = "geometry";
			break;
		case GL_FRAGMENT_SHADER:
			strShaderType = "fragment";
			break;
		}

		std::cerr << "Error creating shader" << std::endl;
		delete[] strInfoLog;
	}

	return shader;
}

GLuint CreateProgram(const std::vector<GLuint> &shaderList) {
	GLuint program = glCreateProgram();

	for (size_t iLoop = 0; iLoop < shaderList.size(); iLoop++)
		glAttachShader(program, shaderList[iLoop]);

	glLinkProgram(program);

	GLint status;
	glGetProgramiv(program, GL_LINK_STATUS, &status);
	if (status == GL_FALSE) {
		GLint infoLogLength;
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &infoLogLength);

		GLchar *strInfoLog = new GLchar[infoLogLength + 1];
		glGetProgramInfoLog(program, infoLogLength, NULL, strInfoLog);
		delete[] strInfoLog;

		std::cerr << "Error creating program" << std::endl;
	}

	for (size_t iLoop = 0; iLoop < shaderList.size(); iLoop++)
		glDetachShader(program, shaderList[iLoop]);

	return program;
}

GLuint InitializeProgram() {
	std::vector<GLuint> shaderList;

	shaderList.push_back(
			createShader(GL_FRAGMENT_SHADER,
					"#version 330\r\n out vec4 outputColor;void main(){outputColor = vec4(0.0f, 0.0f, 1.0f, 1.0f);}"));
	shaderList.push_back(createShader(GL_VERTEX_SHADER, "#version 330\r\n"
			"in vec3 position;"
			"uniform mat4 MVP;"
			"void main() {"
			"    gl_Position = MVP*vec4(position, 1.0f);"
			"}"));

	GLuint ret = CreateProgram(shaderList);

	std::for_each(shaderList.begin(), shaderList.end(), glDeleteShader);

	return ret;
}

glm::vec2 SCREEN_SIZE(640, 480); //screen size
glm::mat4 projectionMatrix; // Store the projection matrix
glm::mat4 viewMatrix; // Store the view matrix
glm::mat4 modelMatrix; // Store the model matrix

namespace g2e {
namespace gl {

Mesh::Mesh(int s) :
		size(s * 3), vbuffer(0), varray(0), program(0) {
	vertices = new double[size];
}

Mesh::~Mesh() {
	delete[] vertices;
}

void Mesh::upload() {
	program = InitializeProgram();

	glGenVertexArrays(1, &varray);
	glGenBuffers(1, &vbuffer);

	glBindVertexArray(varray);
	glBindBuffer(GL_ARRAY_BUFFER, vbuffer);
	glBufferData(GL_ARRAY_BUFFER, (sizeof(double)) * size, vertices,
	GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Mesh::destroy() {

}
double d=0;
void Mesh::render() {
	glUseProgram(program);

	// Projection matrix : 45° Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
	projectionMatrix = glm::perspective(45.0f,
			(float) SCREEN_SIZE.x / (float) SCREEN_SIZE.y, 1.0f, 200.0f);
	// Camera matrix
	viewMatrix = glm::lookAt(glm::vec3(10*cos(d), 0, 10*sin(d)), // Camera is at (4,3,3), in World Space
	glm::vec3(0, 0, 0), // and looks at the origin
	glm::vec3(0, 1, 0)  // Head is up (set to 0,-1,0 to look upside-down)
			);
	d+=0.001;
	// Model matrix : an identity matrix (model will be at the origin)
	modelMatrix = glm::mat4(1.0f);  // Changes for each model !
	// Our ModelViewProjection : multiplication of our 3 matrices

	// Remember, matrix multiplication is the other way around
	glm::mat4 MVP = projectionMatrix * viewMatrix * modelMatrix;
	//MVP = projectionMatrix;

	// Get a handle for our "MVP" uniform.
	// Only at initialisation time.
	GLuint MatrixID = glGetUniformLocation(program, "MVP");

	// Send our transformation to the currently bound shader,
	// in the "MVP" uniform
	// For each model you render, since the MVP will be different (at least the M part)
	glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);

	glBindVertexArray(varray);
	glBindBuffer(GL_ARRAY_BUFFER, vbuffer);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_DOUBLE, GL_FALSE, 0, 0);

	glDrawArrays(GL_TRIANGLES, 0, size);

	glDisableVertexAttribArray(0);
	glUseProgram(0);

//	std::cout << "really" << std::endl;
}

void Mesh::vertex(double x, double y, double z) {
	if (curallocation_ > size - 2)
		throw std::runtime_error("Vertex array not big enough");
	vertices[curallocation_++] = x;
	vertices[curallocation_++] = y;
	vertices[curallocation_++] = z;
}

} /* namespace gl */
} /* namespace g2e */
