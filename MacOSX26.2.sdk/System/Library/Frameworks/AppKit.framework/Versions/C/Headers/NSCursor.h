/*
	NSCursor.h
	Application Kit
	Copyright (c) 1994-2024, Apple Inc.
	All rights reserved.
*/

#import <Foundation/NSObject.h>
#import <Foundation/NSGeometry.h>
#import <AppKit/AppKitDefines.h>
#import <AppKit/NSApplication.h>
#import <AppKit/NSDirection.h>

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

@class NSColor, NSEvent, NSImage;
#if TARGET_OS_IPHONE
@class UIImage;
#endif

API_AVAILABLE(macos(10.0), ios(13.0))
@interface NSCursor : NSObject <NSSecureCoding>

// MARK: - Initializing a New Cursor

#if !TARGET_OS_IPHONE
- (instancetype)initWithImage:(NSImage *)newImage hotSpot:(NSPoint)point NS_DESIGNATED_INITIALIZER;
#else
- (instancetype)initWithImage:(UIImage *)newImage hotSpot:(NSPoint)point NS_DESIGNATED_INITIALIZER;
#endif
- (instancetype)initWithCoder:(NSCoder *)coder NS_DESIGNATED_INITIALIZER;

// MARK: - Setting Cursor Attributes

#if !TARGET_OS_IPHONE
@property (readonly, strong) NSImage *image;
#else
@property (readonly, strong) UIImage *image;
#endif
@property (readonly) NSPoint hotSpot;

// MARK: - Controlling Which Cursor Is Current

+ (void)hide;
+ (void)unhide;
+ (void)setHiddenUntilMouseMoves:(BOOL)flag;
+ (void)pop;
- (void)pop;
- (void)push;
- (void)set;

// MARK: - Retrieving Cursor Instances

/// Returns the application’s current cursor.
/// - Note: This isn’t necessarily the cursor that is currently being displayed, as the system may be showing the cursor for another running application.
@property (class, readonly, strong) NSCursor *currentCursor;

/// Returns the default cursor, the arrow cursor.
/// - Discussion: The default cursor, a slanted arrow with its hot spot at the tip. The arrow cursor is the one you’re used to seeing over buttons, scrollers, and many other objects in the window system.
@property (class, readonly, strong) NSCursor *arrowCursor;

@property (class, readonly, strong) NSCursor *crosshairCursor;
@property (class, readonly, strong) NSCursor *disappearingItemCursor;
@property (class, readonly, strong) NSCursor *operationNotAllowedCursor API_AVAILABLE(macos(10.5));
@property (class, readonly, strong) NSCursor *dragLinkCursor API_AVAILABLE(macos(10.6));
@property (class, readonly, strong) NSCursor *dragCopyCursor API_AVAILABLE(macos(10.6));
@property (class, readonly, strong) NSCursor *contextualMenuCursor API_AVAILABLE(macos(10.6));

// MARK: Hand Cursors

@property (class, readonly, strong) NSCursor *pointingHandCursor;
@property (class, readonly, strong) NSCursor *closedHandCursor;
@property (class, readonly, strong) NSCursor *openHandCursor;

// MARK: I-Beam Cursors

@property (class, readonly, strong) NSCursor *IBeamCursor;
@property (class, readonly, strong) NSCursor *IBeamCursorForVerticalLayout API_AVAILABLE(macos(10.7));

// MARK: Zoom Cursors

/// Returns the zoom-in cursor.
/// - Note: This cursor is used to indicate zooming in on (magnifying) a canvas or object.
@property (class, readonly, strong) NSCursor *zoomInCursor API_AVAILABLE(macos(15.0));

/// Returns the zoom-out cursor.
/// - Note: This cursor is used to indicate zooming out of a canvas or object.
@property (class, readonly, strong) NSCursor *zoomOutCursor API_AVAILABLE(macos(15.0));

// MARK: Column Resize Cursors

/// Returns the cursor for resizing a column (vertical divider) in either direction.
@property (class, readonly, strong) NSCursor *columnResizeCursor NS_SWIFT_NAME(columnResize) API_AVAILABLE(macos(15.0));

/// Returns the cursor for resizing a column (vertical divider) in the specified directions.
/// - Parameter directions: The direction in which a column can be resized.
+ (NSCursor *)columnResizeCursorInDirections:(NSHorizontalDirections)directions NS_REFINED_FOR_SWIFT API_AVAILABLE(macos(15.0));

// MARK: Row Resize Cursors

/// Returns the cursor for resizing a row (horizontal divider) in either direction.
@property (class, readonly, strong) NSCursor *rowResizeCursor NS_SWIFT_NAME(rowResize) API_AVAILABLE(macos(15.0));

/// Returns the cursor for resizing a row (horizontal divider) in the specified directions.
/// - Parameter directions: The direction in which a row can be resized.
+ (NSCursor *)rowResizeCursorInDirections:(NSVerticalDirections)directions NS_REFINED_FOR_SWIFT API_AVAILABLE(macos(15.0));

// MARK: Frame Resize Cursors

/// The position along the perimeter of a rectangular frame (its edges and corners) from which it’s resized.
typedef NS_CLOSED_ENUM(NSUInteger, NSCursorFrameResizePosition) {
    /// The top edge of the frame.
    NSCursorFrameResizePositionTop = (1 << 0),
    /// The left edge of the frame.
    NSCursorFrameResizePositionLeft = (1 << 1),
    /// The bottom edge of the frame.
    NSCursorFrameResizePositionBottom = (1 << 2),
    /// The right edge of the frame.
    NSCursorFrameResizePositionRight = (1 << 3),
    /// The top left corner of the frame.
    NSCursorFrameResizePositionTopLeft = (NSCursorFrameResizePositionTop | NSCursorFrameResizePositionLeft),
    /// The top right corner of the frame.
    NSCursorFrameResizePositionTopRight = (NSCursorFrameResizePositionTop | NSCursorFrameResizePositionRight),
    /// The bottom left corner of the frame.
    NSCursorFrameResizePositionBottomLeft = (NSCursorFrameResizePositionBottom | NSCursorFrameResizePositionLeft),
    /// The bottom right corner of the frame.
    NSCursorFrameResizePositionBottomRight = (NSCursorFrameResizePositionBottom | NSCursorFrameResizePositionRight),
} NS_SWIFT_NAME(NSCursor.FrameResizePosition) API_AVAILABLE(macos(15.0));

/// The directions in which a rectangular frame can be resized.
typedef NS_OPTIONS(NSUInteger, NSCursorFrameResizeDirections) {
    /// Indicates that the shape can be resized inwards to be smaller.
    NSCursorFrameResizeDirectionsInward = (1 << 0),
    /// Indicates that the shape can be resized outwards to be larger.
    NSCursorFrameResizeDirectionsOutward = (1 << 1),
    /// Indicates that the shape can be resized inwards or wards to be either smaller or larger, respectively.
    NSCursorFrameResizeDirectionsAll = (NSCursorFrameResizeDirectionsInward | NSCursorFrameResizeDirectionsOutward),
} NS_REFINED_FOR_SWIFT API_AVAILABLE(macos(15.0));

/// Returns the cursor for resizing a rectangular frame from the specified edge or corner.
/// - Parameters:
///   - position: The position along the perimeter of a rectangular frame (its edges and corners) from which it’s resized.
///   - directions: The directions in which a rectangular frame can be resized.
+ (NSCursor *)frameResizeCursorFromPosition:(NSCursorFrameResizePosition)position inDirections:(NSCursorFrameResizeDirections)directions NS_REFINED_FOR_SWIFT API_AVAILABLE(macos(15.0));

@end

// MARK: - Deprecated

APPKIT_API_UNAVAILABLE_BEGIN_MACCATALYST
static const NSAppKitVersion NSAppKitVersionNumberWithCursorSizeSupport = 682.0;
API_UNAVAILABLE_END

@interface NSCursor (Deprecated)
/// This property will always be `nil` in a future version of macOS.
@property (class, readonly, nullable, strong) NSCursor *currentSystemCursor API_DEPRECATED("No longer recommended. Use ScreenCaptureKit to capture the screen. Use the `showsCursor` property on `SCStreamConfiguration` to control whether or not to include the cursor in the capture. Or, use `NSCursor.currentCursor` if needing to just get the current cursor for this application.", macos(10.6, API_TO_BE_DEPRECATED));
@property (class, readonly, strong) NSCursor *resizeLeftCursor API_DEPRECATED("Use either `+[NSCursor columnResizeCursorInDirections:]` or `+[NSCursor frameResizeCursorFromPosition:inDirections:]` instead, depending on whether a divider is being re-positioned or a rectangular frame is being resized.", macos(10.0, API_TO_BE_DEPRECATED));
@property (class, readonly, strong) NSCursor *resizeRightCursor API_DEPRECATED("Use either `+[NSCursor columnResizeCursorInDirections:]` or `+[NSCursor frameResizeCursorFromPosition:inDirections:]` instead, depending on whether a divider is being re-positioned or a rectangular frame is being resized.", macos(10.0, API_TO_BE_DEPRECATED));
@property (class, readonly, strong) NSCursor *resizeLeftRightCursor API_DEPRECATED("Use either `+[NSCursor columnResizeCursorInDirections:]` or `+[NSCursor frameResizeCursorFromPosition:inDirections:]` instead, depending on whether a divider is being re-positioned or a rectangular frame is being resized.", macos(10.0, API_TO_BE_DEPRECATED));
@property (class, readonly, strong) NSCursor *resizeUpCursor API_DEPRECATED("Use either `+[NSCursor rowResizeCursorInDirections:]` or `+[NSCursor frameResizeCursorFromPosition:inDirections:]` instead, depending on whether a divider is being re-positioned or a rectangular frame is being resized.", macos(10.0, API_TO_BE_DEPRECATED));
@property (class, readonly, strong) NSCursor *resizeDownCursor API_DEPRECATED("Use either `+[NSCursor rowResizeCursorInDirections:]` or `+[NSCursor frameResizeCursorFromPosition:inDirections:]` instead, depending on whether a divider is being re-positioned or a rectangular frame is being resized.", macos(10.0, API_TO_BE_DEPRECATED));
@property (class, readonly, strong) NSCursor *resizeUpDownCursor API_DEPRECATED("Use either `+[NSCursor rowResizeCursorInDirections:]` or `+[NSCursor frameResizeCursorFromPosition:inDirections:]` instead, depending on whether a divider is being re-positioned or a rectangular frame is being resized.", macos(10.0, API_TO_BE_DEPRECATED));
@end

APPKIT_API_UNAVAILABLE_BEGIN_MACCATALYST
@interface NSCursor (NSDeprecated)
- (instancetype)initWithImage:(NSImage *)newImage foregroundColorHint:(nullable NSColor *)fg backgroundColorHint:(nullable NSColor *)bg hotSpot:(NSPoint)hotSpot API_DEPRECATED("Color hints are ignored. Use -initWithImage:hotSpot: instead", macos(10.0,10.12));
- (void)setOnMouseExited:(BOOL)flag API_DEPRECATED("setOnMouseExited is unused and should not be called", macos(10.0,10.13));
- (void)setOnMouseEntered:(BOOL)flag API_DEPRECATED("setOnMouseEntered is unused and should not be called", macos(10.0,10.13));
@property (getter=isSetOnMouseExited, readonly) BOOL setOnMouseExited API_DEPRECATED("isSetOnMouseExited is unused", macos(10.0,10.13));
@property (getter=isSetOnMouseEntered, readonly) BOOL setOnMouseEntered API_DEPRECATED("isSetOnMouseEntered is unused", macos(10.0,10.13));
- (void)mouseEntered:(NSEvent *)event API_DEPRECATED("mouseEntered: is unused and should not be called", macos(10.0,10.13));
- (void)mouseExited:(NSEvent *)event API_DEPRECATED("mouseExited: is unused and should not be called", macos(10.0,10.13));
@end
API_UNAVAILABLE_END

NS_HEADER_AUDIT_END(nullability, sendability)
