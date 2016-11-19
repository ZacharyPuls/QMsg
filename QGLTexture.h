#ifndef QMSG_QGLTEXTURE_H
#define QMSG_QGLTEXTURE_H

#include "QVersion.h"

#include "QGL.h"
#include "QGLObject.h"
#include "QLog.h"

#include <cstdarg>

struct QGLTextureData { 
	GLenum internal_format;
	GLsizei width;
	GLsizei height; // Not needed for 1D textures
	GLsizei depth; // Not needed for 1D or 2D textures
	GLenum data_format;
	GLenum data_type;
};

class QGLTexture : IQGLObject {
public:
	QGLTexture();
	~QGLTexture();

	inline void Bind() {
		glBindTexture(texture_type_, id_);
		glActiveTexture(GL_TEXTURE0);
	}

	inline void Unbind() {
		glBindTexture(texture_type_, 0);
	}

	bool Create();

	void SetTextureData(const GLvoid *data);
	void SetTextureData(GLint x, GLint y, GLint z, GLint width, GLint height, GLint depth, const GLvoid *data);

	inline void SetTextureOption(GLenum pname, GLint param) {
		if (id_ == 0) {
			Log->Error(L"Could not set option on QGLTexture, texture has either not been created, or failed creation.");
			return;
		}
		glBindTexture(texture_type_, id_);
		glTexParameteri(texture_type_, pname, param);
		glBindTexture(texture_type_, 0);
	}

	inline void set_texture_type(GLenum texture_type) {
		texture_type_ = texture_type;
	}

	inline void set_texture_data(QGLTextureData texture_data) {
		texture_data_ = texture_data;
	}
private:
	GLenum texture_type_ = GL_TEXTURE_2D;
	QGLTextureData texture_data_;
};

#endif
