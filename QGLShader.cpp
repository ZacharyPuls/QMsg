#include "QGLShader.h"

#include "QLog.h"

QGLShader::QGLShader() {

}

QGLShader::QGLShader(GLenum type, GLchar *source) : type_(type), source_(source) {

}

QGLShader::~QGLShader() {

}

bool QGLShader::Create() {
	if (id_ != 0) {
		glDeleteShader(id_);
	}
	if ((id_ = glCreateShader(type_)) == 0) {
		Log->Error(L"Could not generate shader id.");
		return false;
	}
	if (source_ == "") {
		Log->Error(L"Could not compile shader, shader source is blank.");
		return false;
	}
	if (!compile_()) {
		Log->Error(L"Could not compile shader: " + TO_QSTRING(get_log_()));
		return false;
	}
	return true;
}

bool QGLShader::compile_() {
	glShaderSource(id_, 1, &source_, NULL);
	glCompileShader(id_);
	GLint compile_status = GL_FALSE;
	glGetShaderiv(id_, GL_COMPILE_STATUS, &compile_status);
	return compile_status == GL_TRUE;
}

GLchar *QGLShader::get_log_() {
	GLint info_log_length_max = 0;
	glGetShaderiv(id_, GL_INFO_LOG_LENGTH, &info_log_length_max);
	if (info_log_length_max > 0) {
		GLint info_log_length_actual = 0;
		GLchar *info_log = new GLchar[info_log_length_max];
		glGetShaderInfoLog(id_, info_log_length_max, &info_log_length_actual, info_log);
		if (info_log_length_actual > 0) {
			return info_log;
		}
		if (info_log) {
			delete info_log;
		}
	}
	return "";
}

