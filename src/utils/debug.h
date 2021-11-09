#pragma once
#define DEBUG

#include "glad/glad.h"

#include "logger.h"

static char const *gl_error_string(GLenum err)
{
    switch (err)
    {
        case GL_NO_ERROR:
            return "GL_NO_ERROR";
        case GL_INVALID_ENUM:
            return "GL_INVALID_ENUM";
        case GL_INVALID_VALUE:
            return "GL_INVALID_VALUE";
        case GL_INVALID_OPERATION:
            return "GL_INVALID_OPERATION";
        case GL_OUT_OF_MEMORY:
            return "GL_OUT_OF_MEMORY";
        case GL_INVALID_FRAMEBUFFER_OPERATION:
            return "GL_INVALID_FRAMEBUFFER_OPERATION";
        default:
            return "UNKNOWN OPENGL ERROR";
    }
}

namespace mrld
{
    inline void CHECK_OGL_ERRORS()
    {
#ifndef DEBUG
        return;
#endif
        GLuint err;
        while ((err = glGetError()) != GL_NO_ERROR) {
            const char* msg = gl_error_string(err);
            Logger::log(LogLevel::ERR, "OPENGL ERROR: %u - %s", err, msg);
        }
    }
}
