/*
	NSCursor.h
	Application Kit
	Copyright (c) 1994-2018, Apple Inc.
	All rights reserved.
*/

#import <Foundation/NSObject.h>
#import <Foundation/NSGeometry.h>
#import <AppKit/NSApplication.h>

NS_ASSUME_NONNULL_BEGIN

@class NSColor, NSEvent, NSImage;

static const NSAppKitVersion NSAppKitVersionNumberWithCursorSizeSupport = 682.0;

@interface NSCursor : NSObject <NSCoding> {
    /*All instance variables are private*/
    NSPoint _hotSpot APPKIT_IVAR;
    struct _cursorFlags {
	unsigned int onMouseExited:1;
	unsigned int onMouseEntered:1;
        unsigned int cursorType:8;
	unsigned int :22;
    } _flags APPKIT_IVAR;
    id _image APPKIT_IVAR;
}

/* Returns the application's current cursor. This is not necessarily the cursor that is currently being displayed on the system. If you need the currently displayed cursor, use currentSystemCursor.
*/
@property (class, readonly, strong) NSCursor *currentCursor;

/* Returns an NSCursor whose image and hot spot match those of the cursor that is currently being displayed on the system, regardless of which application set that cursor. For example, this allows an inactive application to examine the image and hot spot of a cursor set by the active application. This API doesn't care whether the cursor is hidden; it will return an NSCursor whose image matches the cursor you would see if it were visible.
 
 Only the cursor image and hot spot are replicated in the returned NSCursor. Other properties (such as isSetOnMouseExited and isSetOnMouseEntered) will not necessarily be accurate.
 
 This method returns nil if the currently displayed cursor could not be fetched.
 */
@property (class, readonly, nullable, strong) NSCursor *currentSystemCursor NS_AVAILABLE_MAC(10_6);

@property (class, readonly, strong) NSCursor *arrowCursor;
@property (class, readonly, strong) NSCursor *IBeamCursor;
@property (class, readonly, strong) NSCursor *pointingHandCursor;
@property (class, readonly, strong) NSCursor *closedHandCursor;
@property (class, readonly, strong) NSCursor *openHandCursor;
@property (class, readonly, strong) NSCursor *resizeLeftCursor;
@property (class, readonly, strong) NSCursor *resizeRightCursor;
@property (class, readonly, strong) NSCursor *resizeLeftRightCursor;
@property (class, readonly, strong) NSCursor *resizeUpCursor;
@property (class, readonly, strong) NSCursor *resizeDownCursor;
@property (class, readonly, strong) NSCursor *resizeUpDownCursor;
@property (class, readonly, strong) NSCursor *crosshairCursor;
@property (class, readonly, strong) NSCursor *disappearingItemCursor;
@property (class, readonly, strong) NSCursor *operationNotAllowedCursor NS_AVAILABLE_MAC(10_5);
@property (class, readonly, strong) NSCursor *dragLinkCursor NS_AVAILABLE_MAC(10_6);
@property (class, readonly, strong) NSCursor *dragCopyCursor NS_AVAILABLE_MAC(10_6);
@property (class, readonly, strong) NSCursor *contextualMenuCursor NS_AVAILABLE_MAC(10_6);
@property (class, readonly, strong) NSCursor *IBeamCursorForVerticalLayout NS_AVAILABLE_MAC(10_7);

- (instancetype)initWithImage:(NSImage *)newImage hotSpot:(NSPoint)point NS_DESIGNATED_INITIALIZER;
- (instancetype)initWithCoder:(NSCoder *)coder NS_DESIGNATED_INITIALIZER;

- (instancetype)initWithImage:(NSImage *)newImage foregroundColorHint:(nullable NSColor *)fg backgroundColorHint:(nullable NSColor *)bg hotSpot:(NSPoint)hotSpot NS_DEPRECATED_MAC(10_0, 10_12, "Color hints are ignored. Use -initWithImage:hotSpot: instead");

+ (void)hide;
+ (void)unhide;
+ (void)setHiddenUntilMouseMoves:(BOOL)flag;
+ (void)pop;

@property (readonly, strong) NSImage *image;
@property (readonly) NSPoint hotSpot;
- (void)push;
- (void)pop;
- (void)set;
- (void)setOnMouseExited:(BOOL)flag NS_DEPRECATED_MAC(10_0, 10_13, "setOnMouseExited is unused and should not be called");
- (void)setOnMouseEntered:(BOOL)flag NS_DEPRECATED_MAC(10_0, 10_13, "setOnMouseEntered is unused and should not be called");
@property (getter=isSetOnMouseExited, readonly) BOOL setOnMouseExited NS_DEPRECATED_MAC(10_0, 10_13, "isSetOnMouseExited is unused");
@property (getter=isSetOnMouseEntered, readonly) BOOL setOnMouseEntered NS_DEPRECATED_MAC(10_0, 10_13, "isSetOnMouseEntered is unused");
- (void)mouseEntered:(NSEvent *)event NS_DEPRECATED_MAC(10_0, 10_13, "mouseEntered: is unused and should not be called");
- (void)mouseExited:(NSEvent *)event NS_DEPRECATED_MAC(10_0, 10_13, "mouseExited: is unused and should not be called");

@end

NS_ASSUME_NONNULL_END
