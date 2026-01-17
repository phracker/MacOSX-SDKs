/*
     File:       QuickTime.r
 
     Contains:   Master include for all of QuickTime on OS X
 
     Version:    QuickTime 7.7.3
 
     Copyright:  © 1999-2015 by Apple Inc., all rights reserved.
 
     Bugs?:      For bug reports, consult the following page on
                 the World Wide Web:
 
                     http://developer.apple.com/bugreporter/
*/

/*
  QuickTime has been deprecated in 10.9.

  AVFoundation and AVKit are the frameworks recommended for all new development 
  involving time-based audiovisual media on OS X.
*/

#ifndef __QUICKTIME_R__
#define __QUICKTIME_R__

#ifndef __CARBON_R__
#include <Carbon/Carbon.r>
#endif

#ifndef __MOVIES_R__
#include <QuickTime/Movies.r>
#endif

#ifndef __IMAGECOMPRESSION_R__
#include <QuickTime/ImageCompression.r>
#endif

#ifndef __IMAGECODEC_R__
#include <QuickTime/ImageCodec.r>
#endif

#ifndef __QUICKTIMECOMPONENTS_R__
#include <QuickTime/QuickTimeComponents.r>
#endif

#ifndef __QTSMOVIE_R__
#include <QuickTime/QTSMovie.r>
#endif

#ifndef __QTSTREAMINGCOMPONENTS_R__
#include <QuickTime/QTStreamingComponents.r>
#endif


#endif /* __QUICKTIME_R__ */

