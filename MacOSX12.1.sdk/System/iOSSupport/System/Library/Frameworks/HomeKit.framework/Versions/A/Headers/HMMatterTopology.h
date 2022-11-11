//
//  HMMatterTopology.h
//  HomeKit
//
//  Copyright © 2020 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <HomeKit/HMDefines.h>

@class HMMatterHome;
@class HMMatterRoom;

NS_ASSUME_NONNULL_BEGIN

/*!
 * @abstract Wraps the information a Matter Ecosystem Partner is expected to pass when initiating setup. The number of homes vended to HomeKit by this class dictate whether a home selection step will be presented as part of setup. If so, these homes will be represented in system UI for user selection.
 */
HM_EXTERN API_AVAILABLE(ios(15.0))
@interface HMMatterTopology: NSObject <NSCopying, NSSecureCoding>

/*!
 * @abstract HMMatterTopology initializer.
 * @param homes count must be greater than 0.  If count is greater than 1, setup will present a home selection card.
 */
- (instancetype)initWithHomes:(NSArray<HMMatterHome *> *)homes;

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

/*!
 * @abstract Homes  provided by the partner ecosystem app for selection in iOS system UI.
 */
@property (nonatomic, copy, readonly) NSArray<HMMatterHome *> *homes;

@end

NS_ASSUME_NONNULL_END
