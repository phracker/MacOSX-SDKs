//
//  CPPointOfInterestTemplate.h
//  CarPlay
//
//  Copyright © 2020 Apple Inc. All rights reserved.
//

#import <CarPlay/CPTemplate.h>
#import <CarPlay/CPPointOfInterest.h>
#import <MapKit/MKGeometry.h>

@class CPPointOfInterestTemplate;

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(14.0)) API_UNAVAILABLE(macos, watchos, tvos)
@protocol CPPointOfInterestTemplateDelegate <NSObject>
@required

/**
 The user has changed the map region on the @c CPPointOfInterestTemplate. Your application
 should respond by updating @c pointsOfInterest to show new points of interest for the new region.
 */
- (void)pointOfInterestTemplate:(CPPointOfInterestTemplate *)pointOfInterestTemplate didChangeMapRegion:(MKCoordinateRegion)region;

@optional
/**
 The user has selected the @c pointOfInterest and the details are being shown.
 */
- (void)pointOfInterestTemplate:(CPPointOfInterestTemplate *)pointOfInterestTemplate didSelectPointOfInterest:(CPPointOfInterest *)pointOfInterest;

@end

API_AVAILABLE(ios(14.0)) API_UNAVAILABLE(macos, watchos, tvos)
@interface CPPointOfInterestTemplate : CPTemplate

/**
 CPPointOfInterestTemplate displays a map view with selectable points of interest.
 
 @param title Template title
 @param pointsOfInterest Points of interest to be presented in the map.
 @param selectedIndex Index of selected point of interest instance referenced in the pointsOfInterest array. Use NSNotFound to indicate no selection.
 
 @note the maximum number of POIs is 12. If you provide more than 12, only the first 12 will be used.
 */
- (instancetype)initWithTitle:(NSString *)title
             pointsOfInterest:(NSArray<CPPointOfInterest*> *)pointsOfInterest
                selectedIndex:(NSUInteger)selectedIndex NS_DESIGNATED_INITIALIZER;

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

/**
 Template title appears on the template point of interest picker
 */
@property (nonatomic, copy) NSString *title;

/**
 Update the template with a list of points of interests to dispay
 
 @param pointsOfInterest Points of interest to be presented in the map.
 @param selectedIndex  Index of selected point of interest instance referenced in the pointsOfInterest array. Use NSNotFound to indicate no selection.
 
 @note the maximum number of POIs is 12. If you provide more than 12, only the first 12 will be used.
 */
- (void)setPointsOfInterest:(NSArray<CPPointOfInterest*> *)pointsOfInterest selectedIndex:(NSUInteger)selectedIndex;

@property (nonatomic, readonly) NSArray<CPPointOfInterest*> *pointsOfInterest;

/**
 Designate an instance in the pointsOfInterest array to highlight. Use NSNotFound to indicate no selection.
 */
@property (nonatomic, assign) NSUInteger selectedIndex;

/**
 The Point of Interest template's delegate is informed of user events.
 */
@property (nullable, nonatomic, weak) id<CPPointOfInterestTemplateDelegate> pointOfInterestDelegate;

@end

NS_ASSUME_NONNULL_END
