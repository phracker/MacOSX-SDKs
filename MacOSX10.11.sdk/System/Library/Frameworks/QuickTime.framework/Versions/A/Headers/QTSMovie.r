/*
     File:       QTSMovie.r
 
     Contains:   QuickTime Interfaces.
 
     Version:    QuickTime 7.7.3
 
     Copyright:  © 1990-2015 by Apple Inc., all rights reserved
 
     Bugs?:      For bug reports, consult the following page on
                 the World Wide Web:
 
                     http://developer.apple.com/bugreporter/
*/

/*
  QuickTime has been deprecated in 10.9.

  AVFoundation and AVKit are the frameworks recommended for all new development 
  involving time-based audiovisual media on OS X.
*/

#ifndef __QTSMOVIE_R__
#define __QTSMOVIE_R__

#ifndef __CORESERVICES_R__
#include <CoreServices/CoreServices.r>
#endif

#define kQTSStreamMediaType 			'strm'
#define kQTSHintMediaType 				'hint'

#endif /* __QTSMOVIE_R__ */

