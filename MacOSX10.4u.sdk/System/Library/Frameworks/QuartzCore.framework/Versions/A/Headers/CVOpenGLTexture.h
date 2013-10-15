/*
 *  CVOpenGLTexture.h
 *  CoreVideo
 *
 *  Copyright (c) 2004 Apple Computer, Inc. All rights reserved.
 *
 */
 
 /*! @header CVOpenGLTexture.h
	@copyright 2004 Apple Computer, Inc. All rights reserved.
	@availability Mac OS X 10.4 or later
    @discussion A CoreVideo Texture derives from an ImageBuffer, and is used for supplying source image data to OpenGL.
    		   
*/

#if !defined(__COREVIDEO_CVOPENGLTEXTURE_H__)
#define __COREVIDEO_CVOPENGLTEXTURE_H__ 1

#include <QuartzCore/CVBase.h>
#include <QuartzCore/CVReturn.h>
#include <QuartzCore/CVImageBuffer.h>
#include <ApplicationServices/ApplicationServices.h>
#include <OpenGL/OpenGL.h>
#include <OpenGL/gl.h>
#include <stddef.h>
#include <stdint.h>

#if defined(__cplusplus)
extern "C" {
#endif

#pragma mark CVOpenGLTexture

/*!
    @typedef	CVOpenGLTextureRef
    @abstract   OpenGL texture based image buffer

*/
typedef CVImageBufferRef CVOpenGLTextureRef;

CV_EXPORT CFTypeID CVOpenGLTextureGetTypeID() AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/*!
    @function   CVOpenGLTextureRetain
    @abstract   Retains a CVOpenGLTexture object
    @discussion Equivalent to CFRetain, but NULL safe
    @param      buffer A CVOpenGLTexture object that you want to retain.
    @result     A CVOpenGLTexture object that is the same as the passed in buffer.
*/
CV_EXPORT CVOpenGLTextureRef CVOpenGLTextureRetain( CVOpenGLTextureRef texture ) AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/*!
    @function   CVOpenGLTextureRelease
    @abstract   Releases a CVOpenGLTexture object
    @discussion Equivalent to CFRelease, but NULL safe
    @param      buffer A CVOpenGLTexture object that you want to release.
*/
CV_EXPORT void CVOpenGLTextureRelease( CVOpenGLTextureRef texture ) AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/*!
    @function   CVOpenGLTextureGetTarget
    @abstract   Returns the texture target (eg. 2D vs. rect texture extension) of the CVOpenGLTexture
    @param      image Target CVOpenGLTexture
    @result     OpenGL texture target
*/
CV_EXPORT GLenum CVOpenGLTextureGetTarget( CVOpenGLTextureRef image) AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/*!
    @function   CVOpenGLTextureGetName
    @abstract   Returns the texture target name of the CVOpenGLTexture
    @param      image Target CVOpenGLTexture
    @result     OpenGL texture target name
*/
CV_EXPORT GLuint CVOpenGLTextureGetName( CVOpenGLTextureRef image) AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/*!
    @function   CVOpenGLTextureIsFlipped
    @abstract   Returns whether the image is flipped vertically or not.
    @param      image Target CVOpenGLTexture
    @result     True if 0,0 in the texture is upper left, false if 0,0 is lower left
*/
CV_EXPORT Boolean CVOpenGLTextureIsFlipped( CVOpenGLTextureRef image) AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/*!
    @function   CVOpenGLTextureGetCleanTexCoords 
    @abstract   Returns convenient texture coordinates for the part of the image that should be displayed
    @discussion This function automatically takes into account whether or not the texture is flipped.
    @param      image Target CVOpenGLTexture
    @param      lowerLeft  - array of two GLfloats where the s and t texture coordinates of the lower left corner of the image will be stored
    @param      lowerRight - array of two GLfloats where the s and t texture coordinates of the lower right corner of the image will be stored
    @param      upperRight - array of two GLfloats where the s and t texture coordinates of the upper right corner of the image will be stored
    @param      upperLeft  - array of two GLfloats where the s and t texture coordinates of the upper right corner of the image will be stored
*/
CV_EXPORT void CVOpenGLTextureGetCleanTexCoords( CVOpenGLTextureRef image, 
                                                 GLfloat lowerLeft[2], 
						 GLfloat lowerRight[2], 
						 GLfloat upperRight[2],
						 GLfloat upperLeft[2]) AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

#if defined(__cplusplus)
}
#endif

#endif
