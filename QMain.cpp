#include "QMain.h"

#include "QVersion.h"
#include "QLog.h"
#include "QWindow.h"

constexpr char *VERTEX_SHADER = "#version 330 core                                          \n\
                                 layout (location = 1) in vec4 vertex;                                            \n\
								 out vec2 tex_coords;						\n\
                                 uniform mat4x4 projection;                                   \n\
                                 void main() {                                              \n\
							         tex_coords = vertex.zw; \n\
                                     gl_Position = projection * vec4(vertex.xy, 0.0, 1.0);  \n\
                                 }";

constexpr char *FRAGMENT_SHADER = "#version 330 core                                                                        \n\
								   in vec2 tex_coords; \n\
                                   out vec4 color; \n\
								   uniform sampler2D font_texture; \n\
                                   void main() {                                                                            \n\
                                        color = vec4(1.0, 1.0, 1.0, texture2D(font_texture, tex_coords).r) * vec4(1.0, 1.0, 1.0, 1.0);													\n\
                                   }";

INT WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, INT nShowCmd) {
	QWindow *window = new QWindow(hInstance, L"qmsg-main", L"QMsg Client", 480, 640, CW_USEDEFAULT, CW_USEDEFAULT);
	if (!window->Create()) {
		Log->Critical(L"Could not create QWindow. Terminating application.");
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}