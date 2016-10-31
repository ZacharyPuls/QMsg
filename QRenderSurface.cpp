#include "QRenderSurface.h"

#include <iostream>

#pragma comment(lib, "opengl32.lib")

QRenderSurface::QRenderSurface(HWND hWnd) : gl_context_(hWnd) {
	
}

QRenderSurface::~QRenderSurface() {
	
}


