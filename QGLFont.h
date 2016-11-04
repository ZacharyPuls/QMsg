#ifndef QMSG_QGLFONT_H
#define QMSG_QGLFONT_H

#include "QVersion.h"

#include "QFreeType.h"
#include "QGL.h"
#include "QGLTexture.h"

#include <array>
#include <map>

struct QGLCharacter {
    QGLTexture texture;
    std::array<int, 4> attributes; // Size and Bearing
    GLuint advance;
};

class QGLFont {
public:
    QGLFont();
    ~QGLFont();
	bool Load(QString font_path, int font_size);
private:
    std::map<GLchar, QGLCharacter> characters_;
	FT_Face font_face_;
	GLuint texture_id_;
};


#endif
