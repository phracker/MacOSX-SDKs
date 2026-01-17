#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIFoundation/NSTextRange.h>)
//
//  NSTextRange.h
//  Text Kit
//
//  Copyright (c) 2018-2025, Apple Inc. All rights reserved.
//

#import <Foundation/NSObject.h>

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

#pragma mark NSTextLocation
// NSTextLocation represents an abstract location inside document contents. A concrete class conforming to the protocol should be associated with a particular document backing store type. The interpretation of a location in enumeration operations is depending on the logical direction. When enumerating forward, it should start with the item containing the location. The enumeration should start with an item preceding the location for reverse operations.
API_AVAILABLE(macos(12.0), ios(15.0), tvos(15.0), watchos(8.0), visionos(1.0)) NS_PROTOCOL_REQUIRES_EXPLICIT_IMPLEMENTATION
@protocol NSTextLocation <NSObject>

// Compares and returns the logical ordering to location
- (NSComparisonResult)compare:(id <NSTextLocation>)location API_AVAILABLE(macos(12.0), ios(15.0), tvos(15.0), watchos(8.0), visionos(1.0));
@end

#pragma mark NSTextRange
/// A class that represents a contiguous range between two locations inside document contents.
///
/// An `NSTextRange` consists of the starting and terminating locations. There
/// the two basic properties: ``location`` and ``endLocation``, respectively.
/// The terminating ``location``, ``endLocation``, is directly following the
/// last location in the range. For example, a location contains a range if
/// `(range.location <= location) && (location < range.endLocation)` is `true`.
API_AVAILABLE(macos(12.0), ios(15.0), tvos(15.0), watchos(8.0), visionos(1.0))
@interface NSTextRange : NSObject
#pragma mark Initialization
// Returns an empty range when endLocation=nil
/// Creates a new text range with the starting and ending locations you specify.
///
/// - Parameters:
///   - location: The starting location.
///   - endLocation: The ending location.
- (nullable instancetype)initWithLocation:(id <NSTextLocation>)location endLocation:(nullable id <NSTextLocation>)endLocation NS_DESIGNATED_INITIALIZER;

/// Creates a new text range at the location you specify.
///
/// - Parameters:
///   - location: An ``NSTextLocation``.
- (instancetype)initWithLocation:(id <NSTextLocation>)location;

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

#pragma mark Basic properties
/// Returns whether the text range is empty.
@property (readonly, getter=isEmpty) BOOL empty;

/// The starting location of the text range.
@property (strong, readonly) id <NSTextLocation> location;
/// The ending location of the text range.
@property (strong, readonly) id <NSTextLocation> endLocation;

/// Compares two text ranges.
///
/// - Parameters:
///   - textRange: The range used to compare against the current range to evaluate for differences.
///
/// - Returns: Returns `true` if the ranges are equal.
- (BOOL)isEqualToTextRange:(NSTextRange *)textRange;

#pragma mark Basic operations
/// Determines if the text location you specify is in the current text range.
///
/// - Parameters:
///   - location: An ``NSTextLocation``.
///
/// - Returns: Returns `true` if the location is in the range otherwise `false` .
- (BOOL)containsLocation:(id <NSTextLocation>)location;

/// Determines if the text range you specify is in the current text range.
///
/// - Parameters:
///   - textRange: An ``NSTextRange``.
///
/// - Returns: Returns `true` if the range you provide is in the current range; otherwise `false`.
- (BOOL)containsRange:(NSTextRange *)textRange;

/// Determines if two ranges intersect.
///
/// - Parameters:
///   - textRange: The range used to compare against the current range to evaluate for differences.
///
/// - Returns: Returns `true` if the ranges intersect.
- (BOOL)intersectsWithTextRange:(NSTextRange *)textRange;

#pragma mark Basic mutations
/// Returns the range, if any, where two text ranges intersect.
///
/// - Parameters:
///   - textRange: The range used to compare against the current range to evaluate for differences.
///
/// - Returns: An
///   <doc://com.apple.documentation/documentation/foundation/nsrange> that
///   represents the intersection of the ranges, or `nil` if they don't
///   intersect.
- (nullable instancetype)textRangeByIntersectingWithTextRange:(NSTextRange *)textRange;

/// Returns a new text range by forming the union with the text range you provide.
///
/// - Parameters:
///   - textRange: The range to use to create the union.
///
/// - Returns: An ``NSTextRange`` that represent the union of the two ranges.
- (instancetype)textRangeByFormingUnionWithTextRange:(NSTextRange *)textRange;
@end


NS_HEADER_AUDIT_END(nullability, sendability)
#else
#import <UIFoundation/NSTextRange.h>
#endif
