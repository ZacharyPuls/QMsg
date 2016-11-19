#ifndef QMSG_QGLFONT_H
#define QMSG_QGLFONT_H

#include "QVersion.h"

#include "QFreeType.h"
#include "QGL.h"
#include "QGLTexture.h"
#include "QGLPolygon.h"
#include "QString.h"

#include <array>
#include <map>

struct QGLCharacter {
	GLfloat xoffset;
	QGLVertex2i advance;
	QGLVertex2ui size;
	QGLVertex2i origin;
};

class QGLFont {
public:
    QGLFont();
    ~QGLFont();
	bool Load(QString font_path, int font_size);
	QGLTriangle2D *RenderString(QString string, GLfloat x, GLfloat y, GLfloat scale);
private:
	QGLTexture *texture_;
    std::map<GLchar, QGLCharacter> characters_;
	FT_Face font_face_;

	std::pair<GLint, GLint> calculate_font_atlas_size_(FT_Face font_face);
};


#endif
