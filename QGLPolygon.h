#ifndef QMSG_QGLPOLYGON_H
#define QMSG_QGLPOLYGON_H

#include "QVersion.h"

#include "QGLVertex.h"

#include <array>
#include <cassert>
#include <initializer_list>

// T = type, data type for vertices
// N = number, number of points per polygon
template<class T, unsigned char N> class QGLPolygon {
public:
	typedef std::array<T, N> Array_;

	inline QGLPolygon() {}
	inline QGLPolygon(Array_ vertices, Array_ texcoords) : vertices_(vertices), texcoords_(texcoords) {}

	inline QGLPolygon(const QGLPolygon<T, N> &other) {
		this->vertices_ = other.vertices_;
		this->texcoords_ = other.texcoords_;
	}
	inline ~QGLPolygon() {}

	inline void set_vertices(const Array_ &vertices) {
		vertices_ = vertices;
	}

	inline void set_texcoords(const Array_ &texcoords) {
		texcoords_ = texcoords;
	}

	inline const Array_ get_vertices() const {
		return vertices_;
	}

	inline const Array_ get_texcoords() const {
		return texcoords_;
	}

	inline QGLPolygon &operator=(const QGLPolygon &other) {
		this->vertices_ = other.vertices_;
		this->texcoords_ = other.texcoords_;
		return *this;
	}
private:
	Array_ vertices_;
	Array_ texcoords_;
};

#include "QGLPolygonTypes.inl"

#endif
