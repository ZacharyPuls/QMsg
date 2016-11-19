#ifndef QMSG_QVERTEXBUFFER_H
#define QMSG_QVERTEXBUFFER_H

#include "QVersion.h"

#include "QGLMesh2D.h"
#include "QGLVertexArrayObject.h"
#include "QGLVertexBufferObject.h"

#include <vector>

class QVertexBuffer {
public:
	inline QVertexBuffer::QVertexBuffer() {
		vertex_buffer_object_ = new QGLVertexBufferObject();
		vertex_array_object_ = new QGLVertexArrayObject();
	}

	inline QVertexBuffer::~QVertexBuffer() {
		if (vertex_buffer_object_ != nullptr) {
			delete vertex_buffer_object_;
		}

		if (vertex_array_object_ != nullptr) {
			delete vertex_array_object_;
		}
	}
	
	inline void Bind() {
		vertex_buffer_object_->Bind();
		vertex_buffer_object_->UpdateBufferData(sizeof(float) * raw_vertex_data_.size(), &raw_vertex_data_[0]);
		vertex_array_object_->Bind();
	}

	inline void Reset() {
		vertex_buffer_object_->UpdateBufferData(0, (void *)0);
	}
	
	inline void AddMesh(QGLMesh2D *mesh) {
		raw_vertex_data_.emplace_back(mesh->collect_vertex_data());
	}
private:
	QGLVertexArrayObject *vertex_array_object_;
	QGLVertexBufferObject *vertex_buffer_object_;

	std::vector<float> raw_vertex_data_;
};

#endif
