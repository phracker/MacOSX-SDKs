//
//  TCControlLayout.h
//  TouchController
//

#if !TARGET_OS_OSX
#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/// Defines the anchor point for a control.
typedef NS_ENUM(NSInteger, TCControlLayoutAnchor) {
    /// Anchors to the top-left corner, relative to the screen size.
    TCControlLayoutAnchorTopLeft,
    /// Anchors to the top-center, relative to the screen size.
    TCControlLayoutAnchorTopCenter,
    /// Anchors to the top-right corner, relative to the screen size.
    TCControlLayoutAnchorTopRight,
    /// Anchors to the center-left, relative to the screen size.
    TCControlLayoutAnchorCenterLeft,
    /// Anchors to the center, relative to the screen size.
    TCControlLayoutAnchorCenter,
    /// Anchors to the center-right, relative to the screen size.
    TCControlLayoutAnchorCenterRight,
    /// Anchors to the bottom-left corner, relative to the screen size.
    TCControlLayoutAnchorBottomLeft,
    /// Anchors to the bottom-center, relative to the screen size.
    TCControlLayoutAnchorBottomCenter,
    /// Anchors to the bottom-right corner, relative to the screen size.
    TCControlLayoutAnchorBottomRight,
} API_AVAILABLE(ios(26.0)) API_UNAVAILABLE(macCatalyst, visionos);

/// Defines the coodinate system for an anchor point.
typedef NS_ENUM(NSInteger, TCControlLayoutAnchorCoordinateSystem) {
    /// Anchors are positioned relative to the device's screen size.
    /// - On larger devices, the coordinate system is shrunk for easier handling.
    /// - On smaller devices, this is equivalent to `TCControlLayoutAnchorCoordinateSystemAbsolute`.
    TCControlLayoutAnchorCoordinateSystemRelative,
    /// Anchors are positioned according to the absolute edges of the sceren.
    TCControlLayoutAnchorCoordinateSystemAbsolute,
} API_AVAILABLE(ios(26.0)) API_UNAVAILABLE(macCatalyst, visionos);

/// A protocol defining the controlLayout properties for a control.
API_AVAILABLE(ios(26.0)) API_UNAVAILABLE(macCatalyst, visionos)
@protocol TCControlLayout <NSObject>

@required

/// The anchor point of the control.
@property (nonatomic, assign) TCControlLayoutAnchor anchor;
/// The coordinate system for the control's anchor point.
@property (nonatomic, assign) TCControlLayoutAnchorCoordinateSystem anchorCoordinateSystem;
/// The offset from the anchor point.
@property (nonatomic, assign) CGPoint offset;
/// The z-index of the controlLayout, used for z-ordering.
@property (nonatomic, assign) NSInteger zIndex;
/// The size of the control in points.
@property (nonatomic, assign) CGSize size;

/// The calculated position of the control.
@property (nonatomic, assign, readonly) CGPoint position;

@end

NS_ASSUME_NONNULL_END
#endif
