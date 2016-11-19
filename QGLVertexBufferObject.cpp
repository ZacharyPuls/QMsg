#include "QGLVertexBufferObject.h"

#include "QLog.h"
#include "QString.h"

QGLVertexBufferObject::QGLVertexBufferObject() 
{
}

QGLVertexBufferObject::~QGLVertexBufferObject() {
	glDeleteBuffers(1, &id_);
}

bool QGLVertexBufferObject::Create() {
	glGenBuffers(1, &id_);
	// Log->Info(L"VBO created with id " + ITO_QSTRING(id_));
	if (id_ == 0) {
		Log->Error(L"Could not generate vertex buffer object id.");
		return false;
	}
	return true;
}

void QGLVertexBufferObject::UpdateBufferData(const GLsizei size, const GLvoid *data) {
	// Log->Info(L"Updating VBO data with size " + ITO_QSTRING(sizeof(data)) + L" bytes, for VBO with id " + ITO_QSTRING(id_));
	glBufferData(GL_ARRAY_BUFFER, size, data, GL_DYNAMIC_DRAW);
}
