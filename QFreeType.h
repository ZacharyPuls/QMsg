#ifndef QMSG_QFREETYPE_H
#define QMSG_QFREETYPE_H

#include "QVersion.h"

#include "QLog.h"
#include "QString.h"

#include "ft2build.h"
#include "freetype/freetype.h"

// A C++ wrapper around the C FreeType library and associated handle.
// This only serves to allocate/deallocate the FT_Library handle when needed.
class QFreeType {
public:
	static QFreeType &GetInstance() {
		static QFreeType instance;
		return instance;
	}

    inline FT_Library GetFreeType() {
		return freetype_library_handle_;
    }

	inline FT_Face NewFace(QString font_path) {
		FT_Face face = nullptr;
		if (FT_New_Face(freetype_library_handle_, FROM_QSTRING(font_path).c_str(), 0, &face)) {
			Log->Error(L"Could not load FreeType Face: " + font_path + L".");
		}
		return face;
	}

	inline void DoneFace(FT_Face font_face) {
		if (FT_Done_Face(font_face)) {
			Log->Error(L"Could not release FreeType Face.");
		}
	}

	inline void SetPixelSizes(FT_Face face, FT_UInt width, FT_UInt height) {
		FT_Set_Pixel_Sizes(face, width, height);
	}

	inline bool LoadChar(FT_Face face, FT_ULong character, FT_Int32 load_flags) {
		if (FT_Load_Char(face, character, load_flags)) {
			Log->Error(L"Could not load FreeType character " + TO_QSTRING(character) + L".");
			return false;
		}
		return true;
	}
private:
	inline QFreeType() {
		if (FT_Init_FreeType(&freetype_library_handle_)) {
			Log->Error(L"Could not initialize FreeType library.");
		}
	}

	inline ~QFreeType() {
		if (FT_Done_FreeType(freetype_library_handle_)) {
			Log->Error(L"Could not release FreeType library.");
		}
	}

	QFreeType(QFreeType const &) = delete;
	void operator=(QFreeType const &) = delete;

    FT_Library freetype_library_handle_;
};
#endif
