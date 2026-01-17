//
//  BEAccessibilityTextMarker.h
//  BrowserEngineKit
//
//  Copyright © 2024 Apple Inc. All rights reserved.
//

#import <BrowserEngineKit/BEMacros.h>
#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/**
 @abstract Subclass BEAccessibilityTextMarker to encode information about text-based positioning information in browser engines within document models.
 */
BROWSERENGINE_EXTERN BROWSERENGINE_ACCESSIBILITY_MARKER_AVAILABILITY
@interface BEAccessibilityTextMarker : NSObject<NSCopying, NSSecureCoding>
@end

/**
 @abstract BEAccessibilityTextMarkerRange holds the start and end markers for a text range.
 */
BROWSERENGINE_EXTERN BROWSERENGINE_ACCESSIBILITY_MARKER_AVAILABILITY
NS_SWIFT_NAME(BEAccessibilityTextMarker.Range)
@interface BEAccessibilityTextMarkerRange : NSObject<NSCopying, NSSecureCoding>
@property (nonatomic, strong) BEAccessibilityTextMarker *startMarker;
@property (nonatomic, strong) BEAccessibilityTextMarker *endMarker;
@end

/**
 @abstract Implement BEAccessibilityTextMarkerSupport to support assistive technology features that rely on granular text offsets.
 */
BROWSERENGINE_EXPORT BROWSERENGINE_ACCESSIBILITY_MARKER_AVAILABILITY
@protocol BEAccessibilityTextMarkerSupport <NSObject>

/**
 @abstract The accessibility frame for a text range.
 @param range The text marker range.
 @return The bounds in accessibility space of the text marker range. If the bounds cannot be determined, return CGRectZero.
 */
- (CGRect)accessibilityBoundsForTextMarkerRange:(BEAccessibilityTextMarkerRange *)range;

/**
 @abstract The accessibility content for a text range.
 @param range The text marker range.
 */
- (nullable NSString *)accessibilityContentForTextMarkerRange:(BEAccessibilityTextMarkerRange *)range;

/**
 @abstract The text marker range of the current selection. Return nil if there is none.
 */
- (nullable BEAccessibilityTextMarkerRange *)accessibilityTextMarkerRangeForCurrentSelection;

/**
 @abstract The text marker range of the current element.
 */
- (BEAccessibilityTextMarkerRange *)accessibilityTextMarkerRange;

/**
 @abstract The text marker after the marker.
 @param marker The text marker.
 */
- (nullable BEAccessibilityTextMarker *)accessibilityNextTextMarker:(BEAccessibilityTextMarker *)marker;

/**
 @abstract The text marker before the marker.
 @param marker The text marker.
 */
- (nullable BEAccessibilityTextMarker *)accessibilityPreviousTextMarker:(BEAccessibilityTextMarker *)marker;

/**
 @abstract The text marker representing the end-of-line position of the line pointed to by the given marker.
 @param marker The text marker.
 */
- (nullable BEAccessibilityTextMarker *)accessibilityLineEndMarkerForMarker:(BEAccessibilityTextMarker *)marker;

/**
 @abstract The text marker representing the start-of-line position of the line pointed to by the given marker.
 @param marker The text marker.
 */
- (nullable BEAccessibilityTextMarker *)accessibilityLineStartMarkerForMarker:(BEAccessibilityTextMarker *)marker;

/**
 @abstract The text marker for the specific point.
 @param point A point in view space.
 */
- (nullable BEAccessibilityTextMarker *)accessibilityMarkerForPoint:(CGPoint)point;

/**
 @abstract The text marker given an index-based position.
 @param position The text position as an index.
 */
- (nullable BEAccessibilityTextMarker *)accessibilityTextMarkerForPosition:(NSInteger)position;

/**
 @abstract The text marker range given an index-based range.
 @param range The text marker range as an NSRange.
 */
- (nullable BEAccessibilityTextMarkerRange *)accessibilityTextMarkerRangeForRange:(NSRange)range;

/**
 @abstract The index-based range given a text marker range.
 @param range The text marker range.
 */
- (NSRange)accessibilityRangeForTextMarkerRange:(BEAccessibilityTextMarkerRange *)range;

@end

NS_ASSUME_NONNULL_END
