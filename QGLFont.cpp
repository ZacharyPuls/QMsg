#include "QGLFont.h"

QGLFont::QGLFont() {

}

QGLFont::~QGLFont() {
	if (font_face_) {
		QFreeType::GetInstance().DoneFace(font_face_);
	}
}

bool QGLFont::Load(QString font_path, int font_size) {
	font_face_ = QFreeType::GetInstance().NewFace(font_path);
	if (font_face_ != nullptr) {
		QFreeType::GetInstance().SetPixelSizes(font_face_, 0, font_size);
		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
		for (GLubyte c = 0; c < 128; ++c) {
			if (!QFreeType::GetInstance().LoadChar(font_face_, c, FT_LOAD_RENDER)) {
				continue;
			}
			QGLTexture font_texture;
			font_texture.set_texture_type(GL_TEXTURE_2D);
			font_texture.set_texture_data({
				GL_RED, font_face_->glyph->bitmap.width, font_face_->glyph->bitmap.rows, 0, GL_RED, GL_UNSIGNED_BYTE, font_face_->glyph->bitmap.buffer
			});
			if (!font_texture.Create()) {
				continue;
			}
			font_texture.SetTextureOption(GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			font_texture.SetTextureOption(GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			font_texture.SetTextureOption(GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			font_texture.SetTextureOption(GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			QGLCharacter character = {
				font_texture,
				{ font_face_->glyph->bitmap.width, font_face_->glyph->bitmap.rows, font_face_->glyph->bitmap_left, font_face_->glyph->bitmap_top },
				font_face_->glyph->advance.x
			};
			characters_.insert(std::pair<GLchar, QGLCharacter>(c, character));
		}
		return true;
	}
	return false;
}