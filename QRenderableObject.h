#ifndef QMSG_QRENDERABLEOBJECT_H
#define QMSG_QRENDERABLEOBJECT_H

#include "QVersion.h"

#include "QGLMesh2D.h"
#include "QGLShaderProgram.h"
#include "QGLTexture.h"

class QRenderableObject {
public:
	QRenderableObject();
	~QRenderableObject();

	inline void add_triangle(const QGLTriangle2D &triangle) {
		mesh_->add_triangle(triangle);
	}

	inline const QGLMesh2D *get_mesh() const {
		return mesh_;
	}

	inline void set_mesh(const QGLMesh2D mesh) {
		mesh_ = new QGLMesh2D(mesh);
	}
protected:
	QGLMesh2D *mesh_;
private:
	QGLTexture *texture_;
};

#endif
