/*
	NSCursor.h
	Application Kit
	Copyright (c) 1994-2009, Apple Inc.
	All rights reserved.
*/

#import <Foundation/NSObject.h>
#import <Foundation/NSGeometry.h>

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
+ (NSCursor *)currentSystemCursor AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;

+ (NSCursor *)arrowCursor;
+ (NSCursor *)IBeamCursor;
+ (NSCursor *)pointingHandCursor AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;
+ (NSCursor *)closedHandCursor AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;
+ (NSCursor *)openHandCursor AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;
+ (NSCursor *)resizeLeftCursor AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;
+ (NSCursor *)resizeRightCursor AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;
+ (NSCursor *)resizeLeftRightCursor AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;
+ (NSCursor *)resizeUpCursor AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;
+ (NSCursor *)resizeDownCursor AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;
+ (NSCursor *)resizeUpDownCursor AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;
+ (NSCursor *)crosshairCursor AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;
+ (NSCursor *)disappearingItemCursor AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;
+ (NSCursor *)operationNotAllowedCursor AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
+ (NSCursor *)dragLinkCursor AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;
+ (NSCursor *)dragCopyCursor AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;
+ (NSCursor *)contextualMenuCursor AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;

- (id)initWithImage:(NSImage *)newImage hotSpot:(NSPoint)aPoint;
- (id)initWithImage:(NSImage *)newImage	foregroundColorHint:(NSColor *)fg backgroundColorHint:(NSColor *)bg hotSpot:(NSPoint)hotSpot;

+ (void)hide;
+ (void)unhide;
+ (void)setHiddenUntilMouseMoves:(BOOL)flag;
+ (void)pop;

- (NSImage *)image;
- (NSPoint)hotSpot;
- (void)push;
- (void)pop;
- (void)set;
- (void)setOnMouseExited:(BOOL)flag;
- (void)setOnMouseEntered:(BOOL)flag;
- (BOOL)isSetOnMouseExited;
- (BOOL)isSetOnMouseEntered;
- (void)mouseEntered:(NSEvent *)theEvent;
- (void)mouseExited:(NSEvent *)theEvent;

@end
