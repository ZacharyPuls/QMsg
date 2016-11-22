#ifndef QMSG_QWINDOW_H
#define QMSG_QWINDOW_H

#include "QVersion.h"

#include "QRenderSurface.h"
#include "QString.h"

#include <Windows.h>

#include <string>

#define QMSG_QWINDOW_EXSTYLE WS_EX_ACCEPTFILES | WS_EX_APPWINDOW
#define QMSG_QWINDOW_STYLE WS_OVERLAPPEDWINDOW | WS_VSCROLL

// This is an address offset into HWND userdata where we store the address of 'this' (QWindow)
// See GWLP_USERDATA and GetWindowLongPtr
#define QMSG_GWLP_QWINDOW_PTR 9999

class QWindow {
public:
	QWindow() : name_(L""), title_(L""), width_(0), height_(0), x_(0), y_(0) {}
	QWindow(HINSTANCE hInstance, QString name, QString title, int width, int height, int x, int y);
	~QWindow();
	bool Create();
private:
	QString name_;
	QString title_;
	int width_;
	int height_;
	int x_;
	int y_;

	HINSTANCE instance_;
	HWND window_handle_;
	WNDCLASSEX window_class_;
	QRenderSurface *render_surface_ = nullptr;

	bool key_states_[256] = { 0 };
	static LRESULT CALLBACK internal_message_handler_(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

	// Message/Event callbacks
	LRESULT CALLBACK on_window_size_(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	LRESULT CALLBACK on_window_draw_(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

	// Utility methods
	inline static QWindow *get_window_from_user_data_(HWND hWnd) {
		return reinterpret_cast<QWindow *>(GetWindowLongPtr(hWnd, GWLP_USERDATA));
	}
};

#endif