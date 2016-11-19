#ifndef QMSG_QGLSHADER_H
#define QMSG_QGLSHADER_H

#include "QVersion.h"

#include "QGL.h"
#include "QGLObject.h"

class QGLShader : public IQGLObject {
public:
	QGLShader();
	QGLShader(GLenum type, GLchar *source);
	~QGLShader();

	inline void Bind() {
		// Unused
	}

	inline void Unbind() {
		// Unused
	}

	bool Create();
private:
	GLenum type_;
	GLchar *source_;

	bool compile_();
	GLchar *get_log_();
};

#endif
