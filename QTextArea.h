#ifndef QMSG_QTEXTAREA_H
#define QMSG_QTEXTAREA_H

#include "QVersion.h"

#include "QGLFont.h"
#include "QLog.h"
#include "QRenderableObject.h"
#include "QString.h"

#define CURSOR_DESELECTED -1

class QTextArea : public QRenderableObject {
public:
	inline QTextArea() 
		: QTextArea(L"") {

	}

	inline QTextArea(const QString &text) 
		: text_(text), cursor_start_(CURSOR_DESELECTED), cursor_end_(CURSOR_DESELECTED) {

	}

	inline ~QTextArea() {

	}

	inline void begin_select(int cursor) {
		cursor_start_ = cursor;
		cursor_end_ = cursor_start_ + 1;
	}

	inline void select(int cursor) {
		cursor_end_ = cursor;
	}

	inline void set_position(int x, int y) {
		x_ = x;
		y_ = y;
	}

	inline void set_size(int width, int height) {
		width_ = width;
		height_ = height;
	}

	inline void set_font(QGLFont *font) {
		font_ = font;
	}

	inline void set_text(const QString &text) {
		text_ = text;
	}

	inline void type(const QString &text) {
		if (cursor_start_ == CURSOR_DESELECTED) {
			// TextArea is inactive.
			Log->Info(L"Attempted to type in a QTextArea that was deselected.");
		}
		else if (cursor_start_ != CURSOR_DESELECTED && cursor_end_ == CURSOR_DESELECTED) {
			// TextArea is active, cursor is active, but no text is selected.
			text_.insert(cursor_start_, text);
		}
		else if (cursor_start_ != CURSOR_DESELECTED && cursor_end_ != CURSOR_DESELECTED) {
			// TextArea is active, cursor is active, and a section of text is selected.
			text_.replace(cursor_start_, cursor_end_, text);
		}
	}

	inline void Render() {
		mesh_->clear();
		mesh_->add_triangles(font_->RenderString(text_, x_, y_, 1.0f));
	}
private:
	QString text_;
	QGLFont *font_;
	int cursor_start_;
	int cursor_end_;
	int x_;
	int y_;
	int width_;
	int height_;
};

#endif
