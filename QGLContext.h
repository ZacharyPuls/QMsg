#ifndef QMSG_QGLCONTEXT_H
#define QMSG_QGLCONTEXT_H

#include "QVersion.h"
#include "QGL.h"
#include "QLog.h"

#include <Windows.h>

#include <vector>

class QGLContext {
public:
    QGLContext();
	QGLContext(HWND hWnd);
	~QGLContext();

	inline void SwapBuffers() {
		::SwapBuffers(gdi_device_context_);
	}
private:
	HWND parent_window_;
	HGLRC gl_render_context_;
	HDC gdi_device_context_;
	bool compatibility_mode_enabled_;
};

#endif
