//
//  CLKDefines.h
//  ClockKit
//
//  Copyright © 2015 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

typedef NS_ENUM(NSInteger, CLKComplicationFamily) {
    CLKComplicationFamilyModularSmall                                                                       = 0,
    CLKComplicationFamilyModularLarge                                                                       = 1,
    CLKComplicationFamilyUtilitarianSmall                                                                   = 2,
    CLKComplicationFamilyUtilitarianSmallFlat API_AVAILABLE(watchos(3.0)) API_UNAVAILABLE(ios) /* subset of UtilitarianSmall */ = 6,
    CLKComplicationFamilyUtilitarianLarge                                                                   = 3,
    CLKComplicationFamilyCircularSmall                                                                      = 4,
    CLKComplicationFamilyExtraLarge API_AVAILABLE(watchos(3.0)) API_UNAVAILABLE(ios)                    = 7,
    
    CLKComplicationFamilyGraphicCorner API_AVAILABLE(watchos(5.0)) API_UNAVAILABLE(ios)                 = 8,
    CLKComplicationFamilyGraphicBezel API_AVAILABLE(watchos(5.0)) API_UNAVAILABLE(ios)                  = 9,
    CLKComplicationFamilyGraphicCircular API_AVAILABLE(watchos(5.0)) API_UNAVAILABLE(ios)               = 10,
    CLKComplicationFamilyGraphicRectangular API_AVAILABLE(watchos(5.0)) API_UNAVAILABLE(ios)            = 11,
    CLKComplicationFamilyGraphicExtraLarge API_AVAILABLE(watchos(7.0)) API_UNAVAILABLE(ios)             = 12,
} API_AVAILABLE(watchos(2.0)) API_UNAVAILABLE(ios);

typedef NS_OPTIONS(NSUInteger, CLKComplicationTimeTravelDirections) {
    CLKComplicationTimeTravelDirectionNone      = 0,
    CLKComplicationTimeTravelDirectionForward   = 1 << 0,
    CLKComplicationTimeTravelDirectionBackward  = 1 << 1,
} API_AVAILABLE(watchos(2.0)) API_UNAVAILABLE(ios);

typedef NS_ENUM(NSUInteger, CLKComplicationPrivacyBehavior) {
    CLKComplicationPrivacyBehaviorShowOnLockScreen,
    CLKComplicationPrivacyBehaviorHideOnLockScreen,
} API_AVAILABLE(watchos(2.0)) API_UNAVAILABLE(ios);

typedef NS_ENUM(NSUInteger, CLKComplicationTimelineAnimationBehavior) {
    CLKComplicationTimelineAnimationBehaviorNever,
    CLKComplicationTimelineAnimationBehaviorGrouped,
    CLKComplicationTimelineAnimationBehaviorAlways
} API_AVAILABLE(watchos(2.0)) API_UNAVAILABLE(ios);

typedef NS_ENUM(NSInteger, CLKComplicationColumnAlignment)  {
    CLKComplicationColumnAlignmentLeading = 0,
    CLKComplicationColumnAlignmentTrailing = 1,
    CLKComplicationColumnAlignmentLeft API_DEPRECATED_WITH_REPLACEMENT("CLKComplicationColumnAlignmentLeading", watchos(2.0, 2.1)) = CLKComplicationColumnAlignmentLeading,
    CLKComplicationColumnAlignmentRight API_DEPRECATED_WITH_REPLACEMENT("CLKComplicationColumnAlignmentTrailing", watchos(2.0, 2.1)) = CLKComplicationColumnAlignmentTrailing,
} API_AVAILABLE(watchos(2.0)) API_UNAVAILABLE(ios);

typedef NS_ENUM(NSInteger, CLKComplicationRingStyle)  {
    CLKComplicationRingStyleClosed,
    CLKComplicationRingStyleOpen,
} API_AVAILABLE(watchos(2.0)) API_UNAVAILABLE(ios);


typedef NS_ENUM(NSInteger, CLKGaugeProviderStyle) {
    CLKGaugeProviderStyleRing,
    CLKGaugeProviderStyleFill,
} API_AVAILABLE(watchos(5.0)) API_UNAVAILABLE(ios);

extern float const CLKSimpleGaugeProviderFillFractionEmpty API_AVAILABLE(watchos(5.0)) API_UNAVAILABLE(ios);


#pragma mark - Launch Keys

extern NSString * const CLKLaunchedTimelineEntryDateKey API_AVAILABLE(watchos(2.0)) API_UNAVAILABLE(ios);

extern NSString * const CLKLaunchedComplicationIdentifierKey API_AVAILABLE(watchos(7.0)) API_UNAVAILABLE(ios);

#pragma mark - Multiple Complication Support
extern NSString * const CLKDefaultComplicationIdentifier API_AVAILABLE(watchos(7.0)) API_UNAVAILABLE(ios);

extern NSArray<NSNumber *> *CLKAllComplicationFamilies(void) API_AVAILABLE(watchos(7.0)) API_UNAVAILABLE(ios) NS_REFINED_FOR_SWIFT;
