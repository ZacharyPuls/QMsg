#include "QGLContext.h"

#include "QLog.h"

QGLContext::QGLContext() {
    
}

QGLContext::QGLContext(HWND hWnd) : QGLContext() {
    parent_window_ = hWnd;
    gdi_device_context_ = GetDC(hWnd);

    PIXELFORMATDESCRIPTOR pixelFormatDescriptor = { 0 };
    pixelFormatDescriptor.cAlphaBits = 8;
    pixelFormatDescriptor.cBlueBits = 8;
    pixelFormatDescriptor.cColorBits = 32;
    pixelFormatDescriptor.cGreenBits = 8;
    pixelFormatDescriptor.cRedBits = 8;
    pixelFormatDescriptor.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
    pixelFormatDescriptor.iLayerType = PFD_MAIN_PLANE;
    pixelFormatDescriptor.iPixelType = PFD_TYPE_RGBA;
    pixelFormatDescriptor.nSize = sizeof(PIXELFORMATDESCRIPTOR);
    pixelFormatDescriptor.nVersion = 1;

    INT pixelFormat;

    if (!(pixelFormat = ChoosePixelFormat(gdi_device_context_, &pixelFormatDescriptor))) {
        Log->Error(L"Could not choose a suitable pixel format for device context.");
        return;
    }

    if (!SetPixelFormat(gdi_device_context_, pixelFormat, &pixelFormatDescriptor)) {
        Log->Error(L"Could not set device context pixel format.");
        return;
    }

    if (!(gl_render_context_ = wglCreateContext(gdi_device_context_))) {
        Log->Error(L"Could not create OpenGL rendering context.");
        return;
    }

    if (!wglMakeCurrent(gdi_device_context_, gl_render_context_)) {
        Log->Error(L"Could not bind OpenGL rendering context.");
    }

    if (gl3wInit() == -1) {
        Log->Error(L"Could not load OpenGL extensions. This would be caused by either an internal OpenGL driver issue, or because the machine you are running on is ancient. Falling back to super awesome mega compatibility mode.");
        compatibility_mode_enabled_ = true;
    }
    else {
        compatibility_mode_enabled_ = false;
    }
}

QGLContext::~QGLContext() {
	if (gl_render_context_) {
		// Unbind rendering context
		if (!wglMakeCurrent(NULL, NULL)) {
			Log->Error(L"Could not unbind OpenGL rendering context.");
		}
		// Release rendering context
		if (!wglDeleteContext(gl_render_context_)) {
			Log->Error(L"Could not release OpenGL rendering context.");
		}
		gl_render_context_ = NULL;
	}
	if (gdi_device_context_ && !ReleaseDC(parent_window_, gdi_device_context_)) {
		Log->Error(L"Could not release GDI device context.");
		gdi_device_context_ = NULL;
	}
}