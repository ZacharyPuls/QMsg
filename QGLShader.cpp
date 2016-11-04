#include "QGLShader.h"
#include "QLog.h"

QGLShader::QGLShader() {

}

QGLShader::~QGLShader() {

}

bool QGLShader::Create() {
    if (!generate_shader_ids_()) {
        Log->Error(L"Could not generate shader ids.");
        return false;
    }
    if (vertex_shader_source_ == "" || fragment_shader_source_ == "") {
        Log->Error(L"Could not compile shaders, either the vertex or fragment shader source was blank.");
        return false;
    }
    if (!compile_shader_(vertex_shader_id_, vertex_shader_source_)) {
        Log->Error(L"Could not compile vertex shader: " + TO_QSTRING(get_shader_log_(vertex_shader_id_)));
        return false;
    }
    if (!compile_shader_(fragment_shader_id_, fragment_shader_source_)) {
        Log->Error(L"Could not compile fragment shader: " + TO_QSTRING(get_shader_log_(fragment_shader_id_)));
        return false;
    }
    if (!generate_shader_program_id_()) {
        Log->Error(L"Could not generate program id.");
        return false;
    }
    if (!attach_shaders_and_link_program_()) {
        Log->Error(L"Could not link program: " + TO_QSTRING(get_program_log_(shader_program_id_)));
        return false;
    }
    return true;
}

bool QGLShader::generate_shader_ids_() {
    vertex_shader_id_ = glCreateShader(GL_VERTEX_SHADER);
    fragment_shader_id_ = glCreateShader(GL_FRAGMENT_SHADER);
    return vertex_shader_id_ != 0 && fragment_shader_id_ != 0;
}

bool QGLShader::compile_shader_(GLuint shader, GLchar *shader_source) {
    glShaderSource(shader, 1, &shader_source, NULL);
    glCompileShader(shader);
    GLint compile_status = GL_FALSE;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &compile_status);
    return compile_status == GL_TRUE;
}

GLchar *QGLShader::get_shader_log_(GLuint shader) {
    GLint info_log_length_max = 0;
    glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &info_log_length_max);
    if (info_log_length_max > 0) {
        GLint info_log_length_actual = 0;
        GLchar *info_log = new GLchar[info_log_length_max];
        glGetShaderInfoLog(shader, info_log_length_max, &info_log_length_actual, info_log);
        if (info_log_length_actual > 0) {
            return info_log;
        }
        if (info_log) {
            delete info_log;
        }
    }
    return "";
}

bool QGLShader::generate_shader_program_id_() {
    shader_program_id_ = glCreateProgram();
    return shader_program_id_ != 0;
}

bool QGLShader::attach_shaders_and_link_program_() {
    glAttachShader(shader_program_id_, vertex_shader_id_);
    glAttachShader(shader_program_id_, fragment_shader_id_);
    glLinkProgram(shader_program_id_);
    GLint link_status = GL_FALSE;
    glGetProgramiv(shader_program_id_, GL_LINK_STATUS, &link_status);
    return link_status == GL_TRUE;
}

GLchar * QGLShader::get_program_log_(GLuint program) {
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
