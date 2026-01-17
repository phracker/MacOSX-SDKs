/*
	File:  AVFoundation.h

	Framework:  AVFoundation
 
	Copyright 2010-2020 Apple Inc. All rights reserved.

	To report bugs, go to:  http://developer.apple.com/bugreporter/

*/

#if __has_include(<AVFoundation/AVFCore.h>)
#import <AVFoundation/AVFCore.h>
#else
#import <AVFCore/AVFCore.h>
#endif

#if __has_include(<AVFoundation/AVFAudio.h>)
#import <AVFoundation/AVFAudio.h>
#endif

#if __has_include(<AVFoundation/AVFCapture.h>)
#import <AVFoundation/AVFCapture.h>
#else
#import <AVFCapture/AVFCapture.h>
#endif
