#ifndef QMSG_QVERTEXBUFFERPOOL_H
#define QMSG_QVERTEXBUFFERPOOL_H

#include "QVersion.h"

#include "QVertexBuffer.h""

#include <list>

class QVertexBufferPool {
public:
	QVertexBufferPool();
	~QVertexBufferPool();

	static QVertexBufferPool &GetInstance() {
		static QVertexBufferPool instance;
		return instance;
	}

	QVertexBuffer *Get() {
		if (pool_.empty()) {
			return new QVertexBuffer();
		}

		QVertexBuffer *vertex_buffer = pool_.front();
		pool_.pop_front();
		return vertex_buffer;
	}

	void Release(QVertexBuffer *vertex_buffer) {
		vertex_buffer->Reset();
		pool_.push_back(vertex_buffer);
	}
private:
	inline QVertexBufferPool() {

	}

	inline ~QVertexBufferPool() {

	}

	std::list<QVertexBuffer *> pool_;
	
};

#endif
