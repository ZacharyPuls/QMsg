#ifndef QMSG_QGLVERTEX_H
#define QMSG_QGLVERTEX_H

#include "QVersion.h"

#include "QGL.h"

#include <array>
#include <cassert>
#include <initializer_list>

template <typename T, unsigned char N> class QGLVertex {
public:
	typedef std::array<T, N> Array_;

	inline QGLVertex() {}
	inline QGLVertex(Array_ points) : points_(points) {}
	inline QGLVertex(std::initializer_list<T> list) {
		assert(list.size() == N);
		std::copy(list.begin(), list.end(), points_);
	}
	inline ~QGLVertex() {}

	inline void set_points(Array_ points) {
		points_ = points;
	}

	inline Array_ get_points() {
		return points_;
	}

	inline const T &operator[](const int i) const {
		assert(i < N);
		return points_[i];
	}
private:
	Array_ points_;
};

#include "QGLVertexTypes.inl"

#endif
