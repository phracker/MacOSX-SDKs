//
//  PKInk.h
//  PencilKit
//
//  Copyright © 2023 Apple Inc. All rights reserved.
//

#import <PencilKit/PKInkType.h>
#import <PencilKit/PKContentVersion.h>

NS_ASSUME_NONNULL_BEGIN

/// PKInk provides a description of how marks on a PKCanvas render and are created.
API_AVAILABLE(ios(14.0), macos(11.0))
NS_SWIFT_SENDABLE
@interface PKInk : NSObject <NSCopying>

/// Create a new ink, specifying its type, color.
///
/// @param type The type of ink.
/// @param color The color of the ink.
#if TARGET_OS_IPHONE
- (instancetype)initWithInkType:(PKInkType)type color:(UIColor *)color NS_DESIGNATED_INITIALIZER;
#else
- (instancetype)initWithInkType:(PKInkType)type color:(NSColor *)color NS_DESIGNATED_INITIALIZER;
#endif

/// The type of ink, eg. pen, pencil...
@property (nonatomic, readonly) PKInkType inkType;

/// The base color of this ink.
#if TARGET_OS_IPHONE
@property (nonatomic, readonly) UIColor *color;
#else
@property (nonatomic, readonly) NSColor *color;
#endif

/// The PencilKit version required to use this ink.
@property (nonatomic, readonly) PKContentVersion requiredContentVersion API_AVAILABLE(ios(17.0), macos(14.0));

@end

NS_ASSUME_NONNULL_END
