#ifndef QMSG_QRENDERSURFACE_H
#define QMSG_QRENDERSURFACE_H

#include "QVersion.h"

#include "QGLContext.h"
#include "QGLShader.h"
#include "QLog.h"

#include <Windows.h>

#include <array>

class QRenderSurface {
public:
	QRenderSurface() {}
	QRenderSurface(HWND hWnd);
	~QRenderSurface();

    inline void Resize(int width, int height) {
        width_ = width;
        height_ = height;
        projection_matrix_ = project_ortho_((float)width_, (float)height_);
        gl_shader_->set_uniform("projection", projection_matrix_.data());
    }
private:
    int width_;
    int height_;
	QGLContext *gl_context_;
    QGLShader *gl_shader_;
    std::array<float, 16> projection_matrix_;

    std::array<float, 16> project_ortho_(float width, float height);
};

#endif
