#ifndef QMSG_QGLEXTENSIONS_INL
#define QMSG_QGLEXTENSIONS_INL

// Utilities
typedef PFNGLGETSTRINGPROC				glGetString;

// Textures
typedef PFNGLACTIVETEXTUREPROC			glActiveTexture;
typedef PFNGLGENTEXTURESPROC			glGenTextures;
typedef PFNGLBINDTEXTUREPROC			glBindTexture;
typedef PFNGLTEXIMAGE2DPROC				glTexImage2D;
typedef PFNGLTEXPARAMETERIPROC			glTexParameteri;
typedef PFNGLPIXELSTOREIPROC			glPixelStorei;

// Vertex/Array Buffers
typedef PFNGLGENBUFFERSPROC				glGenBuffers;
typedef PFNGLBINDBUFFERPROC				glBindBuffer;
typedef PFNGLBUFFERDATAPROC				glBufferData;
typedef PFNGLGENVERTEXARRAYSPROC		glGenVertexArrays;
typedef PFNGLBINDVERTEXARRAYPROC		glBindVertexArray;
typedef PFNGLVERTEXATTRIBPOINTERPROC	glVertexAttribPointer;

// Shaders
typedef PFNGLUNIFORM1FPROC				glUniform1f;
typedef PFNGLUNIFORM2FPROC				glUniform2f;
typedef PFNGLUNIFORM3FPROC				glUniform3f;
typedef PFNGLUNIFORM4FPROC				glUniform4f;
typedef PFNGLUNIFORM1DPROC				glUniform1f;
typedef PFNGLUNIFORM2DPROC				glUniform2f;
typedef PFNGLUNIFORM3DPROC				glUniform3f;
typedef PFNGLUNIFORM4DPROC				glUniform4f;
typedef PFNGLUNIFORM1IPROC				glUniform1i;
typedef PFNGLUNIFORM2IPROC				glUniform2i;
typedef PFNGLUNIFORM3IPROC				glUniform3i;
typedef PFNGLUNIFORM4IPROC				glUniform4i;
typedef PFNGLUNIFORM1UIPROC				glUniform1ui;
typedef PFNGLUNIFORM2UIPROC				glUniform2ui;
typedef PFNGLUNIFORM3UIPROC				glUniform3ui;
typedef PFNGLUNIFORM4UIPROC				glUniform4ui;
typedef PFNGLUNIFORM1FVPROC				glUniform1fv;
typedef PFNGLUNIFORM2FVPROC				glUniform2fv;
typedef PFNGLUNIFORM3FVPROC				glUniform3fv;
typedef PFNGLUNIFORM4FVPROC				glUniform4fv;
typedef PFNGLUNIFORM1DVPROC				glUniform1fv;
typedef PFNGLUNIFORM2DVPROC				glUniform2fv;
typedef PFNGLUNIFORM3DVPROC				glUniform3fv;
typedef PFNGLUNIFORM4DVPROC				glUniform4fv;
typedef PFNGLUNIFORM1IVPROC				glUniform1iv;
typedef PFNGLUNIFORM2IVPROC				glUniform2iv;
typedef PFNGLUNIFORM3IVPROC				glUniform3iv;
typedef PFNGLUNIFORM4IVPROC				glUniform4iv;
typedef PFNGLUNIFORM1UIVPROC			glUniform1uiv;
typedef PFNGLUNIFORM2UIVPROC			glUniform2uiv;
typedef PFNGLUNIFORM3UIVPROC			glUniform3uiv;
typedef PFNGLUNIFORM4UIVPROC			glUniform4uiv;
#endif
