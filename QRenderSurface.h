#ifndef QMSG_QRENDERSURFACE_H
#define QMSG_QRENDERSURFACE_H

#include "QLog.h"
#include "QVersion.h"

#include <Windows.h>

class QRenderSurface {
public:
	QRenderSurface() {}
	QRenderSurface(HWND hWnd);
	~QRenderSurface();
private:
	HWND parent_window_;
	HGLRC gl_render_context_;
	HDC gdi_device_context_;
};

#endif
