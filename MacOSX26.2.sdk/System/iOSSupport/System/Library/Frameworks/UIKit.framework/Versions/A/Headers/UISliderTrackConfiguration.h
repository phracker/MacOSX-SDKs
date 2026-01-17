#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UISliderTrackConfiguration.h>)
//
//  UISliderTrackConfiguration.h
//  UIKit
//
//  Copyright © 2025 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIImage.h>

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

UIKIT_EXTERN API_AVAILABLE(ios(26.0), visionos(26.0)) API_UNAVAILABLE(tvos, watchos) NS_REFINED_FOR_SWIFT NS_SWIFT_UI_ACTOR
@interface UISliderTick : NSObject <NSCopying, NSCoding>

@property (nonatomic, readonly) float position;
@property (nonatomic, readwrite, copy, nullable) NSString *title;
@property (nonatomic, readwrite, copy, nullable) UIImage *image;

+ (instancetype)tickWithPosition:(float)position title:(nullable NSString *)title image:(nullable UIImage *)image NS_SWIFT_NAME(tick(position:title:image:));

+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;

@end

UIKIT_EXTERN API_AVAILABLE(ios(26.0), visionos(26.0)) API_UNAVAILABLE(tvos, watchos) NS_REFINED_FOR_SWIFT NS_SWIFT_UI_ACTOR
@interface UISliderTrackConfiguration : NSObject <NSCopying, NSCoding>

@property (nonatomic, readwrite) BOOL allowsTickValuesOnly; // defaults to YES
@property (nonatomic, readwrite) float neutralValue;
@property (nonatomic, readwrite) float minimumEnabledValue;
@property (nonatomic, readwrite) float maximumEnabledValue;
@property (nonatomic, readonly, copy) NSArray<UISliderTick *> *ticks;

+ (instancetype)configurationWithTicks:(NSArray<UISliderTick *> *)ticks NS_SWIFT_NAME(configuration(ticks:));
+ (instancetype)configurationWithNumberOfTicks:(NSInteger)ticks NS_SWIFT_NAME(configuration(numberOfTicks:));

+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;

@end

NS_HEADER_AUDIT_END(nullability, sendability)

#else
#import <UIKitCore/UISliderTrackConfiguration.h>
#endif
