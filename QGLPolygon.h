#ifndef QMSG_QGLPOLYGON_H
#define QMSG_QGLPOLYGON_H

#include "QVersion.h"

#include "QGLVertex.h"

#include <array>

// T = type, data type for vertices (Preferably a QGLVertex<> type, e.g. QGLVertex3f, QGLVertex3d, etc.)
// N = number, number of points per polygon
template<class T, unsigned char N> class QGLPolygon {
public:
	QGLPolygon() {}
	~QGLPolygon() {}

	inline void set_vertices(Array_ vertices) {
		vertices_ = vertices;
	}

	inline Array_ get_vertices() {
		return vertices_;
	}
private:
	typedef std::array<T, N> Array_;
	Array_ vertices_;
};

#include "QGLPolygonTypes.inl"

#endif
