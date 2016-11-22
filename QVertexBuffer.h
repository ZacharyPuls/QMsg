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
		vertex_buffer_object_->Create();
		texcoord_buffer_object_ = new QGLVertexBufferObject();
		texcoord_buffer_object_->Create();
		vertex_array_object_ = new QGLVertexArrayObject();
		vertex_array_object_->Create();
	}

	inline QVertexBuffer::~QVertexBuffer() {
		if (vertex_buffer_object_ != nullptr) {
			delete vertex_buffer_object_;
		}

		if (texcoord_buffer_object_ != nullptr) {
			delete texcoord_buffer_object_;
		}

		if (vertex_array_object_ != nullptr) {
			delete vertex_array_object_;
		}
	}
	
	inline void Bind() {
		vertex_buffer_object_->Bind();
		if (!raw_vertex_data_.empty()) {
			vertex_buffer_object_->UpdateBufferData(sizeof(GLfloat) * raw_vertex_data_.size(), &raw_vertex_data_[0]);
		}
		texcoord_buffer_object_->Bind();
		if (!raw_texcoord_data_.empty()) {
			texcoord_buffer_object_->UpdateBufferData(sizeof(GLfloat) * raw_texcoord_data_.size(), &raw_texcoord_data_[0]);
		}
		vertex_array_object_->Bind();
	}


	inline void Reset() {
		vertex_buffer_object_->UpdateBufferData(0, (void *)0);
		texcoord_buffer_object_->UpdateBufferData(0, (void *)0);
	}
	
	inline void AddMesh(const QGLMesh2D *mesh) {
		std::vector<GLfloat> mesh_vertex_data = mesh->collect_vertex_data();
		raw_vertex_data_.insert(raw_vertex_data_.end(), mesh_vertex_data.begin(), mesh_vertex_data.end());
		std::vector<GLfloat> mesh_texcoord_data = mesh->collect_texcoord_data();
		raw_texcoord_data_.insert(raw_texcoord_data_.end(), mesh_texcoord_data.begin(), mesh_texcoord_data.end());
	}

	inline const int get_num_vertices() const {
		return raw_vertex_data_.size();
	}
private:
	QGLVertexArrayObject *vertex_array_object_ = nullptr;
	QGLVertexBufferObject *vertex_buffer_object_ = nullptr;
	QGLVertexBufferObject *texcoord_buffer_object_ = nullptr;

	std::vector<GLfloat> raw_vertex_data_;
	std::vector<GLfloat> raw_texcoord_data_;
};

#endif
