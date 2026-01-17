/*
        NSGraphicsContext.h
        Application Kit
        Copyright (c) 1997-2004, Apple Computer, Inc.
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

typedef enum NSImageInterpolation {
   NSImageInterpolationDefault,
   NSImageInterpolationNone,
   NSImageInterpolationLow,
   NSImageInterpolationHigh
} NSImageInterpolation;

@interface NSGraphicsContext : NSObject {
}

// Instantiates from an appropriate concrete subclass depending on NSGraphicsContextDestinationAttributeName attribute
+ (NSGraphicsContext *)graphicsContextWithAttributes:(NSDictionary *)attributes;

// Convenience cover method for [NSGraphicsContext graphicsContextWithAttributes:[NSDictionary dictionaryWithObject:<NSWindow instance> forKey:NSGraphicsContextDestinationAttributeName]]
+ (NSGraphicsContext *)graphicsContextWithWindow:(NSWindow *)window;

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_4
/* Convenience cover method for [NSGraphicsContext graphicsContextWithAttributes:[NSDictionary dictionaryWithObject:<NSBitmapImageRep instance> forKey:NSGraphicsContextDestinationAttributeName]]. Only NSBitmapImageRep instances with isPlanar == NO are supported.
*/
+ (NSGraphicsContext *)graphicsContextWithBitmapImageRep:(NSBitmapImageRep *)bitmapRep;

/* Instantiates from an arbitrary graphicsPort (usually CGContextRef).  initialFlippedState is used to determine the return value from -isFlipped when no view is focused in the context.
*/
+ (NSGraphicsContext *)graphicsContextWithGraphicsPort:(void *)graphicsPort flipped:(BOOL)initialFlippedState;
#endif /* MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_4 */

// Setting and identifying the current context in the thread
+ (NSGraphicsContext *)currentContext;
+ (void)setCurrentContext:(NSGraphicsContext *)context;

// Convenience cover method for [[NSGraphicsContext currentContext] isDrawingToScreen]
+ (BOOL)currentContextDrawingToScreen;

// Graphics state controls
// Calls -saveGraphicsContext, and pushes the current context on per-thread stack. It's functional equivalent of PSgsave
+ (void)saveGraphicsState;
// Pops a context from per-thread stack, makes it current, and calls -resotreGraphicsContext. It's functional equivalent of PSgrestore
+ (void)restoreGraphicsState;
// Makes gState's context current, and resets graphics state. The gState must be created in the calling thread
+ (void)setGraphicsState:(int)gState;

// Returns attributes used to create this instance
- (NSDictionary *)attributes;

// Testing the drawing destination
- (BOOL)isDrawingToScreen;

// Controlling the context
- (void)saveGraphicsState;
- (void)restoreGraphicsState;

- (void)flushGraphics;

// Focus Stack support (abstract)
- (void *)focusStack;
- (void)setFocusStack:(void *)stack;

// Platform specific drawing context (usually CGContextRef)
- (void *)graphicsPort;

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_4
/* Returns the flip state of the receiver.  The state is determined by messaging -isFlipped to the focus view in the context.  If no view has focus, returns NO unless the receiver is instantiated via graphicsContextWithGraphicsPort:drawingToScreen:flipped: with initialFlippedState == YES.
*/
- (BOOL)isFlipped;
#endif /* MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_4 */
@end

@interface NSGraphicsContext(NSGraphicsContext_RenderingOptions)

- (void)setShouldAntialias:(BOOL)antialias;
- (BOOL)shouldAntialias;
- (void)setImageInterpolation:(NSImageInterpolation)interpolation;
- (NSImageInterpolation)imageInterpolation;

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_2
- (void)setPatternPhase:(NSPoint)phase;
- (NSPoint)patternPhase;
#endif
#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_4
- (void)setCompositingOperation:(NSCompositingOperation)operation;
- (NSCompositingOperation)compositingOperation;
#endif /* MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_4 */
@end

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_4
@class CIContext;
@interface NSGraphicsContext (NSQuartzCoreAdditions)
- (CIContext *)CIContext;
@end
#endif /* MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_4 */
