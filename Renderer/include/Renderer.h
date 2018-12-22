#pragma once

#include <GL/glew.h>

#define ASSERT(x) if (!(x)) __debugbreak()
#define GLCALL(x) GLClearError();\
    x;\
	ASSERT(GLLogCall(#x, __FILE__, __LINE__))

bool GLLogCall(const char* function, const char* file, int line);
void GLClearError();

class Renderer {
public:
	void Clear() const;
};
