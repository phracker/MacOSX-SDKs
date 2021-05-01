//
//  PKInk.h
//  PencilKit
//
//  Copyright © 2020 Apple. All rights reserved.
//

#import <PencilKit/PKInkType.h>


NS_ASSUME_NONNULL_BEGIN

/// PKInk provides a description of how marks on a PKCanvas render and are created.
NS_REFINED_FOR_SWIFT
API_AVAILABLE(ios(14.0), macos(11.0))
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

@end

NS_ASSUME_NONNULL_END
