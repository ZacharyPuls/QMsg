#ifndef QMSG_QGLSHADERPROGRAM_H
#define QMSG_QGLSHADERPROGRAM_H

#include "QVersion.h"

#include "QGL.h"
#include "QGLObject.h"
#include "QGLShader.h"
#include "QGLVertexArrayObject.h"
#include "QLog.h"
#include "QString.h"

#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include <vector>

class QGLShaderProgram : IQGLObject {
public:
	QGLShaderProgram();
	QGLShaderProgram(GLchar *vertex_shader_source, GLchar *fragment_shader_source);
	~QGLShaderProgram();

	inline void Bind() {
		if (id_ == 0) {
			Log->Warn(L"Binding a QGLShader that has either encountered an error during creation, or has not been created. \
						OpenGL will simply unbind the currently bound shader, which will lead to undefined behavior.");
		}
		glUseProgram(id_);
	}

	inline void Unbind() {
		glUseProgram(0);
	}

	bool Create();

	inline void set_uniform(const GLchar *uniform_name, GLfloat *arr) {
		glUniform4fv(get_uniform_location(uniform_name), 1, arr);
	}

	inline void set_uniform(const GLchar *uniform_name, GLint value) {
		glUniform1i(get_uniform_location(uniform_name), value);
	}

	inline void set_uniform_matrix(const GLchar *uniform_name, glm::mat4x4 matrix) {
		glUniformMatrix4fv(get_uniform_location(uniform_name), 1, GL_FALSE, glm::value_ptr(matrix));
	}

	inline void set_uniform_sampler(const GLchar *uniform_sampler_name, GLint texture_index) {
		glUniform1i(get_uniform_location(uniform_sampler_name), texture_index);
	}

	inline GLint get_uniform_location(const GLchar *uniform_name) {
		return glGetUniformLocation(id_, uniform_name);
	}

	inline GLint get_attribute_location(const GLchar *attribute_name) {
		return glGetAttribLocation(id_, attribute_name);
	}
private:
	QGLShader *vertex_shader_;
	QGLShader *fragment_shader_;
	GLchar *shader_program_name_;

    bool generate_shader_program_id_();
    bool attach_shaders_and_link_program_();
    GLchar *get_program_log_(GLuint program);
};

#endif
