#include <g2e/gl/openglservice.h>
#include <g2e/core/Core.h>
#include <g2e/service/servicelocator.h>
#include <g2e/resource/resourceloaderservice.h>

using g2e::Core;
using g2e::io::ResourceLoaderService;

namespace g2e {
namespace gl {

OpenGLService::OpenGLService() {
}

OpenGLService::~OpenGLService() {
	for (auto i = buffer_map.begin(); i != buffer_map.end(); i++) {
		destroy(((opengl_buffers&) ((*i).first)));
	}

	for (auto i = program_list.begin(); i != program_list.end(); i++) {
		destroy(((opengl_buffers&) *i));
	}

	buffer_map.clear();
	program_list.clear();
}

opengl_buffers OpenGLService::upload(double* data, int size, GLuint type) {
	opengl_buffers buffers;
	buffer_map[*((long long*)&buffers)] = size;

	glGenVertexArrays(1, &(buffers.vao));
	glGenBuffers(1, &(buffers.vbo));

	glBindVertexArray((buffers.vao));
	glBindBuffer(GL_ARRAY_BUFFER, (buffers.vbo));
	glBufferData(GL_ARRAY_BUFFER, (sizeof(double)) * size, data, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	return buffers;
}

void OpenGLService::draw(opengl_buffers& buffers) {
	glBindVertexArray(buffers.vao);
	glBindBuffer(GL_ARRAY_BUFFER, buffers.vbo);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_DOUBLE, GL_FALSE, 0, 0);

	glDrawArrays(GL_TRIANGLES, 0, buffer_map[*((long long*)&buffers)]);

	glDisableVertexAttribArray(0);
}

opengl_program OpenGLService::createProgram(std::string vert, std::string frag) {
	ResourceLoaderService* resources = (ResourceLoaderService*) Core::service().get("ResourceLoaderService");

	// vertex

	GLuint vertshader = glCreateShader(GL_VERTEX_SHADER);
	const char *vstrFileData = resources->loadFile(vert);
	glShaderSource(vertshader, 1, &vstrFileData, NULL);
	glCompileShader(vertshader);

	GLint status;
	glGetShaderiv(vertshader, GL_COMPILE_STATUS, &status);
	if (status == GL_FALSE) std::cerr << "Error creating shader" << std::endl;

	// fragment

	GLuint fragshader = glCreateShader(GL_FRAGMENT_SHADER);
	const char* fstrFileData = resources->loadFile(frag);
	glShaderSource(fragshader, 1, &fstrFileData, NULL);
	glCompileShader(fragshader);

	glGetShaderiv(fragshader, GL_COMPILE_STATUS, &status);
	if (status == GL_FALSE) std::cerr << "Error creating shader" << std::endl;

	// program

	GLuint program = glCreateProgram();

	glAttachShader(program, vertshader); // vertex
	glAttachShader(program, fragshader); // fragment

	glLinkProgram(program);

	glGetProgramiv(program, GL_LINK_STATUS, &status);
	if (status == GL_FALSE) {
		GLint infoLogLength;
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &infoLogLength);

		GLchar *strInfoLog = new GLchar[infoLogLength + 1];
		glGetProgramInfoLog(program, infoLogLength, NULL, strInfoLog);
		delete[] strInfoLog;

		std::cerr << "Error creating program" << std::endl;
	}

	glDetachShader(program, fragshader); // fragment
	glDetachShader(program, vertshader); // vertex

	return program;
}

void OpenGLService::useProgram(opengl_program program) {
	glUseProgram(program);
}

void OpenGLService::unuseProgram() {
	glUseProgram(0);
}

void OpenGLService::setProjection(glm::mat4 p) {
	projection = p;
}

glm::mat4 OpenGLService::getProjection() {
	return projection;
}

void OpenGLService::setView(glm::mat4 v) {
	view = v;
}

glm::mat4 OpenGLService::getView() {
	return view;
}

glm::mat4 OpenGLService::getMVP(glm::mat4 model) {
	return projection * view * model;
}

} /* namespace gl */
} /* namespace g2e */
