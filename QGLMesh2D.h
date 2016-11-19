#ifndef QMSG_QGLMESH_H
#define QMSG_QGLMESH_H

#include "QVersion.h"

#include "QGL.h"
#include "QGLPolygon.h"
#include "QGLVertex.h"

#include <algorithm>
#include <vector>

class QGLMesh2D {
public:
	QGLMesh2D() {}
	~QGLMesh2D() {}

	inline void add_triangle(QGLTriangle2D triangle) {
		triangles_.push_back(triangle);
	}

	inline std::vector<QGLTriangle2D> get_triangles() {
		return triangles_;
	}

	inline std::vector<GLfloat> collect_vertex_data() {
		std::vector<GLfloat> vertices;
		vertices.reserve(triangles_.size() * 3 * 2);
		std::transform(triangles_.begin(), triangles_.end(), vertices, [](auto &t) -> { t.get_vertices() });
		return vertices;
	}
private:
	std::vector<QGLTriangle2D> triangles_;
};

#endif
