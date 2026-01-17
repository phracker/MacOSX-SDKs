//
//  CPManeuver.h
//  CarPlay
//
//  Copyright © 2018 Apple Inc. All rights reserved.
//

#import <CarPlay/CPImageSet.h>
#import <Foundation/Foundation.h>
#import <CarPlay/CPLaneGuidance.h>
#import <CarPlay/CPTravelEstimates.h>
#import <UIKit/UIKit.h>

typedef NS_ENUM(NSUInteger, CPManeuverType) {
    CPManeuverTypeNoTurn                    =  0,
    CPManeuverTypeLeftTurn                  =  1,
    CPManeuverTypeRightTurn                 =  2,
    CPManeuverTypeStraightAhead             =  3,
    CPManeuverTypeUTurn                     =  4,
    CPManeuverTypeFollowRoad                =  5,
    CPManeuverTypeEnterRoundabout           =  6,
    CPManeuverTypeExitRoundabout            =  7,
    CPManeuverTypeOffRamp                   =  8,
    CPManeuverTypeOnRamp                    =  9,
    CPManeuverTypeArriveEndOfNavigation     = 10,
    CPManeuverTypeStartRoute                = 11,
    CPManeuverTypeArriveAtDestination       = 12,
    CPManeuverTypeKeepLeft                  = 13,
    CPManeuverTypeKeepRight                 = 14,
    CPManeuverTypeEnter_Ferry               = 15,
    CPManeuverTypeExitFerry                 = 16,
    CPManeuverTypeChangeFerry               = 17,
    CPManeuverTypeStartRouteWithUTurn       = 18,
    CPManeuverTypeUTurnAtRoundabout         = 19,
    CPManeuverTypeLeftTurnAtEnd             = 20,
    CPManeuverTypeRightTurnAtEnd            = 21,
    CPManeuverTypeHighwayOffRampLeft        = 22,
    CPManeuverTypeHighwayOffRampRight       = 23,
    CPManeuverTypeArriveAtDestinationLeft   = 24,
    CPManeuverTypeArriveAtDestinationRight  = 25,
    CPManeuverTypeUTurnWhenPossible         = 26,
    CPManeuverTypeArriveEndOfDirections     = 27,
    CPManeuverTypeRoundaboutExit1           = 28,
    CPManeuverTypeRoundaboutExit2           = 29,
    CPManeuverTypeRoundaboutExit3           = 30,
    CPManeuverTypeRoundaboutExit4           = 31,
    CPManeuverTypeRoundaboutExit5           = 32,
    CPManeuverTypeRoundaboutExit6           = 33,
    CPManeuverTypeRoundaboutExit7           = 34,
    CPManeuverTypeRoundaboutExit8           = 35,
    CPManeuverTypeRoundaboutExit9           = 36,
    CPManeuverTypeRoundaboutExit10          = 37,
    CPManeuverTypeRoundaboutExit11          = 38,
    CPManeuverTypeRoundaboutExit12          = 39,
    CPManeuverTypeRoundaboutExit13          = 40,
    CPManeuverTypeRoundaboutExit14          = 41,
    CPManeuverTypeRoundaboutExit15          = 42,
    CPManeuverTypeRoundaboutExit16          = 43,
    CPManeuverTypeRoundaboutExit17          = 44,
    CPManeuverTypeRoundaboutExit18          = 45,
    CPManeuverTypeRoundaboutExit19          = 46,
    CPManeuverTypeSharpLeftTurn             = 47,
    CPManeuverTypeSharpRightTurn            = 48,
    CPManeuverTypeSlightLeftTurn            = 49,
    CPManeuverTypeSlightRightTurn           = 50,
    CPManeuverTypeChangeHighway             = 51,
    CPManeuverTypeChangeHighwayLeft         = 52,
    CPManeuverTypeChangeHighwayRight        = 53,
} API_AVAILABLE(ios(17.4));

typedef NS_ENUM(NSUInteger, CPJunctionType) {
    CPJunctionTypeIntersection = 0, // single intersection with roads coming to a common point
    CPJunctionTypeRoundabout   = 1, // roundabout, junction elements represent roads exiting the roundabout
} API_AVAILABLE(ios(17.4));

typedef NS_ENUM(NSUInteger, CPTrafficSide) {
    CPTrafficSideRight = 0, // counterclockwise for roundabouts
    CPTrafficSideLeft  = 1, // clockwise for roundabouts
} API_AVAILABLE(ios(17.4));

typedef NS_ENUM(NSInteger, CPManeuverState)
{
    CPManeuverStateContinue = 0,
    CPManeuverStateInitial,
    CPManeuverStatePrepare,
    CPManeuverStateExecute
} API_AVAILABLE(ios(17.4));

NS_ASSUME_NONNULL_BEGIN

/**
 @c CPManeuver describes a navigation instruction.
 */
API_AVAILABLE(ios(12.0)) API_UNAVAILABLE(tvos) API_UNAVAILABLE(macos, watchos)
@interface CPManeuver : NSObject <NSCopying, NSSecureCoding>

/**
 symbolSet is a @c CPImageSet representing the maneuver.
 */
@property (nullable, nonatomic, strong) CPImageSet *symbolSet API_DEPRECATED_WITH_REPLACEMENT("symbolImage", ios(12.0, 13.0)) API_UNAVAILABLE(tvos) API_UNAVAILABLE(macos, watchos);

/**
 Takes precedence over @c guidanceBackgroundColor set in @c CPMapTemplate.
 */
@property (nullable, nonatomic, strong) UIColor *cardBackgroundColor API_AVAILABLE(ios(15.4));

/**
 symbolImage is a @c UIImage representing the maneuver. Provide variants for UIUserInterfaceStyleLight and UIUserInterfaceStyleDark that will be used against light backgrounds and dark backgrounds.
 */
@property (nullable, nonatomic, strong) UIImage *symbolImage;

/**
 junctionImage is a @c UIImage used to display a junction for the maneuver.
 
 @note The maximum image size is 140 points by 100 points. If necessary, images will be scaled down to fit while maintaining the aspect ratio.
 */
@property (nullable, nonatomic, strong) UIImage *junctionImage;

/**
 instructionVariants is an array of @c NSString representing the instruction for this maneuver, arranged from most to least preferred. You must provide at least one variant.
 The variant strings should be provided as localized, displayable content.
 */
@property (nonatomic, copy) NSArray<NSString *> *instructionVariants;

/**
   initialTravelEstimates represents the estimates beginning from the end of the preceding maneuver.
*/
@property (nullable, nonatomic, strong) CPTravelEstimates *initialTravelEstimates;

/**
 attributedInstructionVariants is an array of @c NSAttributedString representing the instruction for this maneuver,
 arranged from most to least preferred.
 
 @c attributedInstructionVariants will be preferred over instructionVariants. You must provide at least one variant for each maneuver.
 
 Only one type of attribute is presently supported: text attachments. You may annotate a maneuver instruction with images
 by including one or more text attachments. The maximum text attachment image size is 64x25 points.

 @warning All attributes other than text attachment attributes will be removed from your attributed string.

 @see +[NSAttributedString attributedStringWithAttachment:], -[NSTextAttachment image]
 */
@property (nonatomic, copy) NSArray<NSAttributedString *> *attributedInstructionVariants;

/**
 dashboardSymbolImage is a @c UIImage representing the maneuver that will be used on the dashboard. Provide variants for UIUserInterfaceStyleLight and UIUserInterfaceStyleDark that will be used against light backgrounds and dark backgrounds. If no dashboard image
 is provided, symbolImage will be used.
 */
@property (nullable, nonatomic, strong) UIImage *dashboardSymbolImage API_AVAILABLE(ios(14.0));

/**
 dashboardJunctionImage is a @c UIImage used to display a junction for the maneuver on the dashboard. If no dashboard junction image is provided, junctionImage will be used.
 
 @note The maximum image size is 140 points by 100 points. If necessary, images will be scaled down to fit while maintaining the aspect ratio.
 */
@property (nullable, nonatomic, strong) UIImage *dashboardJunctionImage API_AVAILABLE(ios(14.0));

/**
 dashboardInstructionVariants is an array of @c NSString representing the instruction for this maneuver on the dashboard, arranged from most to least preferred. If no dashboard variants are provided, the system will check for attributedInstructionVariants, then instructionVariants.
 The variant strings should be provided as localized, displayable content.
 */
@property (nonatomic, copy) NSArray<NSString *> *dashboardInstructionVariants API_AVAILABLE(ios(14.0));

/**
 dashboardAttributedInstructionVariants is an array of @c NSAttributedString representing the instruction for this maneuver on the dashboard,
 arranged from most to least preferred.
 
 @c dashboardAttributedInstructionVariants will be preferred over dashboardInstructionVariants. If no dashboard attributed variants are provided, dashboardInstructionVariants will be used.
 
 Only one type of attribute is presently supported: text attachments. You may annotate a maneuver instruction with images
 by including one or more text attachments. The maximum text attachment image size is 64x25 points.

 @warning All attributes other than text attachment attributes will be removed from your attributed string.

 @see +[NSAttributedString attributedStringWithAttachment:], -[NSTextAttachment image]
 */
@property (nonatomic, copy) NSArray<NSAttributedString *> *dashboardAttributedInstructionVariants API_AVAILABLE(ios(14.0));

/**
 notificationSymbolImage is a @c UIImage representing the maneuver that will be used in a notification banner. Provide variants for UIUserInterfaceStyleLight and UIUserInterfaceStyleDark that will be used against light backgrounds and dark backgrounds. If no
 notification symbol image is provided, symbolImage will be used.
 */
@property (nullable, nonatomic, strong) UIImage *notificationSymbolImage API_AVAILABLE(ios(14.0));

/**
 notificationInstructionVariants is an array of @c NSString representing the instruction for this maneuver in a notification banner, arranged from most to least preferred. If no notification instruction variants are provided, the system will check for attributedInstructionVariants, then instructionVariants.
 The variant strings should be provided as localized, displayable content.
 */
@property (nonatomic, copy) NSArray<NSString *> *notificationInstructionVariants API_AVAILABLE(ios(14.0));

/**
 notificationAttributedInstructionVariants is an array of @c NSAttributedString representing the instruction for this maneuver in a notification banner,
 arranged from most to least preferred.
 
 @c notificationAttributedInstructionVariants will be preferred over instructionVariants. If no notification attributed variants are provided, notificationInstructionVariants will be used.
 
 Only one type of attribute is presently supported: text attachments. You may annotate a maneuver instruction with images
 by including one or more text attachments. The maximum text attachment image size is 64x25 points.

 @warning All attributes other than text attachment attributes will be removed from your attributed string.

 @see +[NSAttributedString attributedStringWithAttachment:], -[NSTextAttachment image]
 */
@property (nonatomic, copy) NSArray<NSAttributedString *> *notificationAttributedInstructionVariants API_AVAILABLE(ios(14.0));

/**
 maneuverType is a @c CPManeuverType representing the type of maneuver.
 */
@property (nonatomic, assign) CPManeuverType maneuverType API_AVAILABLE(ios(17.4));

/**
 roadFollowingManeuverVariants is an array of @c NSString representing the name of the road following this maneuver,
 arranged from most to least preferred. (arranged by space)
 */
@property (nonatomic, copy, nullable) NSArray<NSString *> *roadFollowingManeuverVariants API_AVAILABLE(ios(17.4));

/**
 trafficSide is a @c CPTrafficSide representing which side of the road the traffic drives on.
 */
@property (nonatomic, assign) CPTrafficSide trafficSide API_AVAILABLE(ios(17.4));

/**
 junctionType is a @c CPJunctionType representing the type of the junction associated with this maneuver
 */
@property (nonatomic, assign) CPJunctionType junctionType API_AVAILABLE(ios(17.4));

/**
 junctionExitAngle is the angle of the exit road of this junction.
 */
@property (nonatomic, copy, nullable) NSMeasurement<NSUnitAngle *> *junctionExitAngle API_AVAILABLE(ios(17.4));

/**
 junctionElementAngles is a set of angles of the rest of the roads of this junction. This must not include @c junctionExitAngle .
 */
@property (nonatomic, copy, nullable) NSSet<NSMeasurement<NSUnitAngle *> *> *junctionElementAngles API_AVAILABLE(ios(17.4));

/**
 linkedLaneGuidance is the optional @c CPLaneGuidance associated with this maneuver // conditional - must be there if there is a corresponding lane guidance
 */
@property (nonatomic, assign) CPLaneGuidance *linkedLaneGuidance API_AVAILABLE(ios(17.4));

/**
 highwayExitLabel is a @c NSString describing a highway exit. Exit 123 for example.
 */
@property (nonatomic, copy) NSString *highwayExitLabel API_AVAILABLE(ios(17.4));

/**
 Any custom user info related to this maneuver.
 */
@property (nullable, nonatomic, strong) id userInfo;

@end

NS_ASSUME_NONNULL_END
