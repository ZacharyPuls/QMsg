#include "QGLTexture.h"

#include "QLog.h"
#include "QString.h"

QGLTexture::QGLTexture() {

}

QGLTexture::~QGLTexture() {
	glDeleteTextures(1, &id_);
}

bool QGLTexture::Create() {
	glGenTextures(1, &id_);
	// Log->Info(L"Creating texture with id " + ITO_QSTRING(id_));
	if (id_ == 0) {
		Log->Error(L"Could not generate texture ID.");
		return false;
	}

	SetTextureData(NULL);
	
	return true;
}

// TODO: Allow for mipmap generation, as of right now, everything is done at the 0th mipmap level. 
// This has to be done manually, as automatic mipmap generation has been deprecated as of OpenGL 4.5. Not a big deal, since you should have already been doing it this way.
void QGLTexture::SetTextureData(const GLvoid *data) {
	Bind();
	switch (texture_type_) {
	case GL_TEXTURE_1D:
		glTexImage1D(texture_type_, 0, texture_data_.internal_format, texture_data_.width, 0, texture_data_.data_format, texture_data_.data_type, data);
		break;
	case GL_TEXTURE_2D:
		glTexImage2D(texture_type_, 0, texture_data_.internal_format, texture_data_.width, texture_data_.height, 0, texture_data_.data_format, texture_data_.data_type, data);
		break;
	case GL_TEXTURE_3D:
		glTexImage3D(texture_type_, 0, texture_data_.internal_format, texture_data_.width, texture_data_.height, texture_data_.depth, 0, texture_data_.data_format, texture_data_.data_type, data);
		break;
	default:
		Log->Info(L"You passed in an unsupported texture format to QGLTexture::SetTextureData(). No data was written to the OpenGL texture object.");
		break;
	}
	Unbind();
}

void QGLTexture::SetTextureData(GLint x, GLint y, GLint z, GLint width, GLint height, GLint depth, const GLvoid *data) {
	Bind();
	switch (texture_type_) {
	case GL_TEXTURE_1D:
		glTexSubImage1D(texture_type_, 0, x, width, texture_data_.data_format, texture_data_.data_type, data);
		break;
	case GL_TEXTURE_2D:
		glTexSubImage2D(texture_type_, 0, x, y, width, height, texture_data_.data_format, texture_data_.data_type, data);
		break;
	case GL_TEXTURE_3D:
		glTexSubImage3D(texture_type_, 0, x, y, z, width, height, depth, texture_data_.data_format, texture_data_.data_type, data);
		break;
	default:
		Log->Info(L"You passed in an unsupported texture format to QGLTexture::SetTextureData(). No data was written to the OpenGL texture object.");
		break;
	}
	Unbind();
}