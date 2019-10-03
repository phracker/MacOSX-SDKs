//
//  INImage+IntentsUI.h
//  Intents
//
//  Copyright (c) 2016 Apple Inc. All rights reserved.
//

#import <Intents/INImage.h>

#import <CoreGraphics/CoreGraphics.h>
#import <UIKit/UIKit.h>

@class INIntentResponse;

NS_ASSUME_NONNULL_BEGIN

@interface INImage (IntentsUI)

+ (instancetype)imageWithCGImage:(CGImageRef)imageRef API_AVAILABLE(ios(10.0), watchos(5.0)) API_UNAVAILABLE(macosx, tvos);
+ (instancetype)imageWithUIImage:(UIImage *)image API_AVAILABLE(ios(10.0), watchos(5.0)) API_UNAVAILABLE(macosx, tvos);

/*!
 @abstract Returns the image size at which the image for an INIntentResponse will be displayed
 */
+ (CGSize)imageSizeForIntentResponse:(INIntentResponse *)response API_AVAILABLE(ios(10.0), watchos(5.0)) API_UNAVAILABLE(macosx, tvos);

- (void)fetchUIImageWithCompletion:(void (^)(UIImage * _Nullable image))completion API_AVAILABLE(ios(11.0), watchos(5.0)) API_UNAVAILABLE(macosx, tvos);

@end

NS_ASSUME_NONNULL_END
