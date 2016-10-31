#ifndef QMSG_QGLCONTEXT_H
#define QMSG_QGLCONTEXT_H

#include "QVersion.h"
#include "QLog.h"

#include "GL/glcorearb.h"

#include <Windows.h>

#include <vector>

#include "QGLExtensions.inl"

class QGLContext {
public:
	QGLContext() {
		if (extensions_available_ == nullptr) {
			glGetString = (PFNGLGETSTRINGPROC)wglGetProcAddress("glGetString");
			if (!glGetString) {
				Log->Error(L"Could not load glGetString extension. This would be caused by either an internal OpenGL driver issue, or because the machine you are running on is ancient. Falling back to super awesome mega compatibility mode.");
				compatibility_ = true;
			}
			else {
				extensions_available_ = glGetString(GL_EXTENSIONS);
				compatibility_ = false;
			}
		}
	}
	QGLContext(HWND hWnd);
	~QGLContext();
private:
	HWND parent_window_;
	HGLRC gl_render_context_;
	HDC gdi_device_context_;
	std::vector<GLenum> extensions_;

	static PFNGLGETSTRINGPROC glGetString;
	static const GLubyte *extensions_available_;
	static bool compatibility_;

	inline void request_gl_extension_(GLenum extension) {
		this->extensions_.push_back(extension);
	}
	bool load_extensions_();
	bool load_extension_(GLenum extension);
};

#endif
