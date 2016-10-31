#ifndef QMSG_QGLSHADER_H
#define QMSG_QGLSHADER_H

#include "QVersion.h"
#include "QString.h"

class QGLShader {
public:
	QGLShader();
	~QGLShader();
private:
	QString vertex_shader_name_;
	QString vertex_shader_data_;
	QString fragment_shader_name_;
	QString fragment_shader_data_;
	QString shader_program_name_;
};

#endif
