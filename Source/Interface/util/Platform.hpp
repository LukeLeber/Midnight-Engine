/**
 */
#define OPENGLPP_TESTING

#ifndef PLATFORM_HPP
#    define PLATFORM_HPP

#    include "BuildConstraints.hpp"

#    if defined(__linux__)
#        define MIDNIGHT_LINUX 1
#        include <GL/glew.h>
#        include <GL/gl.h>
#        include <GL/glu.h>
#        if defined(OPENGLPP_TESTING)
#            include <GL/glut.h>
//#			include <GL/freeglut.h>
#        endif
#    elif defined(__APPLE__)
#        define MIDNIGHT_MAC
#        include <OpenGL/gl.h>
#        include <OpenGL/glu.h>
#        include <GLUT/glut.h>
#    elif defined(_WIN32)
#        define MIDNIGHT_WINDOWS
#        include <windows.h>
#        include <GL/gl.h>
#        include <GL/glu.h>
#    else
#        error This platform is not supported
#    endif
#endif
