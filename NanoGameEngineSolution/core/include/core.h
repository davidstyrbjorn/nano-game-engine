#pragma once

#include<string>

namespace nano
{

// Definitions used in both the editor and the engine side

// Version macros and methods
#define NANO_MAJOR_VERSION 0
#define NANO_MINOR_VERSION 1
static std::string GetWelcomeMessage() { return std::string("Nano Game Engine!\nVersion: " + std::to_string(NANO_MAJOR_VERSION) + "." + std::to_string(NANO_MINOR_VERSION)); }

// Nano typedefs
typedef unsigned int GLenum;
typedef unsigned int GLbitfield;
typedef unsigned int GLuint;
typedef int GLint;
typedef int GLsizei;
typedef unsigned char GLboolean;
typedef signed char GLbyte;
typedef short GLshort;
typedef unsigned char GLubyte;
typedef unsigned short GLushort;
typedef unsigned long GLulong;
typedef float GLfloat;
typedef float GLclampf;
typedef double GLdouble;
typedef double GLclampd;
typedef void GLvoid;
typedef ptrdiff_t GLintptr;
typedef ptrdiff_t GLsizeiptr;

// Nano macros
#define PI 3.14159265359
#define DEG2RADS PI/180
#define RADS2DEG 180/PI

}