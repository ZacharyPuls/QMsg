#ifndef QMSG_QGLVERTEXARRAYOBJECT_H
#define QMSG_QGLVERTEXARRAYOBJECT_H

#include "QVersion.h"

#include "QGL.h"
#include "QGLObject.h"
#include "QGLShaderProgram.h"
#include "QGLVertexBufferObject.h"
#include "QLog.h"

class QGLVertexArrayObject : IQGLObject {
public:
	QGLVertexArrayObject();
	~QGLVertexArrayObject();

	inline void Bind() {
		if (id_ == 0) {
			Log->Warn(L"Binding a QGLVertexArrayObject that has either encountered an error during creation, or has not been created. \
						OpenGL will simply unbind the currently bound vertex array object, which will lead to undefined behavior.");
		}
		glBindVertexArray(id_);
	}

	inline void Unbind() {
		// When a VAO is unbound, NEVER call a procedure that modifies VAO state, including glBindBuffer 
		// (But only for buffers other than GL_ARRAY_BUFFER. Confusing, right?).
		glBindVertexArray(0);
	}

	bool Create();
private:
};

#endif
