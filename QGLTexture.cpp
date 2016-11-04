#include "QGLTexture.h"

#include "QLog.h"

QGLTexture::QGLTexture() {

}

QGLTexture::~QGLTexture() {

}

bool QGLTexture::Create() {
	glGenTextures(1, &id_);
	if (id_ == 0) {
		Log->Error(L"Could not generate texture ID.");
		return false;
	}
	Bind();
	// TODO: Allow for mipmap generation, as of right now, everything is done at the 0th mipmap level.
	switch (texture_type_) {
	case GL_TEXTURE_1D:
		glTexImage1D(texture_type_, 0, texture_data_.internal_format, texture_data_.width, 0, texture_data_.data_format, texture_data_.data_type, texture_data_.data);
		break;
	case GL_TEXTURE_2D:
		glTexImage2D(texture_type_, 0, texture_data_.internal_format, texture_data_.width, texture_data_.height, 0, texture_data_.data_format, texture_data_.data_type, texture_data_.data);
		break;
	case GL_TEXTURE_3D:
		glTexImage3D(texture_type_, 0, texture_data_.internal_format, texture_data_.width, texture_data_.height, texture_data_.depth, 0, texture_data_.data_format, texture_data_.data_type, texture_data_.data);
		break;
	default:
		Log->Info(L"You passed in an unsupported texture format to QGLTexture::Create(). No data was written to the OpenGL texture object.");
		break;
	}

	Unbind();
}
