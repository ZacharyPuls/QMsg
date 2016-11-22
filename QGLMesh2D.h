#ifndef QMSG_QGLMESH_H
#define QMSG_QGLMESH_H

#include "QVersion.h"

#include "QGL.h"
#include "QGLPolygon.h"
#include "QGLVertex.h"

#include <algorithm>
#include <initializer_list>
#include <vector>

class QGLMesh2D {
public:
	QGLMesh2D() {

	}

	~QGLMesh2D() {

	}

	inline void add_triangle(QGLTriangle2D triangle) {
		triangles_.push_back(triangle);
	}

	inline void add_triangles(std::vector<QGLTriangle2D> triangles) {
		triangles_.insert(triangles_.end(), triangles.begin(), triangles.end());
	}

	inline std::vector<QGLTriangle2D> get_triangles() {
		return triangles_;
	}

	inline std::vector<GLfloat> collect_vertex_data() const {
		std::vector<GLfloat> vertices;
		vertices.reserve(triangles_.size() * 3 * 2);

		for (auto &triangle : triangles_) {
			for (auto &vertex : triangle.get_vertices()) {
				vertices.push_back(vertex);
			}
		}

		return vertices;
	}

	inline std::vector<GLfloat> collect_texcoord_data() const {
		std::vector<GLfloat> texcoords;
		texcoords.reserve(triangles_.size() * 3 * 2);

		for (auto &triangle : triangles_) {
			for (auto &texcoord : triangle.get_texcoords()) {
				texcoords.push_back(texcoord);
			}
		}

		return texcoords;
	}

	inline void clear() {
		triangles_.clear();
	}
private:
	std::vector<QGLTriangle2D> triangles_;
};

#endif
