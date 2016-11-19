#include "QRenderSurface.h"

#include "QGLVertexArrayObject.h"
#include "QGLVertexBufferObject.h"

#include <algorithm>
#include <vector>

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
    gl_shader_ = new QGLShaderProgram(VERTEX_SHADER, FRAGMENT_SHADER);
    if (!gl_shader_->Create()) {
        Log->Error(L"Could not initialize QGLShader for QRenderSurface creation.");
        return;
    }

    gl_shader_->Bind();
	
	vertex_buffer_object_ = new QGLVertexBufferObject();
	vertex_array_object_ = new QGLVertexArrayObject();

	if (!vertex_buffer_object_->Create()) {
		Log->Error(L"Could not initialize QGLVertexBufferObject for QRenderSurface creation.");
		return;
	}

	if (!vertex_array_object_->Create()) {
		Log->Error(L"Could not initialize QGLVertexArrayObject for QRenderSurface creation.");
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
	if (gl_shader_) {
		delete gl_shader_;
	}

	if (gl_context_) {
		delete gl_context_;
	}

	if (vertex_buffer_object_) {
		delete vertex_buffer_object_;
	}

	if (vertex_array_object_) {
		delete vertex_array_object_;
	}
}

std::array<float, 16> QRenderSurface::project_ortho_(float width, float height) {
    return {
        2.0f / width, 0.0f, 0.0f, -1.0f,
        0.0f, 2.0f / height, 0.0f, -1.0f,
        0.0f, 0.0f, -1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f
    };
}

void QRenderSurface::Render() {
	glClear(GL_COLOR_BUFFER_BIT);
	gl_shader_->Bind();
	vertex_array_object_->Bind();
	vertex_buffer_object_->Bind();
	int num_points = meshes_.size() * 2 * 3 * 2;
	// Assume 2 triangles per mesh, 3 vertices per triangle, and 2 points per vertex.
	// This is a decent assumption for using fonts, which are two triangles each, in 2D.
	// TODO: Make this a little bit more robust, and add more generic mapped buffer pooling and rendering.
	std::vector<GLfloat> all_vertices(num_points);
	std::transform(meshes_.begin(), meshes_.end(), all_vertices, [](auto &m) -> {m.collect_vertex_data()});
	vertex_buffer_object_->UpdateBufferData(sizeof(GLfloat) * all_vertices.size(), &all_vertices[0]);
	GLint attribute_index = gl_shader_->get_attribute_location("vertex");
#if defined(QMSG_GL_HIGH_PRECISION)
	GLenum attribute_type = GL_DOUBLE; // Double precision attributes require OpenGL Version 4.1 or higher, FYI.
#else
	GLenum attribute_type = GL_FLOAT;
#endif
	glEnableVertexAttribArray(attribute_index);
	glVertexAttribPointer(attribute_index, 2, attribute_type, GL_FALSE, 0, 0);
	glDrawArrays(GL_TRIANGLES, 0, all_vertices.size() / 6); // 2 points per vertex, 3 vertices per triangle.
	vertex_buffer_object_->Unbind();
	vertex_array_object_->Unbind();
	gl_context_->SwapBuffers();
}