/*
 * Copyright (c) 2015-2018 Apple Inc.
 * All rights reserved.
 */

#ifndef __NE_INDIRECT__
#error "Please import the NetworkExtension module instead of this file directly."
#endif

#import <NetworkExtension/NEFilterProvider.h>

@class NEFilterVerdict;
@class NEFilterNewFlowVerdict;
@class NEFilterDataVerdict;
@class NEFilterRemediationVerdict;
@class NEFilterFlow;
@class NEFilterBrowserFlow;
@class NEFilterSocketFlow;

NS_ASSUME_NONNULL_BEGIN

#define NEFILTER_DATA_PROVIDER_EXTERN extern

/*!
 * @file NEFilterDataProvider.h
 * @discussion This file declares the NEFilterDataProvider. The NEFilterDataProvider API is used to implement the portion of a content filtering solution that is responsible for making filtering decisions about network data flows.
 */

/*!
 * @interface NEFilterDataProvider
 * @discussion The NEFilterDataProvider class declares the programmatic interface for an object that evaluates network data flows based on a set of locally-available rules and makes decisions about whether to block or allow the flows.
 */
API_AVAILABLE(ios(9.0)) API_UNAVAILABLE(macos, watchos, tvos)
@interface NEFilterDataProvider : NEFilterProvider

/*!
 * @method handleNewFlow:
 * @discussion This function is called by the framework when a filtering decision needs to be made about a new network data flow. Subclasses must override this method to implement the steps necessary to match the flow against some locally stored rules and return an appropriate verdict.
 * @param flow An NEFilterFlow object containing details about the new flow.
 * @return An NEFilterNewFlowVerdict object containing the veridct for the new flow.
 */
- (NEFilterNewFlowVerdict *)handleNewFlow:(NEFilterFlow *)flow API_AVAILABLE(ios(9.0)) API_UNAVAILABLE(macos, watchos, tvos);

/*!
 * @method handleInboundDataFromFlow:readBytesStartOffset:readBytes:
 * @discussion This function is called by the framework when a filtering decision needs to be made about some inbound data that the filter previously requested access to via the NEFilterFlowDataVerdict or the NEFilterNewFlowVerdict. Subclasses must override this method.
 * @param flow The NEFilterFlow from which the data was read.
 * @param offset The offset in bytes from the start of the flow's data of readBytes.
 * @param readBytes The data that was read.
 * @return An NEFilterFlowDataVerdict containing the verdict for the flow.
 */
- (NEFilterDataVerdict *)handleInboundDataFromFlow:(NEFilterFlow *)flow readBytesStartOffset:(NSUInteger)offset readBytes:(NSData *)readBytes API_AVAILABLE(ios(9.0)) API_UNAVAILABLE(macos, watchos, tvos);

/*!
 * @method handleOutboundDataFromFlow:readBytesStartOffset:readBytes:
 * @discussion This function is called by the framework when a filtering decision needs to be made about some outbound data that the filter previously requested access to via the NEFilterFlowDataVerdict or the NEFilterNewFlowVerdict. Subclasses must override this method.
 * @param flow The NEFilterFlow from which the data was read.
 * @param offset The offset in bytes from the start of the flow's data of readBytes.
 * @param readBytes The data that was read.
 * @return An NEFilterFlowDataVerdict containing the verdict for the flow.
 */
- (NEFilterDataVerdict *)handleOutboundDataFromFlow:(NEFilterFlow *)flow readBytesStartOffset:(NSUInteger)offset readBytes:(NSData *)readBytes API_AVAILABLE(ios(9.0)) API_UNAVAILABLE(macos, watchos, tvos);

/*!
 * @method handleInboundDataCompleteForFlow:
 * @discussion This function is called by the framework after all of the inbound data for a flow has been seen by the filter. Subclasses must override this method to return an appropriate pass/block result.
 * @param flow The flow
 * @return The final NEFilterFlowDataVerdict verdict for the flow.
 */
- (NEFilterDataVerdict *)handleInboundDataCompleteForFlow:(NEFilterFlow *)flow API_AVAILABLE(ios(9.0)) API_UNAVAILABLE(macos, watchos, tvos);

/*!
 * @method handleOutboundDataCompleteForFlow:
 * @discussion This function is called by the framework after all of the outbound data for a flow has been seen by the filter. Subclasses must override this method to return an appropriate pass/block result.
 * @param flow The flow
 * @return The final NEFilterFlowDataVerdict verdict for the flow.
 */
- (NEFilterDataVerdict *)handleOutboundDataCompleteForFlow:(NEFilterFlow *)flow API_AVAILABLE(ios(9.0)) API_UNAVAILABLE(macos, watchos, tvos);

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

@end

/*!
 * @interface NEFilterDataVerdict
 * @discussion The NEFilterDataVerdict class declares the programmatic interface of an object that is the verdict for a flow of network data after some of the data has been seen by the filter.
 *
 * NEFilterDataVerdict is part of NetworkExtension.framework
 */
API_AVAILABLE(ios(9.0)) API_UNAVAILABLE(macos, watchos, tvos)
@interface NEFilterDataVerdict : NEFilterVerdict <NSSecureCoding,NSCopying>

/*!
 * @method allowVerdict
 * @discussion This class method returns a verdict indicating that the flow should be allowed.
 * @return The NEFilterDataVerdict object.
 */
+ (NEFilterDataVerdict *) allowVerdict API_AVAILABLE(ios(9.0)) API_UNAVAILABLE(macos, watchos, tvos);

/*!
 * @method dropVerdict
 * @discussion This class method returns a verdict indicating that the flow should be dropped.
 * @return The NEFilterDataVerdict object.
 */
+ (NEFilterDataVerdict *) dropVerdict API_AVAILABLE(ios(9.0)) API_UNAVAILABLE(macos, watchos, tvos);

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
+ (NEFilterDataVerdict *)dataVerdictWithPassBytes:(NSUInteger)passBytes peekBytes:(NSUInteger)peekBytes API_AVAILABLE(ios(9.0)) API_UNAVAILABLE(macos, watchos, tvos);

/*!
 * @method needRulesVerdict
 * @discussion This class method returns a verdict indicating that control provider needs to be asked how to handle the data flow. The control provider can either drop or allow the flow, or update the rules and ask the data provider to decide on the data flow again.
 * @return The NEFilterDataVerdict object.
 */
+ (NEFilterDataVerdict *)needRulesVerdict API_AVAILABLE(ios(9.0)) API_UNAVAILABLE(macos, watchos, tvos);
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

