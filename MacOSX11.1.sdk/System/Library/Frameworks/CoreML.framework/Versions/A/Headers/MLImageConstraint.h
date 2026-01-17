//
//  MLImageConstraint.h
//  CoreML
//
//  Copyright © 2017 Apple Inc. All rights reserved.
//
#import <Foundation/Foundation.h>
#import <CoreML/MLImageSizeConstraint.h>
#import <CoreML/MLExport.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 * MLImageConstraint
 *
 * Constraint on image properties.
 */
API_AVAILABLE(macos(10.13), ios(11.0), watchos(4.0), tvos(11.0))
ML_EXPORT
@interface MLImageConstraint : NSObject <NSSecureCoding>

/// The required or default height of the image
@property (readonly, nonatomic) NSInteger pixelsHigh;

/// The required or default width of the image
@property (readonly, nonatomic) NSInteger pixelsWide;

/// The accepted kCVPixelFormatType for the image.
@property (readonly, nonatomic) OSType pixelFormatType;

/// Detailed image size constraint
@property (readonly, nonatomic) MLImageSizeConstraint *sizeConstraint API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0));

// cannot construct object without parameters.
- (instancetype)init NS_UNAVAILABLE NS_SWIFT_UNAVAILABLE("");

@end

NS_ASSUME_NONNULL_END

