#ifndef QMSG_QGLVERTEX_H
#define QMSG_QGLVERTEX_H

#include "QVersion.h"

template <typename T, unsigned char N> class QGLVertex {
public:
	inline QGLVertex() {}
	inline ~QGLVertex() {}

	inline void set_points(Array_ points) {
		points_ = points;
	}

	inline Array_ get_points() {
		return points_;
	}
private:
	typedef std::array<T, N> Array_;
	Array_ points_;
};

#include "QGLVertexTypes.inl"

#endif
