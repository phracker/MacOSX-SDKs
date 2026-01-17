//
//  CLKFullColorImageProvider.h
//  ClockKit
//
//  Copyright © 2018 Apple Inc. All rights reserved.
//

#import <UIKit/UIImage.h>
#import <ClockKit/CLKDefines.h>
#import <ClockKit/CLKImageProvider.h>

NS_ASSUME_NONNULL_BEGIN

API_DEPRECATED("On watchOS 9.0 or later, use WidgetKit instead", watchos(5.0, API_TO_BE_DEPRECATED)) API_UNAVAILABLE(ios)
@interface CLKFullColorImageProvider : NSObject <NSCopying>

- (instancetype)init API_DEPRECATED("Use initializers that take parameters.", watchos(2.0, 7.0), ios(9.0, 14.0));
+ (instancetype)new API_DEPRECATED("Use factory methods that take parameters.", watchos(2.0, 7.0), ios(9.0, 14.0));

- (instancetype)initWithFullColorImage:(UIImage *)image API_AVAILABLE(watchos(7.0)) API_UNAVAILABLE(ios) NS_SWIFT_UNAVAILABLE("Use class factory");
- (instancetype)initWithFullColorImage:(UIImage *)image
                   tintedImageProvider:(CLKImageProvider * _Nullable)tintedImageProvider API_AVAILABLE(watchos(7.0)) API_UNAVAILABLE(ios) NS_SWIFT_UNAVAILABLE("Use class factory");


+ (instancetype)providerWithFullColorImage:(UIImage *)image;
+ (instancetype)providerWithFullColorImage:(UIImage *)image
                       tintedImageProvider:(CLKImageProvider * _Nullable)tintedImageProvider API_AVAILABLE(watchos(6.0)) API_UNAVAILABLE(ios);

@property (nonatomic, retain) UIImage *image;
/// Optional image provider for monochrome contexts. If nil, the full color image is desaturated.
@property (nonatomic, nullable, retain) CLKImageProvider *tintedImageProvider API_AVAILABLE(watchos(6.0)) API_UNAVAILABLE(ios);

/// Text for accessibility.
@property (nonatomic, nullable, retain) NSString *accessibilityLabel;

@end

NS_ASSUME_NONNULL_END

