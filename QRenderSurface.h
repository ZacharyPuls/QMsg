#ifndef QMSG_QRENDERSURFACE_H
#define QMSG_QRENDERSURFACE_H

#include "QVersion.h"

#include "QGL.h"
#include "QGLContext.h"
#include "QGLShaderProgram.h"
#include "QGLMesh2D.h"
#include "QLog.h"
#include "QRenderableObject.h"
#include "QVertexBuffer.h"

#include <Windows.h>

#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include <array>
#include <vector>

class QRenderSurface {
public:
	QRenderSurface() {}
	QRenderSurface(HWND hWnd);
	~QRenderSurface();

    inline void Resize(int width, int height) {
        width_ = width;
        height_ = height;
        projection_matrix_ = glm::ortho(0.0f, (float)width_, 0.0f, (float)height_);
        gl_shader_->set_uniform_matrix("projection", projection_matrix_);
		glViewport(0, 0, width_, height_);
    }

	void Render();

	inline void add_object(const QRenderableObject &object) {
		objects_.push_back(object);
	}

	inline void set_shader(GLchar *vertex_shader_source, GLchar *fragment_shader_source) {
		if (gl_shader_ != nullptr) {
			delete gl_shader_;
		}
		gl_shader_ = new QGLShaderProgram(vertex_shader_source, fragment_shader_source);
		gl_shader_->Create();
	}
private:
    int width_;
    int height_;
	QGLContext *gl_context_ = nullptr;
    QGLShaderProgram *gl_shader_ = nullptr;
    glm::mat4x4 projection_matrix_;
	std::vector<QRenderableObject> objects_;
	QVertexBuffer *vertex_buffer_ = nullptr;

    std::array<float, 16> project_ortho_(float width, float height);
};

#endif
