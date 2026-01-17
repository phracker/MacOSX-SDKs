//
//  CPTrip.h
//  CarPlay
//
//  Copyright © 2018 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <MapKit/MapKit.h>

NS_ASSUME_NONNULL_BEGIN

/**
 @c CPRouteChoice describes a possible route for a @c CPTrip.
 */
API_AVAILABLE(ios(12.0)) API_UNAVAILABLE(macos, watchos, tvos)
@interface CPRouteChoice : NSObject <NSCopying, NSSecureCoding>

/**
 Initialize a @c CPRouteChoice with summary variants, additional information variants, and selection summary variants.
 The variant strings should be provided as localized, displayable content.
 */
- (instancetype)initWithSummaryVariants:(NSArray<NSString *> *)summaryVariants additionalInformationVariants:(NSArray<NSString *> *)additionalInformationVariants selectionSummaryVariants:(NSArray<NSString *> *)selectionSummaryVariants NS_DESIGNATED_INITIALIZER;

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

/**
 summaryVariants is an array of summary variants for this route choice, arranged from most to least preferred. You must provide at least one variant.
 The system will select the first variant that fits the available space. The variant strings should be provided as localized, displayable content.
 Example: "Via I-280 S"
 */
@property (nonatomic, readonly, copy) NSArray<NSString *> *summaryVariants;

/**
 selectionSummaryVariants is an array of summary variants for this route choice, arranged from most to least preferred. You must provide at least one variant.
 The system will select the first variant that fits the available space.
 */
@property (nullable, nonatomic, readonly, copy) NSArray<NSString *> *selectionSummaryVariants;

/**
 additionalInformationVariants is an array of additional information variants for this route choice, arranged from most to least preferred. You must provide at least one variant.
 The system will select the first variant that fits the available space. The variant strings should be provided as localized, displayable content.
 Examples: "Fastest Route", "Avoids Tolls"
 */
@property (nullable, nonatomic, readonly, copy) NSArray<NSString *> *additionalInformationVariants;

/**
 Any custom user info related to this route choice.
 */
@property (nullable, nonatomic, strong) id userInfo;

@end

/**
 @c CPTrip represents an origin and destination with route choices.
 */
API_AVAILABLE(ios(12.0)) API_UNAVAILABLE(macos, watchos, tvos)
@interface CPTrip : NSObject <NSSecureCoding>

/**
 Initialize a @c CPTrip with an origin item, destination item, and route choices.
 */
- (instancetype)initWithOrigin:(MKMapItem *)origin destination:(MKMapItem *)destination routeChoices:(NSArray<CPRouteChoice *> *)routeChoices NS_DESIGNATED_INITIALIZER;
- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

/**
 @c MKMapItem representing the origin for the trip.
 */
@property (nonatomic, readonly, strong) MKMapItem *origin;

/**
 @c MKMapItem representing the destination for the trip.
 */
@property (nonatomic, readonly, strong) MKMapItem *destination;

/**
 Array of @c CPRouteChoices for the trip.
 */
@property (nonatomic, readonly, copy) NSArray<CPRouteChoice *> *routeChoices;

/**
 Any custom user info related to this trip.
 */
@property (nullable, nonatomic, strong) id userInfo;

@end

NS_ASSUME_NONNULL_END
