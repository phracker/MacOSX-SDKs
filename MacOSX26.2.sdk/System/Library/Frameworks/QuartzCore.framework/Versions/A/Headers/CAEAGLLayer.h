/* CoreAnimation - CAEAGLLayer.h

   Copyright (c) 2007-2025, Apple Inc.
   All rights reserved. */

#ifdef __OBJC__

#if __has_include(<OpenGLES/EAGLDrawable.h>)

#import <QuartzCore/CALayer.h>
#import <OpenGLES/EAGLDrawable.h>

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

/* CAEAGLLayer is a layer that implements the EAGLDrawable protocol,
 * allowing it to be used as an OpenGLES render target. Use the
 * `drawableProperties' property defined by the protocol to configure
 * the created surface. */

#ifndef GLES_SILENCE_DEPRECATION
API_DEPRECATED("OpenGLES is deprecated. (Define GLES_SILENCE_DEPRECATION to silence these warnings)", ios(2.0, 12.0), tvos(9.0, 12.0))
API_UNAVAILABLE(macos, watchos, visionos)
#else
API_AVAILABLE(ios(2.0), tvos(9.0)) API_UNAVAILABLE(macos, watchos, visionos)
#endif
@interface CAEAGLLayer : CALayer <EAGLDrawable>
{
@private
  struct _CAEAGLNativeWindow *_win;
}

/* When false (the default value) changes to the layer's render buffer
 * appear on-screen asynchronously to normal layer updates. When true,
 * changes to the GLES content are sent to the screen via the standard
 * CATransaction mechanisms. */

@property BOOL presentsWithTransaction API_AVAILABLE(macos(11.0), ios(9.0), tvos(9.0)) API_UNAVAILABLE(watchos);

/* Note: the default value of the `opaque' property in this class is true,
 * not false as in CALayer. */

@end

NS_HEADER_AUDIT_END(nullability, sendability)

#endif /* __has_include(<OpenGLES/EAGLDrawable.h>) */

#endif /* __OBJC__ */
