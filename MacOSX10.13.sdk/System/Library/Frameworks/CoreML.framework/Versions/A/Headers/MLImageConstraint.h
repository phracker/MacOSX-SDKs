//
//  MLImageConstraint.h
//  CoreML
//
//  Copyright © 2017 Apple Inc. All rights reserved.
//
#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 * MLImageConstraint
 *
 * Constraint on image properties.
 */
API_AVAILABLE(macos(10.13), ios(11.0), watchos(4.0), tvos(11.0))
@interface MLImageConstraint : NSObject

/// The required height of the image
@property (readonly, nonatomic) NSInteger pixelsHigh;

/// The required width of the image
@property (readonly, nonatomic) NSInteger pixelsWide;

/// The accepted kCVPixelFormatType for the image.
@property (readonly, nonatomic) OSType pixelFormatType;

@end

NS_ASSUME_NONNULL_END

