/*
     File:       QuickTime/QuickTime.h
 
     Contains:   Master include for all of QuickTime on OS X
 
     Version:    QuickTime 7.2.1
 
     Copyright:  © 1999-2006 by Apple Inc., all rights reserved.
 
     Bugs?:      For bug reports, consult the following page on
                 the World Wide Web:
 
                     http://developer.apple.com/bugreporter/
 
*/
#ifndef __QUICKTIME__
#define __QUICKTIME__

#ifndef __CARBON__
#include <Carbon/Carbon.h>
#endif



/* QuickTime is not available to 64-bit clients */

#if !__LP64__

#ifndef __QTML__
#include <QuickTime/QTML.h>
#endif

#ifndef __MEDIAHANDLERS__
#include <QuickTime/MediaHandlers.h>
#endif

#ifndef __MOVIES__
#include <QuickTime/Movies.h>
#endif

#ifndef __MOVIESFORMAT__
#include <QuickTime/MoviesFormat.h>
#endif

#ifndef __QUICKTIMEVR__
#include <QuickTime/QuickTimeVR.h>
#endif

#ifndef __QUICKTIMEVRFORMAT__
#include <QuickTime/QuickTimeVRFormat.h>
#endif

#ifndef __IMAGECOMPRESSION__
#include <QuickTime/ImageCompression.h>
#endif

#ifndef __IMAGECODEC__
#include <QuickTime/ImageCodec.h>
#endif

#ifndef __QUICKTIMEMUSIC__
#include <QuickTime/QuickTimeMusic.h>
#endif

#ifndef __QUICKTIMECOMPONENTS__
#include <QuickTime/QuickTimeComponents.h>
#endif

#ifndef __QUICKTIMESTREAMING__
#include <QuickTime/QuickTimeStreaming.h>
#endif

#ifndef __QTSMOVIE__
#include <QuickTime/QTSMovie.h>
#endif

#ifndef __QTSTREAMINGCOMPONENTS__
#include <QuickTime/QTStreamingComponents.h>
#endif

#ifndef __QUICKTIMEERRORS__
#include <QuickTime/QuickTimeErrors.h>
#endif

#ifndef __HIMOVIEVIEW__
#include <QuickTime/HIMovieView.h>
#endif



#endif // !__LP64__


#endif /* __QUICKTIME__ */

