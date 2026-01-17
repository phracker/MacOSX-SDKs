//
//  CPLaneGuidance.h
//  CarPlay
//
//  Copyright © 2023 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CarPlay/CPLane.h>

NS_ASSUME_NONNULL_BEGIN

/**
 @c CPLaneGuidance represents guidance to give the user which lane or lanes are preferred.
 */
API_AVAILABLE(ios(17.4))
@interface CPLaneGuidance : NSObject <NSCopying, NSSecureCoding>

/**
 lanes is an array of @c CPLane objects, each describes a single lane.
*/
@property (nonatomic, copy) NSArray<CPLane *> *lanes API_AVAILABLE(ios(17.4));

/**
 instructionVariants is an array of @c NSString representing the instruction for this lane guidance, arranged from most to least preferred. You must provide at least one variant.
 The variant strings should be provided as localized, displayable content.
*/
@property (nonatomic, copy) NSArray<NSString *> *instructionVariants API_AVAILABLE(ios(17.4));
@end

NS_ASSUME_NONNULL_END
