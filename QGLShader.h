#ifndef QMSG_QGLSHADER_H
#define QMSG_QGLSHADER_H

#include "QVersion.h"
#include "QGL.h"
#include "QString.h"

class QGLShader {
public:
	QGLShader();
    QGLShader(GLchar *vertex_shader_source, GLchar *fragment_shader_source) : QGLShader() {
        vertex_shader_source_ = vertex_shader_source;
        fragment_shader_source_ = fragment_shader_source;
    }
	~QGLShader();
	
	bool Create();
	inline void Bind() {
        glUseProgram(shader_program_id_);
	}

	inline void set_vertex_shader_source(GLchar *source) {
		vertex_shader_source_ = source;
	}
	inline void set_fragment_shader_source(GLchar *source) {
		fragment_shader_source_ = source;
	}
    inline void set_uniform(const GLchar *uniform_name, GLfloat *array) {
        glUniform4fv(glGetUniformLocation(shader_program_id_, uniform_name), 1, array);
    }
private:
	GLuint vertex_shader_id_;
	GLchar *vertex_shader_name_;
	GLchar *vertex_shader_source_;
	GLuint fragment_shader_id_;
	GLchar *fragment_shader_name_;
	GLchar *fragment_shader_source_;
	GLchar *shader_program_name_;
	GLuint shader_program_id_;

    bool generate_shader_ids_();
    bool compile_shader_(GLuint shader, GLchar *shader_source);
    GLchar *get_shader_log_(GLuint shader);
    bool attach_shaders_and_link_program_();
    GLchar *get_program_log_(GLuint program);
};

#endif
