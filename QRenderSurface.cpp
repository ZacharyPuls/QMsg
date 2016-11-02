#include "QRenderSurface.h"

#include <iostream>

#pragma comment(lib, "opengl32.lib")

constexpr char *VERTEX_SHADER = "#version 330 core                                          \n\
                                 in vec4 vertex;                                            \n\
                                 out vec2 tex_coords;                                       \n\
                                 uniform mat4 projection;                                   \n\
                                 void main() {                                              \n\
                                     gl_Position = projection * vec4(vertex.xy, 0.0, 1.0);  \n\
                                     tex_coords = vertex.zw;                                \n\
                                 }";

constexpr char *FRAGMENT_SHADER = "#version 330 core                                                                        \n\
                                   in vec2 tex_coords;                                                                      \n\
                                   out vec4 color;                                                                          \n\
                                   uniform sampler2D font_texture;                                                          \n\
                                   uniform vec3 text_color;                                                                 \n\
                                   void main() {                                                                            \n\
                                       vec4 texture_sample = vec4(1.0, 1.0, 1.0, texture(font_texture, tex_coords).r);      \n\
                                       color = vec4(text_color, 1.0) * texture_sample;                                      \n\
                                   }";

QRenderSurface::QRenderSurface(HWND hWnd) : gl_context_(new QGLContext(hWnd)) {
    gl_shader_ = new QGLShader(VERTEX_SHADER, FRAGMENT_SHADER);
    if (!gl_shader_->Create()) {
        Log->Error(L"Could not initialize QGLShader for QRenderSurface creation.");
        return;
    }

    gl_shader_->Bind();

    RECT client_rect = { 0 };
    if (!GetClientRect(hWnd, &client_rect)) {
        Log->SystemError(L"GetClientRect");
        return;
    }

    Resize(client_rect.right, client_rect.bottom);
}

QRenderSurface::~QRenderSurface() {
	
}

std::array<float, 16> QRenderSurface::project_ortho_(float width, float height) {
    return {
        2.0f / width, 0.0f, 0.0f, -1.0f,
        0.0f, 2.0f / height, 0.0f, -1.0f,
        0.0f, 0.0f, -1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f
    };
}

