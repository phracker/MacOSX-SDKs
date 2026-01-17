/* CoreGraphics - CGDirectDisplayMetal.h
   Copyright (c) 2000-2015 Apple Inc.
   All rights reserved. */

#ifndef CGDIRECTDISPLAYMETAL_H_
#define CGDIRECTDISPLAYMETAL_H_

/* This file only makes sense to Objective C clients */
#if defined(__OBJC__)

#import <CoreGraphics/CGDirectDisplay.h>

@protocol MTLDevice;

/* Return the Metal device for the GPU currently being used to drive a given display */
/* Note: On systems with automatic graphics switching enabled, this value can change at
   almost any time. */
CG_EXTERN id<MTLDevice> __nullable CGDirectDisplayCopyCurrentMetalDevice(CGDirectDisplayID display) CG_AVAILABLE_STARTING(__MAC_10_11, __IPHONE_NA);

#endif /* __OBJC__ */

#endif /* CGDIRECTDISPLAYMETAL_H_ */
