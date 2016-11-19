#ifndef QMSG_QGLPOLYGON_H
#define QMSG_QGLPOLYGON_H

#include "QVersion.h"

#include "QGLVertex.h"

#include <array>
#include <cassert>
#include <initializer_list>

// T = type, data type for vertices (Preferably a QGLVertex<> type, e.g. QGLVertex3f, QGLVertex3d, etc.)
// N = number, number of points per polygon
template<class T, unsigned char N> class QGLPolygon {
public:
	typedef std::array<T, N> Array_;

	inline QGLPolygon() {}
	inline QGLPolygon(Array_ vertices) : vertices_(vertices) {}
	inline QGLPolygon(std::initializer_list<T> list) {
		assert(list.size() == N);
		std::copy(list.begin(), list.end(), vertices_);
	}
	inline QGLPolygon(const QGLPolygon<T, N> &other) {
		this->vertices_ = other.vertices_;
	}
	inline ~QGLPolygon() {}

	inline void set_vertices(Array_ vertices) {
		vertices_ = vertices;
	}

	inline Array_ get_vertices() {
		return vertices_;
	}

	inline QGLPolygon &operator=(const QGLPolygon &other) {
		this->vertices_ = other.vertices_;
		return *this;
	}
private:
	Array_ vertices_;
};

#include "QGLPolygonTypes.inl"

#endif
