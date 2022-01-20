/* ======================================================
SFile: OpenGL.h
SDate: 2021.10.03.
SRevision: S
SCreator: Gergely Zara
SNotice: S
======================================================*/

//https://www.khronos.org/registry/OpenGL/api/GL/glxext.h
//https://www.khronos.org/registry/OpenGL/api/GLES2/gl2.h

#include <gl/gl.h>
#include "GLLoading.h"

#ifndef GL_MULTISAMPLE
#define GL_MULTISAMPLE  0x809D
#endif

#define GL_ARRAY_BUFFER 0x8892
#define GL_STATIC_DRAW 0x88E4 //use when buffer objects are not changed a lot
#define GL_DYNAMIC_DRAW 0x88E8 //use when buffer objects are changed a lot

#define GL_FRAGMENT_SHADER 0x8B30
#define GL_VERTEX_SHADER 0x8B31

//typedef khronos_ssize_t GLsizeiptr;
typedef char GLchar;

typedef void (*GENBUFFERS) (GLsizei, GLuint*);
typedef void (*BINDBUFFER) (GLenum, GLuint);
typedef void (*BUFFERDATA) (GLenum, size_t, const void*, GLenum);//GLsizeiptr needed
typedef void (*ENABLEVERTEXATTRIBARRAY) (GLuint);
typedef void (*VERTEXATTRIBPOINTER)
(
	GLuint index,
	GLint size,
	GLenum type,
	GLboolean normalized,
	GLsizei stride,
	const void* pointer
);

typedef void (*GENVERTEXARRAYS) (GLsizei, GLuint*);
typedef void (*BINDVERTEXARRAY) (GLuint);

typedef GLuint (*CREATESHADER) (GLenum);
typedef void (*SHADERSOURCE) (GLuint, GLsizei, const char**, const int*);
typedef void (*COMPILESHADER) (GLuint);
typedef void (*GETSHADERIV) (GLsizei, GLuint*);
typedef void (*GETSHADERINFOLOG) (GLsizei, GLuint*);
typedef void (*DELETESHADER) (GLsizei, GLuint*);
typedef void (*ATTACHSHADER) (GLuint, GLuint);

typedef void (*BINDATTRIBLOC) (GLsizei, GLuint*);
typedef void (*LINKPROGRAM) (GLuint);
typedef void (*USEPROGRAM) (GLuint);
typedef void (*GETPROGRAMIV) (GLsizei, GLuint*);
typedef void (*GETPROGRAMINFOLOG) (GLsizei, GLuint*);
typedef void (*DELETEPROGRAM) (GLsizei, GLuint*);
typedef GLuint (*CREATEPROGRAM) ();

typedef GLint (*GETUNIFORMLOCATION) (GLuint, const GLchar*);
typedef void (*UNIFORM1FV) (GLint, GLsizei, const GLfloat*);
typedef void (*PROGRAMUNIFORM1FV)
(
	GLuint,
	GLint,
	GLsizei,
	const GLfloat*
);

void* GetAnyGLFuncAddress(const char* name)
{
	void *p = (void *)wglGetProcAddress(name);
	if (p == 0 || (p == (void*)0x1) || (p == (void*)0x2) || (p == (void*)0x3) || (p == (void*)-1))
	{
		HMODULE module = LoadLibraryA("opengl32.dll");
		p = (void *)GetProcAddress(module, name);
	}
	return p;
}

struct WindowProperty
{
	HGLRC OpenGLHandle;

}WindowProperties[1];

struct GLBufferObject
{
	int VertIndex;
	int NormIndex;
	int ColIndex;
	int IndIndex;

	GLfloat VertBuffer[800000];
	GLfloat NormBuffer[800000];
	GLfloat ColBuffer[800000];
	GLfloat TestBuffer[800000];
	GLubyte IndicesBuffer[800000];
}BO[1];

/*
		*
	   /|
	c / |b
	 /  |
  angle *---*
	  a
*/

float CalcHeightHalf(float FOV, float N)
{
	float a = N;
	float Angle = FOV / 2;
	double c = a / cos(Angle);
	double b = sqrt(c * c - a * a);
	return (float)b;

}

