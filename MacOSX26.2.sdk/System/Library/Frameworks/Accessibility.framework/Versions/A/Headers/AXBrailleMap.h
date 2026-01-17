//
//  AXBrailleMap.h
//  Accessibility
//
//  Copyright © 2021 Apple Inc. All rights reserved.
//

#import <Accessibility/AXFoundation.h>

NS_ASSUME_NONNULL_BEGIN

/* An AXBrailleMap object represents a connected two-dimensional braille display.
   A display is comprised of a grid of pins that can be raised and lowered.
   This is useful for representing graphics, images, and other visual data to VoiceOver users.
 */
AX_EXTERN API_AVAILABLE(ios(15.2), tvos(15.2), watchos(8.2), macos(12.1))
@interface AXBrailleMap : NSObject <NSCopying, NSSecureCoding>

// Indicates the number of dots in each dimension. This size may change if the user zooms in the content.
@property (nonatomic, readonly) CGSize dimensions;

// These methods provide individual access to braille dots.
// 1 indicates completely raised, 0 completely lowered.
// The bottom, left is represented by { 0,0 }.
// The top, right is represented by { dimensions.width - 1, dimensions.height - 1}
- (void)setHeight:(float)status atPoint:(CGPoint)point;
- (float)heightAtPoint:(CGPoint)point;

- (void)presentImage:(CGImageRef)image;

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

AX_EXTERN
// Implement one of the following methods in order to provide data for a braille map to be rendered.
@protocol AXBrailleMapRenderer <NSObject>

@optional
// If the element displays a region that should be rendered into the braille map automatically,
// specify it here (relative to the bounds of the object). VoiceOver will snapshot that region of the element
// and convert to a braille map internally.
@property (nonatomic, assign) CGRect accessibilityBrailleMapRenderRegion API_AVAILABLE(ios(15.2), tvos(15.2), watchos(8.2), macos(12.1));

// This handler is called to ask the element to update the values of the braille map on-demand.
@property (nonatomic, copy) void (^accessibilityBrailleMapRenderer)(AXBrailleMap *map)  API_AVAILABLE(ios(15.2), tvos(15.2), watchos(8.2), macos(12.1));

@end

NS_ASSUME_NONNULL_END
