#include "QGLVertexArrayObject.h"

QGLVertexArrayObject::QGLVertexArrayObject() {

}

QGLVertexArrayObject::~QGLVertexArrayObject() {

}

bool QGLVertexArrayObject::Create() {
	glGenVertexArrays(1, &id_);
	if (id_ == 0) {
		Log->Error(L"Could not generate id for vertex array object.");
		return false;
	}
	return true;
}