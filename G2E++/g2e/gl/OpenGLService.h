#ifndef GL_OPENGLSERVICE_H_
#define GL_OPENGLSERVICE_H_

#define GLSL(src) "#version 150 core\n" #src

#include <gl3w.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <string>
#include <vector>
#include <map>

#include <g2e/service/service.h>

namespace g2e {
namespace gl {

typedef struct {
	GLuint vao, vbo;
} opengl_buffers;

typedef GLuint opengl_program;

class OpenGLService : public g2e::service::Service {
public:
	OpenGLService();
	virtual ~OpenGLService();
	virtual std::string getClass() { return "OpenGLService"; }

	opengl_buffers upload(double* data, int size, GLuint type);
	void destroy(opengl_buffers& buffers) {} // TODO: implement
	void draw(opengl_buffers& buffers);

	opengl_program createProgram(std::string vert, std::string frag);
	opengl_program createProgramSrc(const char* vert, const char* frag);
	void useProgram(opengl_program program);
	void unuseProgram();

	void setProjection(glm::mat4);
	glm::mat4 getProjection();
	void setView(glm::mat4);
	glm::mat4 getView();
	glm::mat4 getMVP(glm::mat4); // argument is model matrix (position)
private:
	std::map<long long, int> buffer_map;
	std::vector<opengl_program> program_list;

	glm::mat4 view, projection;
};

} /* namespace gl */
} /* namespace g2e */

#endif /* GL_OPENGLSERVICE_H_ */
