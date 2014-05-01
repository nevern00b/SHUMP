#pragma once

// Get the platform
#if defined(_WIN64) || defined(_WIN32)
#define OS_WINDOWS
#elif __APPLE__
#include "TargetConditionals.h"
#if TARGET_OS_IPHONE
#define OS_IOS
#endif
#endif

#if defined(OS_WINDOWS)
	#include <GL3/gl3w.h>
	#include <GLFW/glfw3.h>
#elif defined(OS_IOS)
    #include <OpenGLES/ES3/gl.h>
    //#include <GLES3/gl3.h>
#endif

typedef unsigned char uchar;
typedef unsigned short ushort;
typedef unsigned int uint;
