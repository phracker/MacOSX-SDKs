/*
	NSCursor.h
	Application Kit
	Copyright (c) 1994-2015, Apple Inc.
	All rights reserved.
*/

#import <Foundation/NSObject.h>
#import <Foundation/NSGeometry.h>

NS_ASSUME_NONNULL_BEGIN

@class NSColor, NSEvent, NSImage;

#define NSAppKitVersionNumberWithCursorSizeSupport 682.0

@interface NSCursor : NSObject <NSCoding> {
    /*All instance variables are private*/
    NSPoint _hotSpot;
    struct _cursorFlags {
	unsigned int onMouseExited:1;
	unsigned int onMouseEntered:1;
        unsigned int cursorType:8;
	unsigned int :22;
    } _flags;
    id _image;
}

/* Returns the application's current cursor. This is not necessarily the cursor that is currently being displayed on the system. If you need the currently displayed cursor, use currentSystemCursor.
*/
+ (NSCursor *)currentCursor;

/* Returns an NSCursor whose image and hot spot match those of the cursor that is currently being displayed on the system, regardless of which application set that cursor. For example, this allows an inactive application to examine the image and hot spot of a cursor set by the active application. This API doesn't care whether the cursor is hidden; it will return an NSCursor whose image matches the cursor you would see if it were visible.
 
 Only the cursor image and hot spot are replicated in the returned NSCursor. Other properties (such as isSetOnMouseExited and isSetOnMouseEntered) will not necessarily be accurate.
 
 This method returns nil if the currently displayed cursor could not be fetched.
 */
+ (nullable NSCursor *)currentSystemCursor NS_AVAILABLE_MAC(10_6);

+ (NSCursor *)arrowCursor;
+ (NSCursor *)IBeamCursor;
+ (NSCursor *)pointingHandCursor;
+ (NSCursor *)closedHandCursor;
+ (NSCursor *)openHandCursor;
+ (NSCursor *)resizeLeftCursor;
+ (NSCursor *)resizeRightCursor;
+ (NSCursor *)resizeLeftRightCursor;
+ (NSCursor *)resizeUpCursor;
+ (NSCursor *)resizeDownCursor;
+ (NSCursor *)resizeUpDownCursor;
+ (NSCursor *)crosshairCursor;
+ (NSCursor *)disappearingItemCursor;
+ (NSCursor *)operationNotAllowedCursor NS_AVAILABLE_MAC(10_5);
+ (NSCursor *)dragLinkCursor NS_AVAILABLE_MAC(10_6);
+ (NSCursor *)dragCopyCursor NS_AVAILABLE_MAC(10_6);
+ (NSCursor *)contextualMenuCursor NS_AVAILABLE_MAC(10_6);
+ (NSCursor *)IBeamCursorForVerticalLayout NS_AVAILABLE_MAC(10_7);

- (instancetype)initWithImage:(NSImage *)newImage hotSpot:(NSPoint)aPoint;
- (instancetype)initWithImage:(NSImage *)newImage	foregroundColorHint:(nullable NSColor *)fg backgroundColorHint:(nullable NSColor *)bg hotSpot:(NSPoint)hotSpot;

+ (void)hide;
+ (void)unhide;
+ (void)setHiddenUntilMouseMoves:(BOOL)flag;
+ (void)pop;

@property (readonly, strong) NSImage *image;
@property (readonly) NSPoint hotSpot;
- (void)push;
- (void)pop;
- (void)set;
- (void)setOnMouseExited:(BOOL)flag;
- (void)setOnMouseEntered:(BOOL)flag;
@property (getter=isSetOnMouseExited, readonly) BOOL setOnMouseExited;
@property (getter=isSetOnMouseEntered, readonly) BOOL setOnMouseEntered;
- (void)mouseEntered:(NSEvent *)theEvent;
- (void)mouseExited:(NSEvent *)theEvent;

@end

NS_ASSUME_NONNULL_END
