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

	inline void add_vertices(float *vertices) {
		
	}

	inline QGLMesh2D get_mesh() const {
		return mesh_;
	}

	inline void set_shader(QGLShaderProgram *shader) {
		shader_ = shader;
	}

private:
	QGLMesh2D mesh_;
	QGLShaderProgram *shader_;
	QGLTexture *texture_;
};

#endif
