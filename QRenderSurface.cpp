#include "QRenderSurface.h"

#include "QGLVertexArrayObject.h"
#include "QGLVertexBufferObject.h"
#include "QVertexBufferPool.h"

#include <algorithm>
#include <vector>

#pragma comment(lib, "opengl32.lib")

constexpr char *VERTEX_SHADER = "#version 330 core                                          \n\
                                 in vec2 vertex;                                            \n\
                                 in vec2 in_texcoord;                                       \n\
								 out vec2 tex_coords;								     	\n\
                                 uniform mat4 projection;                                   \n\
                                 void main() {                                              \n\
                                     gl_Position = projection * vec4(vertex.xy, 0.0, 1.0);  \n\
                                     tex_coords = in_texcoord;                              \n\
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
    gl_shader_ = new QGLShaderProgram(VERTEX_SHADER, FRAGMENT_SHADER);
    if (!gl_shader_->Create()) {
        Log->Error(L"Could not initialize QGLShader for QRenderSurface creation.");
        return;
    }

    gl_shader_->Bind();

	vertex_buffer_ = QVertexBufferPool::GetInstance().Get();

	if (vertex_buffer_ == nullptr) {
		Log->Error(L"Could not retrieve QVertexBuffer from QVertexBufferPool.");
		return;
	}

    RECT client_rect = { 0 };
    if (!GetClientRect(hWnd, &client_rect)) {
        Log->SystemError(L"GetClientRect");
        return;
    }

    Resize(client_rect.right, client_rect.bottom);
}

QRenderSurface::~QRenderSurface() {
	if (gl_shader_ != nullptr) {
		delete gl_shader_;
	}

	if (gl_context_ != nullptr) {
		delete gl_context_;
	}

	if (vertex_buffer_ != nullptr) {
		QVertexBufferPool::GetInstance().Release(vertex_buffer_);
	}
}

void QRenderSurface::Render() {
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f); // Black
	glClear(GL_COLOR_BUFFER_BIT);

	gl_shader_->Bind();

	vertex_buffer_->Reset();

	for (auto &object : objects_) {
		vertex_buffer_->AddMesh(object.get_mesh());
	}

	GLint vertex_attribute = gl_shader_->get_attribute_location("vertex");
	GLint texcoord_attribute = gl_shader_->get_attribute_location("in_texcoord");

	vertex_buffer_->Bind();

	glEnableVertexAttribArray(vertex_attribute);
	glEnableVertexAttribArray(texcoord_attribute);
	glVertexAttribPointer(vertex_attribute, 2, GL_FLOAT, GL_FALSE, 0, 0);
	glVertexAttribPointer(texcoord_attribute, 2, GL_FLOAT, GL_FALSE, 0, 0);
	glDrawArrays(GL_TRIANGLES, 0, vertex_buffer_->get_num_vertices() / 6); // 2 points per vertex, 3 vertices per triangle.

	GLint err = glGetError();
	if (err != GL_NO_ERROR) {
		Log->Error(L"OpenGL Error: " + ITO_QSTRING(err));
	}

	gl_context_->SwapBuffers();
}