#include "QGLVertexBufferObject.h"

QGLVertexBufferObject::QGLVertexBufferObject() 
{
}

QGLVertexBufferObject::~QGLVertexBufferObject() {

}

bool QGLVertexBufferObject::Create() {
	glGenBuffers(1, &id_);
	if (id_ == 0) {
		Log->Error(L"Could not generate vertex buffer object id.");
		return false;
	}
	return true;
}

void QGLVertexBufferObject::UpdateBufferData(const GLvoid * data) {
	Bind();
	glBufferData(GL_ARRAY_BUFFER, sizeof(data), data, GL_DYNAMIC_DRAW);
	Unbind();
}
