/*
 * Mesh.h
 *
 *  Created on: Nov 19, 2014
 *      Author: Jake
 */

#ifndef G2E_GL_MESH_H_
#define G2E_GL_MESH_H_

#include <iostream>

#include <gl3w.h>
#include <glcorearb.h>
#include <GL/gl.h>
#include <vector>
#include <algorithm>

#include "../../g2e/math/Vector3.h"

namespace g2e {
namespace gl {

class Mesh {
public:
	Mesh(int);
	virtual ~Mesh();

	void upload();
	void destroy();

	void render();

	void vertex(double, double, double);
	void vertex(g2e::math::Vector3 v) { vertex(v.x(), v.y(), v.z()); }
private:
	int size;
	double* vertices;
	GLuint vbuffer, varray, program;

	int curallocation_ = 0;
};

} /* namespace g2e */
}

#endif /* G2E_GL_MESH_H_ */
