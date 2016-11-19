#ifndef QMSG_QGLVERTEXBUFFEROBJECT_H
#define QMSG_QGLVERTEXBUFFEROBJECT_H

#include "QVersion.h"

#include "QGL.h"
#include "QGLMesh2D.h"
#include "QGLObject.h"
#include "QLog.h"

class QGLVertexBufferObject : IQGLObject {
public:
	QGLVertexBufferObject();
	~QGLVertexBufferObject();

	inline void Bind() {
		if (id_ == 0) {
			Log->Warn(L"Binding a QGLVertexBufferObject that has either encountered an error during creation, or has not been created. \
						OpenGL will simply unbind the currently bound vertex buffer object, which will lead to undefined behavior.");
		}
		glBindBuffer(GL_ARRAY_BUFFER, id_);
		bound_ = true;
	}

	inline void Unbind() {
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		bound_ = false;
	}

	bool Create();

	inline void set_buffer_size(GLsizei buffer_size) {
		buffer_size_ = buffer_size;
	}

	void UpdateBufferData(const GLsizei size, const GLvoid *data);

private:
	GLsizei buffer_size_;
};

#endif
