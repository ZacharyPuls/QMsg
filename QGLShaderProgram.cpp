#include "QGLShaderProgram.h"

#include "QGLShader.h"
#include "QLog.h"

QGLShaderProgram::QGLShaderProgram() {

}

QGLShaderProgram::QGLShaderProgram(GLchar *vertex_shader_source, GLchar *fragment_shader_source) : QGLShaderProgram() {
	vertex_shader_ = new QGLShader(GL_VERTEX_SHADER, vertex_shader_source);
	fragment_shader_ = new QGLShader(GL_FRAGMENT_SHADER, fragment_shader_source);
}

QGLShaderProgram::~QGLShaderProgram() {
	glDeleteProgram(id_);

	if (vertex_shader_) {
		delete vertex_shader_;
	}

	if (fragment_shader_) {
		delete fragment_shader_;
	}
}

bool QGLShaderProgram::Create() {
    if (vertex_shader_ == nullptr || fragment_shader_ == nullptr) {
        Log->Error(L"Could not compile shaders, either the vertex or fragment shader was missing. Did you forget to call QGLShaderProgram(GLchar *, GLchar *)?");
        return false;
    }

	if (!vertex_shader_->Create() || !fragment_shader_->Create()) {
		return false;
	}

    if (!generate_shader_program_id_()) {
        Log->Error(L"Could not generate program id.");
        return false;
    }

    if (!attach_shaders_and_link_program_()) {
        Log->Error(L"Could not link program: " + TO_QSTRING(get_program_log_(id_)));
        return false;
    }

    return true;
}

bool QGLShaderProgram::generate_shader_program_id_() {
    id_ = glCreateProgram();
    return id_ != 0;
}

bool QGLShaderProgram::attach_shaders_and_link_program_() {
    glAttachShader(id_, vertex_shader_->get_id());
    glAttachShader(id_, fragment_shader_->get_id());

    glLinkProgram(id_);

    GLint link_status = GL_FALSE;
    glGetProgramiv(id_, GL_LINK_STATUS, &link_status);

    return link_status == GL_TRUE;
}

GLchar *QGLShaderProgram::get_program_log_(GLuint program) {
    GLint info_log_length_max = 0;
    glGetProgramiv(program, GL_INFO_LOG_LENGTH, &info_log_length_max);

    if (info_log_length_max > 0) {
        GLint info_log_length_actual = 0;
        GLchar *info_log = new GLchar[info_log_length_max];
        glGetProgramInfoLog(program, info_log_length_max, &info_log_length_actual, info_log);
        if (info_log_length_actual > 0) {
            return info_log;
        }
        if (info_log) {
            delete info_log;
        }
    }

    return "";
}
