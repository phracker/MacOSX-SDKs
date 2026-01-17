/*
 * Copyright (c) 2019, 2020 Apple Inc.
 * All rights reserved.
 */

#ifndef __NE_INDIRECT__
#error "Please import the NetworkExtension module instead of this file directly."
#endif

#import <NetworkExtension/NEFilterDataProvider.h>

NS_ASSUME_NONNULL_BEGIN

@class NEFilterRule;

/*!
 * @interface NEFilterSettings
 * @discussion The NEFilterSettings class declares the programmatic interface for an object that contains filter settings.
 *
 * NEFilterSettings is used by NEFilterDataProviders to communicate the desired settings for the filter to the framework. The framework takes care of applying the contained settings to the system.
 */
API_AVAILABLE(macos(10.15)) API_UNAVAILABLE(ios, watchos, tvos)
@interface NEFilterSettings : NSObject <NSSecureCoding,NSCopying>

/*!
 * @method initWithRules:defaultAction:
 * @discussion Initialize a newly-allocated NEFilterSettings object with a set of filtering rules and a default filter action to takke if none
 *    of the rules match.
 * @param rules An NSArray containing an ordered list of NEFilterRule objects. The maximum number of rules that this array can contain is 1000.
 * @param defaultAction The NEFilterAction to take for flows of network (non-loopback) data that do not match any of the specified rules. The default defaultAction is
 *     NEFilterActionFilterData. If defaultAction is NEFilterActionAllow or NEFilterActionDrop, then the rules array must contain at least one NEFilterRule.
 *     The default action for loopback traffic is NEFilterActionAllow and cannot be changed. To filter loopback traffic you must include rules in the rules array that specifically match loopback traffic
 *     and have an action of NEFilterActionFilterData.
 * @return the newly-initialized NEFilterSettings object.
 */
- (instancetype)initWithRules:(NSArray<NEFilterRule *> *)rules defaultAction:(NEFilterAction)defaultAction API_AVAILABLE(macos(10.15)) API_UNAVAILABLE(ios, watchos, tvos);

/*!
 * @property rules
 * @discussion An NSArray containing an ordered list of NEFilterRuleObjects. After the NEFilterSettings are applied to the system,
 *     each network flow is matched against these rules in order, and the NEFilterAction of the first rule that matches is taken:
 *         NEFilterActionAllow: Allow the flow of data to proceed on its journey through the networking stack without consulting this provider.
 *         NEFilterActionDrop: Drop the flow without consulting this provider.
 *         NEFilterActionFilterData: Call this provider's handleNewFlow: method with the flow.
 */
@property (readonly, copy) NSArray<NEFilterRule *> *rules API_AVAILABLE(macos(10.15)) API_UNAVAILABLE(ios, watchos, tvos);

/*!
 * @property defaultAction
 * @discussion An NEFilterAction containing the default action to take for flows of network data that do not match any of the specified rules.
 */
@property (readonly) NEFilterAction defaultAction API_AVAILABLE(macos(10.15)) API_UNAVAILABLE(ios, watchos, tvos);

@end

NS_ASSUME_NONNULL_END
