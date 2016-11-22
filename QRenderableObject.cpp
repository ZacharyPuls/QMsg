#include "QRenderableObject.h"

#include "QVertexBuffer.h"
#include "QVertexBufferPool.h"

QRenderableObject::QRenderableObject() {
	mesh_ = new QGLMesh2D();
}

QRenderableObject::~QRenderableObject() {
	if (mesh_ != nullptr) {
		delete mesh_;
	}
}
