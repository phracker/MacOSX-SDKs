//
//  CLKImageProvider.h
//  ClockKit
//
//  Copyright © 2015 Apple Inc. All rights reserved.
//

#import <UIKit/UIImage.h>
#import <ClockKit/CLKDefines.h>

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(watchos(2.0)) API_UNAVAILABLE(ios)
@interface CLKImageProvider : NSObject <NSCopying>

- (instancetype)init API_DEPRECATED("Use initializers that take parameters.", watchos(2.0, 7.0), ios(9.0, 14.0));
+ (instancetype)new API_DEPRECATED("Use factory methods that take parameters.", watchos(2.0, 7.0), ios(9.0, 14.0));

- (instancetype)initWithOnePieceImage:(UIImage *)onePieceImage API_AVAILABLE(watchos(7.0)) API_UNAVAILABLE(ios) NS_SWIFT_UNAVAILABLE("Use class factory");
- (instancetype)initWithOnePieceImage:(UIImage *)onePieceImage
              twoPieceImageBackground:(UIImage * __nullable)twoPieceImageBackground
              twoPieceImageForeground:(UIImage * __nullable)twoPieceImageForeground API_AVAILABLE(watchos(7.0)) API_UNAVAILABLE(ios) NS_SWIFT_UNAVAILABLE("Use class factory");

+ (instancetype)imageProviderWithOnePieceImage:(UIImage *)onePieceImage;

+ (instancetype)imageProviderWithOnePieceImage:(UIImage *)onePieceImage
                       twoPieceImageBackground:(UIImage * __nullable)twoPieceImageBackground
                       twoPieceImageForeground:(UIImage * __nullable)twoPieceImageForeground;

/// Image to be used in single-color contexts, e.g. single-color faces.
@property (nonatomic, retain) UIImage *onePieceImage;

/// Tint color, honored in multicolor contexts.
/// Not honored for tinted graphic complications.
@property (nonatomic, nullable, retain) UIColor *tintColor;

/// Background image to be used in multicolor or tinted contexts, e.g. multicolor modular, tinted graphic complications.
/// If supplied, a twoPieceImageForeground is required as well.
@property (nonatomic, nullable, retain) UIImage *twoPieceImageBackground;

/// Foreground image to be used in multicolor or tinted contexts.
/// Overlaid on top of twoPieceImageBackground.
/// If supplied, a twoPieceImageBackground is required as well.
@property (nonatomic, nullable, retain) UIImage *twoPieceImageForeground;

/// Text for accessibility.
@property (nonatomic, nullable, retain) NSString *accessibilityLabel;

@end

NS_ASSUME_NONNULL_END
