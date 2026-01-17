/*
 * Copyright (c) 2015-2020 Apple Inc.
 * All rights reserved.
 */

#ifndef __NE_INDIRECT__
#error "Please import the NetworkExtension module instead of this file directly."
#endif

#import <NetworkExtension/NEFilterProvider.h>
#import <NetworkExtension/NENetworkRule.h>

@class NEFilterVerdict;
@class NEFilterNewFlowVerdict;
@class NEFilterDataVerdict;
@class NEFilterRemediationVerdict;
@class NEFilterFlow;
@class NEFilterBrowserFlow;
@class NEFilterSocketFlow;
@class NEFilterSettings;

NS_ASSUME_NONNULL_BEGIN

#define NEFILTER_DATA_PROVIDER_EXTERN extern

/*!
 * @file NEFilterDataProvider.h
 * @discussion This file declares the NEFilterDataProvider. The NEFilterDataProvider API is used to implement the portion of a content filtering solution that is responsible for making filtering decisions about network data flows.
 */

/*!
 * @typedef NEFilterDataAttribute
 * @abstract Attribute flags describing data
 */
typedef NS_ENUM(NSInteger, NEFilterDataAttribute) {
	/*! @const NEFilterDataAttributeHasIPHeader IP header is included in data */
	NEFilterDataAttributeHasIPHeader = 0x00000001
} API_AVAILABLE(macos(10.15.5)) API_UNAVAILABLE(ios, watchos, tvos);

/*!
 * @interface NEFilterDataProvider
 * @discussion The NEFilterDataProvider class declares the programmatic interface for an object that evaluates network data flows based on a set of locally-available rules and makes decisions about whether to block or allow the flows.
 */
API_AVAILABLE(macos(10.15), ios(9.0)) API_UNAVAILABLE(watchos, tvos)
@interface NEFilterDataProvider : NEFilterProvider

/*!
 * @method handleNewFlow:
 * @discussion This function is called by the framework when a filtering decision needs to be made about a new network data flow. Subclasses must override this method to implement the steps necessary to match the flow against some locally stored rules and return an appropriate verdict.
 * @param flow An NEFilterFlow object containing details about the new flow.
 * @return An NEFilterNewFlowVerdict object containing the verdict for the new flow.
 */
- (NEFilterNewFlowVerdict *)handleNewFlow:(NEFilterFlow *)flow API_AVAILABLE(macos(10.15), ios(9.0)) API_UNAVAILABLE(watchos, tvos);

/*!
 * @method handleInboundDataFromFlow:readBytesStartOffset:readBytes:
 * @discussion This function is called by the framework when a filtering decision needs to be made about some inbound data that the filter previously requested access to via the NEFilterFlowDataVerdict or the NEFilterNewFlowVerdict. Subclasses must override this method.
 * @param flow The NEFilterFlow from which the data was read.
 * @param offset The offset in bytes from the start of the flow's inbound data at which readBytes begins.
 * @param readBytes The data that was read.  For non-UDP/TCP flows, since data may optionally include the IP header, readBytes includes a 4-bytes NEFilterDataAttribute field preceding the user data.  Handler must examine the NEFilterDataAttribute field and handle the data accordingly.
 * @return An NEFilterFlowDataVerdict containing the verdict for the flow.
 */
- (NEFilterDataVerdict *)handleInboundDataFromFlow:(NEFilterFlow *)flow readBytesStartOffset:(NSUInteger)offset readBytes:(NSData *)readBytes API_AVAILABLE(macos(10.15), ios(9.0)) API_UNAVAILABLE(watchos, tvos);

/*!
 * @method handleOutboundDataFromFlow:readBytesStartOffset:readBytes:
 * @discussion This function is called by the framework when a filtering decision needs to be made about some outbound data that the filter previously requested access to via the NEFilterFlowDataVerdict or the NEFilterNewFlowVerdict. Subclasses must override this method.
 * @param flow The NEFilterFlow from which the data was read.
 * @param offset The offset in bytes from the start of the flow's outbound data at which readBytes begins.
 * @param readBytes The data that was read.  For non-UDP/TCP flows, since data may optionally include the IP header, readBytes includes a 4-bytes NEFilterDataAttribute field preceding the user data.  Handler must examine the NEFilterDataAttribute field and handle the data accordingly.
 * @return An NEFilterFlowDataVerdict containing the verdict for the flow.
 */
- (NEFilterDataVerdict *)handleOutboundDataFromFlow:(NEFilterFlow *)flow readBytesStartOffset:(NSUInteger)offset readBytes:(NSData *)readBytes API_AVAILABLE(macos(10.15), ios(9.0)) API_UNAVAILABLE(watchos, tvos);

/*!
 * @method handleInboundDataCompleteForFlow:
 * @discussion This function is called by the framework after all of the inbound data for a flow has been seen by the filter. Subclasses must override this method to return an appropriate pass/block result.
 * @param flow The flow
 * @return The final NEFilterFlowDataVerdict verdict for the flow.
 */
- (NEFilterDataVerdict *)handleInboundDataCompleteForFlow:(NEFilterFlow *)flow API_AVAILABLE(macos(10.15), ios(9.0)) API_UNAVAILABLE(watchos, tvos);

/*!
 * @method handleOutboundDataCompleteForFlow:
 * @discussion This function is called by the framework after all of the outbound data for a flow has been seen by the filter. Subclasses must override this method to return an appropriate pass/block result.
 * @param flow The flow
 * @return The final NEFilterFlowDataVerdict verdict for the flow.
 */
- (NEFilterDataVerdict *)handleOutboundDataCompleteForFlow:(NEFilterFlow *)flow API_AVAILABLE(macos(10.15), ios(9.0)) API_UNAVAILABLE(watchos, tvos);

/*!
 * @method handleRemediationForFlow:
 * @discussion This function is called by the framework after the user requests remediation for a blocked flow. Subclasses must override this method to return an appropriate pass/block result.
 * @param flow The flow
 * @return The final NEFilterRemediationVerdict verdict for the flow.
 */
- (NEFilterRemediationVerdict *)handleRemediationForFlow:(NEFilterFlow *)flow API_AVAILABLE(ios(9.0)) API_UNAVAILABLE(macos, watchos, tvos);

/*!
 * @method handleRulesChanged
 * @discussion This function is called by the framework when -[NEFilterControlProvider notifyRulesChanged] is called. Subclasses should override this method to reload new rules from disk.
 */
- (void)handleRulesChanged API_AVAILABLE(ios(9.0)) API_UNAVAILABLE(macos, watchos, tvos);

/*!
 * @method applyFilterRules:defaultAction:withCompletionHandler:
 * @discussion The provider calls this function to apply the current set of filtering rules associated with the provider and also change the default filtering action.
 * @param settings A NEFilterSettings object containing the filter settings to apply to the system. Pass nil to revert to the default settings, which are an
 *     empty list of rules and a default action of NEFilterActionFilterData.
 * @param completionHandler A block that will be executed when the settings have been applied to the system. If an error occurs then the error parameter will be non-nil.
 */
- (void)applySettings:(nullable NEFilterSettings *)settings completionHandler:(void (^)(NSError * _Nullable error))completionHandler API_AVAILABLE(macos(10.15)) API_UNAVAILABLE(ios, watchos, tvos);

/*!
 * @method resumeFlow:withVerdict:
 * @discussion This function is called by the provider to resume a flow that was previously paused by the provider returning a pause verdict.
 * @param flow The flow to resume
 * @param verdict The next NEFilterDataVerdict for the flow. This verdict is used as the verdict corresponding to the
 *    flow handler callback (handleNewFlow:, handleInboundDataFromFlow:, etc.) that returned the pause verdict that
 *    paused the flow. This must be either a NEFilterDataVerdict or a NEFilterNewFlowVerdict. It is invalid to resume
 *    a flow that is not paused.
 */
- (void)resumeFlow:(NEFilterFlow *)flow withVerdict:(NEFilterVerdict *)verdict API_AVAILABLE(macos(10.15)) API_UNAVAILABLE(ios, watchos, tvos);

/*!
 * @method updateFlow:withVerdict:forDirection:
 * @discussion This function is called by the provider to update the verdict for a flow outside the context of any NEFilterDataProvider callback.
 * @param flow The NEFilterSocketFlow to update the verdict for.
 * @param verdict The NEFilterDataVerdict. Must be a +[NEFilterDataVerdict allowVerdict], a +[NEFilterDataVerdict dropVerdict], or a +[NEFilterDataVerdict dataVerdictWithPassBytes:peekBytes:].
 * @param direction The direction to which the verdict applies. Pass NETrafficDirectionAny to update the verdict for both the inbound and outbound directions. This parameter is ignored if the verdict is +[NEFilterDataVerdict dropVerdict].
 */
- (void)updateFlow:(NEFilterSocketFlow *)flow usingVerdict:(NEFilterDataVerdict *)verdict forDirection:(NETrafficDirection)direction API_AVAILABLE(macos(10.15.4)) API_UNAVAILABLE(ios, watchos, tvos);

@end

/*!
 * @interface NEFilterDataVerdict
 * @discussion The NEFilterDataVerdict class declares the programmatic interface of an object that is the verdict for a flow of network data after some of the data has been seen by the filter.
 *
 * NEFilterDataVerdict is part of NetworkExtension.framework
 */
API_AVAILABLE(macos(10.15), ios(9.0)) API_UNAVAILABLE(watchos, tvos)
@interface NEFilterDataVerdict : NEFilterVerdict <NSSecureCoding,NSCopying>

/*!
 * @property statisticsReportFrequency
 * @discussion The frequency at which the data provider's -[NEFilterProvider handleReport:] method is called with a NEFilterReport instance with an event of NEFilterReportEventFlowStatistics.
 *     The default value is NEFilterReportFrequencyNone, so by default no statistics are reported.
 */
@property NEFilterReportFrequency statisticsReportFrequency API_AVAILABLE(macos(10.15.4)) API_UNAVAILABLE(ios, watchos, tvos);

/*!
 * @method allowVerdict
 * @discussion This class method returns a verdict indicating that the flow should be allowed.
 * @return The NEFilterDataVerdict object.
 */
+ (NEFilterDataVerdict *)allowVerdict API_AVAILABLE(macos(10.15), ios(9.0)) API_UNAVAILABLE(watchos, tvos);

/*!
 * @method dropVerdict
 * @discussion This class method returns a verdict indicating that the flow should be dropped.
 * @return The NEFilterDataVerdict object.
 */
+ (NEFilterDataVerdict *)dropVerdict API_AVAILABLE(macos(10.11), ios(9.0)) API_UNAVAILABLE(watchos, tvos);

/*!
 * @method remediateVerdictWithRemediationURLMapKey:remediationButtonTextMapKey:
 * @discussion This class method returns a verdict indicating that a "content blocked" page should be displayed to the user. The block page should contain a link to the given URL.
 * @param remediationURLMapKey Remediation map key used by data plugin to get remediation url. Passing nil will result into data provider being notified with the callback handleRemediationForFlow:
 * @param remediationButtonTextMapKey Remediation button map key used by the data plugin to get the remediation button text. Passing nil will set the button text to "Request Access"
 * @return The NEFilterDataVerdict object.
 */
+ (NEFilterDataVerdict *)remediateVerdictWithRemediationURLMapKey:(nullable NSString *)remediationURLMapKey remediationButtonTextMapKey:(nullable NSString *)remediationButtonTextMapKey API_AVAILABLE(ios(9.0)) API_UNAVAILABLE(macos, watchos, tvos);

/*!
 * @method dataVerdictWithPassBytes:peekBytes:
 * @discussion This class method returns a data verdict indicating that the filter is passing a given number of bytes through the filter and needs to see a given number of bytes after the bytes that are passed.
 * @param passBytes The number of bytes to pass through the filter.
 * @param peekBytes The number of bytes after the end of the bytes passed that the filter wants to see in the next call to -[NEFilterDataProvider handleOutboundDataFromFlow:readBytesStartOffset:readBytes:] or -[NEFilterDataProvider handleInboundDataFromFlow:readBytesStartOffset:readBytes:].
 * @return The data flow verdict.
 */
+ (NEFilterDataVerdict *)dataVerdictWithPassBytes:(NSUInteger)passBytes peekBytes:(NSUInteger)peekBytes API_AVAILABLE(macos(10.15), ios(9.0)) API_UNAVAILABLE(watchos, tvos);

/*!
 * @method needRulesVerdict
 * @discussion This class method returns a verdict indicating that control provider needs to be asked how to handle the data flow. The control provider can either drop or allow the flow, or update the rules and ask the data provider to decide on the data flow again.
 * @return The NEFilterDataVerdict object.
 */
+ (NEFilterDataVerdict *)needRulesVerdict API_AVAILABLE(ios(9.0)) API_UNAVAILABLE(macos, watchos, tvos);

/*!
 * @method pauseVerdict
 * @discussion This class method returns a verdict indicating that none of the data provider's handler callbacks shall be called for the flow until after the flow is resumed
 *     by a call to -[NEFilterDataProvider resumeFlow:withVerdict:]. TCP flows may be paused indefinitely. UDP flows will be dropped if not resumed within 10 seconds of
 *     being paused. It is invalid to pause a flow that is already paused.
 * @return The NEFilterDataVerdict object.
 */
+ (NEFilterDataVerdict *)pauseVerdict API_AVAILABLE(macos(10.15)) API_UNAVAILABLE(ios, watchos, tvos);

@end

/*!
 * @interface NEFilterRemediationVerdict
 * @discussion The NEFilterRemediationVerdict class declares the programmatic interface of an object that is the verdict for a flow which has been blocked by the filter, but the user has made a request for remediation.
 *
 * NEFilterRemediationVerdict is part of NetworkExtension.framework
 */
API_AVAILABLE(ios(9.0)) API_UNAVAILABLE(macos, watchos, tvos)
@interface NEFilterRemediationVerdict : NEFilterVerdict <NSSecureCoding,NSCopying>

/*!
 * @method allowVerdict
 * @discussion This class method returns a verdict indicating that the flow should be allowed.
 * @return The NEFilterRemediationVerdict object.
 */
+ (NEFilterRemediationVerdict *) allowVerdict API_AVAILABLE(ios(9.0)) API_UNAVAILABLE(macos, watchos, tvos);

/*!
 * @method dropVerdict
 * @discussion This class method returns a verdict indicating that the flow should be dropped.
 * @return The NEFilterRemediationVerdict object.
 */
+ (NEFilterRemediationVerdict *) dropVerdict API_AVAILABLE(ios(9.0)) API_UNAVAILABLE(macos, watchos, tvos);

/*!
 * @method needRulesVerdict
 * @discussion This class method returns a verdict indicating that control provider needs to be asked how to handle the remediation. The control provider can either drop or allow the flow, or update the rules and ask the data provider to decide on the data flow again.
 * @return The NEFilterRemediationVerdict object.
 */
+ (NEFilterRemediationVerdict *) needRulesVerdict API_AVAILABLE(ios(9.0)) API_UNAVAILABLE(macos, watchos, tvos);

@end

NS_ASSUME_NONNULL_END

