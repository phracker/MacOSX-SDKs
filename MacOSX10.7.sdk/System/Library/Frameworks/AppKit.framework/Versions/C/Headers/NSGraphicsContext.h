/*
        NSGraphicsContext.h
        Application Kit
        Copyright (c) 1997-2011, Apple Inc.
        All rights reserved.
*/

#import <AppKit/AppKitDefines.h>
#import <AppKit/NSGraphics.h>
#import <Foundation/NSGeometry.h>
#import <Foundation/NSObject.h>

@class NSDictionary;
@class NSString;
@class NSWindow;
@class NSBitmapImageRep;

/* Attributes that can be passed to graphicsContextWithAttributes: method */
APPKIT_EXTERN NSString *NSGraphicsContextDestinationAttributeName; // Can be an instance of NSWindow, NSMutableData, NSBitmapImageRep, or NSURL.

// Attributes for NSMutableData or NSURL destinations
APPKIT_EXTERN NSString *NSGraphicsContextRepresentationFormatAttributeName; // Specifies destination file format

// Supported file format
APPKIT_EXTERN NSString *NSGraphicsContextPSFormat;
APPKIT_EXTERN NSString *NSGraphicsContextPDFFormat;

enum {
   NSImageInterpolationDefault = 0,
   NSImageInterpolationNone = 1,
   NSImageInterpolationLow = 2, /* Low quality, fast interpolation. */
#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_6
   NSImageInterpolationMedium = 4, /* Medium quality, slower than NSImageInterpolationLow. */
#endif
   NSImageInterpolationHigh = 3 /* Highest quality, slower than NSImageInterpolationMedium. */
};
typedef NSUInteger NSImageInterpolation;

@interface NSGraphicsContext : NSObject {
}

// Instantiates from an appropriate concrete subclass depending on NSGraphicsContextDestinationAttributeName attribute
+ (NSGraphicsContext *)graphicsContextWithAttributes:(NSDictionary *)attributes;

// Convenience cover method for [NSGraphicsContext graphicsContextWithAttributes:[NSDictionary dictionaryWithObject:<NSWindow instance> forKey:NSGraphicsContextDestinationAttributeName]]
+ (NSGraphicsContext *)graphicsContextWithWindow:(NSWindow *)window;

/* Convenience cover method for [NSGraphicsContext graphicsContextWithAttributes:[NSDictionary dictionaryWithObject:<NSBitmapImageRep instance> forKey:NSGraphicsContextDestinationAttributeName]]. Only NSBitmapImageRep instances with isPlanar == NO are supported.
*/
+ (NSGraphicsContext *)graphicsContextWithBitmapImageRep:(NSBitmapImageRep *)bitmapRep;

/* Instantiates from an arbitrary graphicsPort (usually CGContextRef).  initialFlippedState is used to determine the return value from -isFlipped when no view is focused in the context.
*/
+ (NSGraphicsContext *)graphicsContextWithGraphicsPort:(void *)graphicsPort flipped:(BOOL)initialFlippedState;

// Setting and identifying the current context in the thread
+ (NSGraphicsContext *)currentContext;
+ (void)setCurrentContext:(NSGraphicsContext *)context;

// Convenience cover method for [[NSGraphicsContext currentContext] isDrawingToScreen]
+ (BOOL)currentContextDrawingToScreen;

// Graphics state controls
// Calls -saveGraphicsContext, and pushes the current context on per-thread stack. It's functional equivalent of PSgsave
+ (void)saveGraphicsState;
// Pops a context from per-thread stack, makes it current, and calls -restoreGraphicsContext. It's functional equivalent of PSgrestore
+ (void)restoreGraphicsState;
// Makes gState's context current, and resets graphics state. The gState must be created in the calling thread
+ (void)setGraphicsState:(NSInteger)gState;

// Returns attributes used to create this instance
- (NSDictionary *)attributes;

// Testing the drawing destination
- (BOOL)isDrawingToScreen;

// Controlling the context
- (void)saveGraphicsState;
- (void)restoreGraphicsState;

- (void)flushGraphics;

// Platform specific drawing context (usually CGContextRef)
- (void *)graphicsPort;

/* Returns the flip state of the receiver.  The state is determined by messaging -isFlipped to the focus view in the context.  If no view has focus, returns NO unless the receiver is instantiated via graphicsContextWithGraphicsPort:drawingToScreen:flipped: with initialFlippedState == YES.
*/
- (BOOL)isFlipped;
@end

@interface NSGraphicsContext(NSGraphicsContext_RenderingOptions)

- (void)setShouldAntialias:(BOOL)antialias;
- (BOOL)shouldAntialias;
- (void)setImageInterpolation:(NSImageInterpolation)interpolation;
- (NSImageInterpolation)imageInterpolation;

- (void)setPatternPhase:(NSPoint)phase;
- (NSPoint)patternPhase;
- (void)setCompositingOperation:(NSCompositingOperation)operation;
- (NSCompositingOperation)compositingOperation;
- (NSColorRenderingIntent)colorRenderingIntent NS_AVAILABLE_MAC(10_5);
- (void)setColorRenderingIntent:(NSColorRenderingIntent)renderingIntent NS_AVAILABLE_MAC(10_5);
@end

@class CIContext;
@interface NSGraphicsContext (NSQuartzCoreAdditions)
- (CIContext *)CIContext;
@end

/********* Deprecated API *********/
// The remaining portion is deprecated on Mac OS X 10.6 and Later.
#if MAC_OS_X_VERSION_MIN_REQUIRED < MAC_OS_X_VERSION_10_6
@interface NSGraphicsContext (NSGraphicsContextDeprecated)
- (id)focusStack;
- (void)setFocusStack:(id)stack;
@end
#endif /* MAC_OS_X_VERSION_MIN_REQUIRED <= MAC_OS_X_VERSION_10_6 */
