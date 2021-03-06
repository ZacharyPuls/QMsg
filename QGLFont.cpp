#include "QGLFont.h"

#include "QLog.h"

#include <algorithm>

QGLFont::QGLFont() {

}

QGLFont::~QGLFont() {
	if (texture_ != nullptr) {
		delete texture_;
	}
	if (font_face_) {
		QFreeType::GetInstance().DoneFace(font_face_);
	}
}

bool QGLFont::Load(QString font_path, int font_size) {
	if (texture_ != nullptr) {
		delete texture_;
	}

	if (font_face_ != NULL) {
		QFreeType::GetInstance().DoneFace(font_face_);
	}

	font_face_ = QFreeType::GetInstance().NewFace(font_path);

	if (font_face_ == NULL) {
		Log->Error(L"Could not load font from file " + font_path + L".");
		return false;
	}

	QFreeType::GetInstance().SetPixelSizes(font_face_, 0, font_size);

	atlas_size_ = calculate_font_atlas_size_(font_face_);

	texture_ = new QGLTexture();
	texture_->set_texture_type(GL_TEXTURE_2D);
	texture_->set_texture_data({
		GL_RED, atlas_size_.first, atlas_size_.second, 0, GL_RED, GL_UNSIGNED_BYTE
	});

	if (!texture_->Create()) {
		Log->Error(L"Could not allocate empty texture of size [" + ITO_QSTRING(atlas_size_.first) + L"," + ITO_QSTRING(atlas_size_.second) + L"] for font texture atlas.");
		QFreeType::GetInstance().DoneFace(font_face_);
		delete texture_;
		return false;
	}

	texture_->SetTextureOption(GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	texture_->SetTextureOption(GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	texture_->SetTextureOption(GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	texture_->SetTextureOption(GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	texture_->Bind();
	
	int x_offset = 0;
	for (GLubyte c = 32; c < 128; ++c) {
		if (!QFreeType::GetInstance().LoadChar(font_face_, c, FT_LOAD_RENDER)) {
			continue;
		}

		texture_->SetTextureData(x_offset, 0, NULL, font_face_->glyph->bitmap.width, font_face_->glyph->bitmap.rows, NULL, font_face_->glyph->bitmap.buffer);
		x_offset += font_face_->glyph->bitmap.width;

		QGLCharacter character = {
			(GLfloat) x_offset / (GLfloat)atlas_size_.first,
			{ { font_face_->glyph->advance.x >> 6, font_face_->glyph->advance.y >> 6 } },
			{ { font_face_->glyph->bitmap.width, font_face_->glyph->bitmap.rows } },
			{ { font_face_->glyph->bitmap_left, font_face_->glyph->bitmap_top } }
		};
		characters_.insert(std::make_pair(c, character));
	}

	texture_->Unbind();

	return true;
}

std::vector<QGLTriangle2D> QGLFont::RenderString(QString string, GLfloat x, GLfloat y, GLfloat scale) {
	std::vector<QGLTriangle2D> triangles;
	triangles.reserve(string.length() * 2);
	for (auto &c : FROM_QSTRING(string)) {
		QGLCharacter character = characters_[c];
		
		GLfloat transformed_x_pos = x + character.origin[0] * scale;
		GLfloat transformed_y_pos = -y - character.origin[1] * scale;
		GLfloat width = character.size[0] * scale;
		GLfloat height = character.size[1] * scale;
		
		triangles.push_back(QGLTriangle2D({
			transformed_x_pos, -transformed_y_pos - height,
			transformed_x_pos + width, -transformed_y_pos - height,
			transformed_x_pos, -transformed_y_pos
		},
		{
			character.xoffset, 0.0f,
			character.xoffset + character.size[0] / (GLfloat)atlas_size_.first, 0.0f,
			character.xoffset, character.size[1] / (GLfloat)atlas_size_.second
		}));

		triangles.push_back(QGLTriangle2D(
		{
			transformed_x_pos + width, -transformed_y_pos - height,
			transformed_x_pos + width, -transformed_y_pos,
			transformed_x_pos, -transformed_y_pos
		},
		{
			character.xoffset + character.size[0] / (GLfloat)atlas_size_.first, 0.0f,
			character.xoffset + character.size[0] / (GLfloat)atlas_size_.first, character.size[1] / (GLfloat)atlas_size_.second,
			character.xoffset, character.size[1] / (GLfloat)atlas_size_.second
		}));
		
		x += (character.advance[0] >> 6) * scale;
	}
	return triangles;
}

std::pair<GLint, GLint> QGLFont::calculate_font_atlas_size_(FT_Face font_face) {
	GLint atlas_width = 0;
	GLint atlas_height = 0;
	for (GLubyte c = 32; c < 128; ++c) {
		if (FT_Load_Char(font_face, c, FT_LOAD_RENDER)) {
			Log->Error(L"Could not load font face for character code " + ITO_QSTRING(c) + L".");
			continue;
		}
		atlas_width += font_face->glyph->bitmap.width;
		atlas_height = std::max(atlas_height, (GLint)font_face->glyph->bitmap.rows);
	}

	return std::make_pair(atlas_width, atlas_height);
}
