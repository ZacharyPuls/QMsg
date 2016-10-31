#ifndef QMSG_QRENDERSURFACE_H
#define QMSG_QRENDERSURFACE_H

#include "QVersion.h"

#include "QGLContext.h"
#include "QLog.h"

#include <Windows.h>

class QRenderSurface {
public:
	QRenderSurface() {}
	QRenderSurface(HWND hWnd);
	~QRenderSurface();
private:
	QGLContext gl_context_;
};

#endif
