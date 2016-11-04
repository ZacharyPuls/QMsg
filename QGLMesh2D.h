#ifndef QMSG_QGLMESH_H
#define QMSG_QGLMESH_H

#include "QVersion.h"

#include "QGLPolygon.h"

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
private:
	std::vector<QGLTriangle2D> triangles_;
};

#endif
