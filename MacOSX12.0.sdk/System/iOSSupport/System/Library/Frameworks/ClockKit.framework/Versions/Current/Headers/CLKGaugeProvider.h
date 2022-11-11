//
//  CLKGaugeProvider.h
//  ClockKit
//
//  Copyright © 2018 Apple Inc. All rights reserved.
//

#import <UIKit/UIColor.h>
#import <ClockKit/CLKDefines.h>

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(watchos(5.0)) API_UNAVAILABLE(ios)
@interface CLKGaugeProvider : NSObject <NSCopying>

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@property (nonatomic, assign, readonly) CLKGaugeProviderStyle style;

@property (nonatomic, nullable, readonly) NSArray<UIColor *> *gaugeColors;
@property (nonatomic, nullable, readonly) NSArray<NSNumber *> *gaugeColorLocations;

/// Text for accessibility.
@property (nonatomic, nullable, retain) NSString *accessibilityLabel;

@end

API_AVAILABLE(watchos(5.0)) API_UNAVAILABLE(ios)
@interface CLKSimpleGaugeProvider : CLKGaugeProvider

+ (instancetype)gaugeProviderWithStyle:(CLKGaugeProviderStyle)style
                           gaugeColors:(NSArray<UIColor *> *_Nullable)gaugeColors
                   gaugeColorLocations:(NSArray<NSNumber *> *_Nullable)gaugeColorLocations
                          fillFraction:(float)fillFraction;

+ (instancetype)gaugeProviderWithStyle:(CLKGaugeProviderStyle)style
                            gaugeColor:(UIColor *)color
                          fillFraction:(float)fillFraction;

@property (nonatomic, assign, readonly) float fillFraction;

@end

API_AVAILABLE(watchos(5.0)) API_UNAVAILABLE(ios)
@interface CLKTimeIntervalGaugeProvider : CLKGaugeProvider

+ (instancetype)gaugeProviderWithStyle:(CLKGaugeProviderStyle)style
                           gaugeColors:(NSArray<UIColor *> *_Nullable)gaugeColors
                   gaugeColorLocations:(NSArray<NSNumber *> *_Nullable)gaugeColorLocations
                             startDate:(NSDate *)startDate
                               endDate:(NSDate *)endDate;

+ (instancetype)gaugeProviderWithStyle:(CLKGaugeProviderStyle)style
                           gaugeColors:(NSArray<UIColor *> *_Nullable)gaugeColors
                   gaugeColorLocations:(NSArray<NSNumber *> *_Nullable)gaugeColorLocations
                             startDate:(NSDate *)startDate
                     startFillFraction:(float)startFillFraction
                               endDate:(NSDate *)endDate
                       endFillFraction:(float)endFillFraction;

@property (nonatomic, readonly) NSDate *startDate;
@property (nonatomic, readonly) NSDate *endDate;
@property (nonatomic, readonly) float startFillFraction;
@property (nonatomic, readonly) float endFillFraction;

@end

NS_ASSUME_NONNULL_END

