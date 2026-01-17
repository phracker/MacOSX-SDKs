//
//  jawt_md.h
//
//  Copyright (c) 2002 Apple computer Inc. All rights reserved.
//

#ifndef _JAVASOFT_JAWT_MD_H_
#define _JAVASOFT_JAWT_MD_H_

#include <jawt.h>
#include <AppKit/NSView.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct JAWT_MacOSXDrawingSurfaceInfo
{
    NSView *cocoaViewRef; // the view is guaranteed to be valid only for the duration of Component.paint method
}
JAWT_MacOSXDrawingSurfaceInfo;

#ifdef __cplusplus
}
#endif

#endif /* !_JAVASOFT_JAWT_MD_H_ */
