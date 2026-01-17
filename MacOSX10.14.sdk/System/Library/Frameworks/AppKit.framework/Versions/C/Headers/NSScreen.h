/*
	NSScreen.h
	Application Kit
	Copyright (c) 1994-2018, Apple Inc.
	All rights reserved.
*/

#import <Foundation/NSObject.h>
#import <Foundation/NSArray.h>
#import <Foundation/NSDictionary.h>
#import <Foundation/NSGeometry.h>
#import <Foundation/NSNotification.h>
#import <AppKit/NSGraphics.h>

NS_ASSUME_NONNULL_BEGIN

@class NSColorSpace;

typedef struct NSScreenAuxiliary NSScreenAuxiliaryOpaque;

@interface NSScreen : NSObject {
/*All instance variables are private*/
@private
    NSRect _frame APPKIT_IVAR;          // cached value, possibly stale
    NSWindowDepth _depth APPKIT_IVAR;  
    int _screenNumber APPKIT_IVAR;
    id _auxiliaryStorage APPKIT_IVAR;
}

@property (class, readonly, copy) NSArray<NSScreen *> *screens;	/* All screens; first one is "zero" screen */
@property (class, readonly, nullable, strong) NSScreen *mainScreen;	/* Screen with key window */
@property (class, readonly, nullable, strong) NSScreen *deepestScreen;

/* screensHaveSeparateSpaces returns YES if each screen has its own set of spaces.  This is a system  setting and does not necessarily imply that there are multiple screens, nor that there are multiple spaces on any one screen 
*/
@property (class, readonly) BOOL screensHaveSeparateSpaces NS_AVAILABLE_MAC(10_9);

@property (readonly) NSWindowDepth depth;
@property (readonly) NSRect frame;
@property (readonly) NSRect visibleFrame;
@property (readonly, copy) NSDictionary<NSDeviceDescriptionKey, id> *deviceDescription;
@property (nullable, readonly, strong) NSColorSpace *colorSpace NS_AVAILABLE_MAC(10_6);

@property (readonly) const NSWindowDepth *supportedWindowDepths NS_RETURNS_INNER_POINTER; /* 0 terminated */

/* canRepresentDisplayGamut: returns YES if the colorSpace of the receiving screen is capable of representing the given display gamut
 */
- (BOOL)canRepresentDisplayGamut:(NSDisplayGamut)displayGamut  NS_AVAILABLE_MAC(10_12);

/* Convert to/from the device pixel aligned coordinates sytem of a display 
 */
- (NSRect)convertRectToBacking:(NSRect)rect NS_AVAILABLE_MAC(10_7);
- (NSRect)convertRectFromBacking:(NSRect)rect NS_AVAILABLE_MAC(10_7);

/* Uses NSIntegralRectWithOptions() to produce a pixel aligned rectangle on the target screen from the given input rectangle in global screen coordinates.
 */
- (NSRect)backingAlignedRect:(NSRect)rect options:(NSAlignmentOptions)options NS_AVAILABLE_MAC(10_7);

/* Returns the scale factor representing the number of backing store pixels corresponding to each linear unit in screen space on this NSScreen. This method is provided for rare cases when the explicit scale factor is needed.  Please use -convert*ToBacking: methods whenever possible. 
 */
@property (readonly) CGFloat backingScaleFactor NS_AVAILABLE_MAC(10_7); 

@end


/* Notifications */
APPKIT_EXTERN NSNotificationName const NSScreenColorSpaceDidChangeNotification NS_AVAILABLE_MAC(10_6);  // the notification object is the screen whose profile has changed


@interface NSScreen (NSExtendedDynamicRange)

/* Returns the current maximum color component value for the screen. Typically the maximum is 1.0, but if any rendering context on the screen has requested extended dynamic range, it may return a value greater than 1.0, depending on system capabilities and other conditions. Only rendering contexts that support extended dynamic range can use values greater than 1.0. When the value changes, NSApplicationDidChangeScreenParametersNotification will be posted.
 */
@property (readonly) CGFloat maximumExtendedDynamicRangeColorComponentValue NS_AVAILABLE_MAC(10_11);

@end


@interface NSScreen(NSDeprecated)

/*  This method is deprecated and should not be used by applications targeting Mac OS X 10.7 or later.
 The implementation of this method will always return 1.0.  Please use -convertRectToBacking: or -backingScaleFactor instead.
 */
- (CGFloat)userSpaceScaleFactor NS_DEPRECATED_MAC(10_4, 10_7, "Use -convertRectToBacking: or -backingScaleFactor instead");

@end

NS_ASSUME_NONNULL_END
