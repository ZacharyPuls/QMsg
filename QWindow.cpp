#include "QWindow.h"

#include "QGLFont.h"
#include "QGLMesh2D.h"
#include "QGLPolygon.h"
#include "QGLVertex.h"
#include "QLog.h"
#include "QRenderSurface.h"

#include "glm/glm.hpp"
#include "glm/ext.hpp"

#include <array>
#include <iostream>

#pragma comment(lib, "user32.lib")

QWindow::QWindow(HINSTANCE hInstance, QString name, QString title, int width, int height, int x, int y) : instance_(hInstance), name_(name), title_(title), width_(width), height_(height), x_(x), y_(y) {

}

QWindow::~QWindow() {
    if (render_surface_ != nullptr) {
        delete render_surface_;
    }
}

bool QWindow::Create() {
	Log->Info(L"Creating QWindow.");
	window_class_ = {};
	window_class_.cbClsExtra = 0;
	window_class_.cbSize = sizeof(WNDCLASSEX);
	window_class_.cbWndExtra = 0;
	window_class_.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	window_class_.hCursor = LoadCursor(NULL, IDC_ARROW);
	window_class_.hIcon = LoadIcon(instance_, (LPCWSTR)MAKEINTRESOURCE(IDI_WINLOGO));
	window_class_.hIconSm = LoadIcon(instance_, (LPCWSTR)MAKEINTRESOURCE(IDI_WINLOGO));
	window_class_.hInstance = instance_;
	window_class_.lpfnWndProc = &this->internal_message_handler_;
	window_class_.lpszClassName = name_.c_str();
	window_class_.lpszMenuName = NULL;
	window_class_.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;

	if (!RegisterClassEx(&window_class_)) {
		Log->Error(L"Could not register window class.");
		return false;
	}

	if ((window_handle_ = CreateWindowEx(QMSG_QWINDOW_EXSTYLE, name_.c_str(), title_.c_str(), QMSG_QWINDOW_STYLE, x_, y_, width_, height_, NULL, NULL, instance_, NULL)) == NULL) {
		Log->Error(L"Could not create window handle.");
		return false;
	}

	Log->Info(L"Creating QRenderSurface");

	render_surface_ = new QRenderSurface(window_handle_);

	Log->Info(L"Successfully created QRenderSurface.");

	// Store a pointer to this QWindow object in USERDATA, so internal_message_handler_ (a static function) is able to access it and mutate state.
	SetWindowLongPtr(window_handle_, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(this));
	
	ShowWindow(window_handle_, SW_SHOW);
	UpdateWindow(window_handle_);

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	QGLFont ubuntu_mono;

	if (!ubuntu_mono.Load(L"fonts/Ubuntu-R.ttf", 16)) {
		Log->Error(L"Could not load Ubuntu Mono Regular font.");
	}

	QGLMesh2D text_mesh;
	text_mesh.add_triangles(ubuntu_mono.RenderString(L"Test string.", 100.0f, 100.0f, 1.0f));
	
	QRenderableObject text_object;
	text_object.set_mesh(text_mesh);

	render_surface_->add_object(text_object);

	MSG msg;
	bool running = true;

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDisable(GL_DEPTH_TEST);

	while (running) {
		int ret = GetMessage(&msg, window_handle_, 0, 0);
		if (ret == -1 || ret == 0) { // Error, or WM_QUIT
			running = false;
			continue;
		}
		else {
			TranslateMessage(&msg);
			DispatchMessage(&msg);	
		}	
		render_surface_->Render();
	}

	return true;
}

LRESULT CALLBACK QWindow::internal_message_handler_(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	// We can't retrieve this value here if some window messages (WM_NCCREATE, etc.) that are sent before window creation need to be handled.
	QWindow *window = get_window_from_user_data_(hWnd);

	switch (uMsg) {
	case WM_CLOSE:
		DestroyWindow(window->window_handle_);
		break;
	case WM_DESTROY:
		PostQuitMessage(EXIT_SUCCESS);
		break;
	case WM_KEYDOWN:
		window->key_states_[wParam] = true;
		break;
	case WM_KEYUP:
		window->key_states_[wParam] = false;
		break;
	case WM_SIZE:
		return window->on_window_size_(hWnd, uMsg, wParam, lParam);
	case WM_PAINT:
		return window->on_window_draw_(hWnd, uMsg, wParam, lParam);
	default:
		return DefWindowProc(hWnd, uMsg, wParam, lParam);
	}
	return 0;
}

LRESULT CALLBACK QWindow::on_window_size_(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	this->width_ = LOWORD(lParam);
	this->height_ = HIWORD(lParam);
	render_surface_->Resize(this->width_, this->height_);
	return 0;
}

LRESULT CALLBACK QWindow::on_window_draw_(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	// render_surface_->Render();
	return 0;
}
