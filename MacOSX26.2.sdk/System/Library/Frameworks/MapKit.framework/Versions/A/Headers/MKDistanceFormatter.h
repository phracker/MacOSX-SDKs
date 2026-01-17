//
//  MKDistanceFormatter.h
//  MapKit
//
//  Copyright (c) 2013-2014, Apple Inc. All rights reserved.
//

#import <MapKit/MKFoundation.h>
#import <CoreLocation/CoreLocation.h>

NS_ASSUME_NONNULL_BEGIN

NS_CLASS_AVAILABLE(10_9, 7_0) __TVOS_AVAILABLE(9_2)
@interface MKDistanceFormatter : NSFormatter

// Convenience methods. MKDistanceFormatter also responds to the usual NSFormatter methods.
- (NSString *)stringFromDistance:(CLLocationDistance)distance;
- (CLLocationDistance)distanceFromString:(NSString *)distance; // Returns negative distance if distance string could not be parsed.

@property (copy, NS_NONATOMIC_IOSONLY, null_resettable) NSLocale *locale; // defaults to current locale

typedef NS_ENUM(NSUInteger, MKDistanceFormatterUnits) {
    MKDistanceFormatterUnitsDefault, // Let units depend on locale. Note that some locales use imperial measurements for distances but metric for everything else, so this is not identical to NSLocaleUsesMetricSystem.
    MKDistanceFormatterUnitsMetric,
    MKDistanceFormatterUnitsImperial,
    MKDistanceFormatterUnitsImperialWithYards
} NS_ENUM_AVAILABLE(10_9, 7_0) __TVOS_AVAILABLE(9_2);

@property (assign, NS_NONATOMIC_IOSONLY) MKDistanceFormatterUnits units;

typedef NS_ENUM(NSUInteger, MKDistanceFormatterUnitStyle) {
    MKDistanceFormatterUnitStyleDefault = 0,    // Whether to abbreviate depends on units, locale, and user interface language
    MKDistanceFormatterUnitStyleAbbreviated,    // Ex. km
    MKDistanceFormatterUnitStyleFull            // Ex. kilometers
} NS_ENUM_AVAILABLE(10_9, 7_0) __TVOS_AVAILABLE(9_2);

@property (assign, NS_NONATOMIC_IOSONLY) MKDistanceFormatterUnitStyle unitStyle;

@end

NS_ASSUME_NONNULL_END

