#ifndef QMSG_QMATRIX_H
#define QMSG_QMATRIX_H

#include "QVersion.h"

#include <array>
#include <initializer_list>

class QMatrix {
public:
	inline QMatrix() {
		values_.fill(0.0f);
		values_[0] = 1.0f;
		values_[5] = 1.0f;
		values_[10] = 1.0f;
		values_[15] = 1.0f;
	}
	inline QMatrix(std::initializer_list<float> values) {
		std::copy(values.begin(), values.end(), values_);
	}
	inline ~QMatrix() {

	}

	inline const float *ptr() const {
		return values_.data();
	}

	inline static const QMatrix &Ortho(float left, float right, float top, float bottom) {
		return {
			2.0f / (right - left), 0.0f, 0.0f, 0.0f,
			0.0f, 2.0f / (top - bottom), 0.0f, 0.0f,
			0.0f, 0.0f, -1.0f, 0.0f,
			-(right + left) / (right - left), -(top + bottom) / (top - bottom), 0.0f, 1.0f
		};		
	}
private:
	std::array<float, 16> values_;
};

#endif
