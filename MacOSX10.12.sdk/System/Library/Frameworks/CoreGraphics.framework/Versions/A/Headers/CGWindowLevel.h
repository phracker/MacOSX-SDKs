/* CoreGraphics - CGWindowLevel.h
   Copyright (c) 2000-2008 Apple Inc.
   All rights reserved. */

#ifndef CGWINDOWLEVEL_H_
#define CGWINDOWLEVEL_H_

#include <CoreFoundation/CFAvailability.h>
#include <CoreGraphics/CGBase.h>
#include <stdint.h>

/* Windows may be assigned to a particular level. When assigned to a level,
   the window is ordered relative to all other windows in that level.
   Windows with a higher level are sorted in front of windows with a lower
   level.

   A common set of window levels is defined here for use within higher level
   frameworks. The levels are accessed via a key and function, so that
   levels may be changed or adjusted in future releases without breaking
   binary compatability. */

typedef CF_ENUM (int32_t, CGWindowLevelKey) {
    kCGBaseWindowLevelKey = 0,
    kCGMinimumWindowLevelKey,
    kCGDesktopWindowLevelKey,
    kCGBackstopMenuLevelKey,
    kCGNormalWindowLevelKey,
    kCGFloatingWindowLevelKey,
    kCGTornOffMenuWindowLevelKey,
    kCGDockWindowLevelKey,
    kCGMainMenuWindowLevelKey,
    kCGStatusWindowLevelKey,
    kCGModalPanelWindowLevelKey,
    kCGPopUpMenuWindowLevelKey,
    kCGDraggingWindowLevelKey,
    kCGScreenSaverWindowLevelKey,
    kCGMaximumWindowLevelKey,
    kCGOverlayWindowLevelKey,
    kCGHelpWindowLevelKey,
    kCGUtilityWindowLevelKey,
    kCGDesktopIconWindowLevelKey,
    kCGCursorWindowLevelKey,
    kCGAssistiveTechHighWindowLevelKey,
    kCGNumberOfWindowLevelKeys	/* Must be last. */
};

typedef int32_t CGWindowLevel;

/* Return the window level that corresponds to one of the standard window
   types. */

CG_EXTERN CGWindowLevel CGWindowLevelForKey(CGWindowLevelKey key)
  CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_NA);

/* The number of window levels reserved by Apple for internal use. */
#define kCGNumReservedWindowLevels	(16)

/* Definitions of older constant values. */
#define kCGBaseWindowLevel						\
  CGWindowLevelForKey(kCGBaseWindowLevelKey)
#define kCGMinimumWindowLevel						\
  CGWindowLevelForKey(kCGMinimumWindowLevelKey)
#define kCGDesktopWindowLevel						\
  CGWindowLevelForKey(kCGDesktopWindowLevelKey)
#define kCGDesktopIconWindowLevel					\
  CGWindowLevelForKey(kCGDesktopIconWindowLevelKey)
#define kCGBackstopMenuLevel						\
  CGWindowLevelForKey(kCGBackstopMenuLevelKey)
#define kCGNormalWindowLevel						\
  CGWindowLevelForKey(kCGNormalWindowLevelKey)
#define kCGFloatingWindowLevel						\
  CGWindowLevelForKey(kCGFloatingWindowLevelKey)
#define kCGTornOffMenuWindowLevel					\
  CGWindowLevelForKey(kCGTornOffMenuWindowLevelKey)
#define kCGDockWindowLevel						\
  CGWindowLevelForKey(kCGDockWindowLevelKey)
#define kCGMainMenuWindowLevel						\
  CGWindowLevelForKey(kCGMainMenuWindowLevelKey)
#define kCGStatusWindowLevel						\
  CGWindowLevelForKey(kCGStatusWindowLevelKey)
#define kCGModalPanelWindowLevel					\
  CGWindowLevelForKey(kCGModalPanelWindowLevelKey)
#define kCGPopUpMenuWindowLevel						\
  CGWindowLevelForKey(kCGPopUpMenuWindowLevelKey)
#define kCGDraggingWindowLevel						\
  CGWindowLevelForKey(kCGDraggingWindowLevelKey)
#define kCGScreenSaverWindowLevel					\
  CGWindowLevelForKey(kCGScreenSaverWindowLevelKey)
#define kCGCursorWindowLevel						\
  CGWindowLevelForKey(kCGCursorWindowLevelKey)
#define kCGOverlayWindowLevel						\
  CGWindowLevelForKey(kCGOverlayWindowLevelKey)
#define kCGHelpWindowLevel						\
  CGWindowLevelForKey(kCGHelpWindowLevelKey)
#define kCGUtilityWindowLevel						\
  CGWindowLevelForKey(kCGUtilityWindowLevelKey)
#define kCGAssistiveTechHighWindowLevel					\
  CGWindowLevelForKey(kCGAssistiveTechHighWindowLevelKey)
#define kCGMaximumWindowLevel						\
  CGWindowLevelForKey(kCGMaximumWindowLevelKey)

#endif /* CGWINDOWLEVEL_H_ */
