/*
 * Copyright (c) 2015-2019 Apple Inc.
 * All rights reserved.
 */

#ifndef __NE_INDIRECT__
#error "Please import the NetworkExtension module instead of this file directly."
#endif

#import <NetworkExtension/NEProvider.h>
#import <NetworkExtension/NEFilterFlow.h>

@class NEFilterProviderConfiguration;
@class NEFilterReport;

NS_ASSUME_NONNULL_BEGIN

#if defined(__cplusplus)
#define NEFILTER_EXPORT extern "C"
#else
#define NEFILTER_EXPORT extern
#endif

/*!
 *	Key to specify in the NSDictionary which is returned as a value in remediationMap.
 *	This key is used to indicate the Remediation URL. The URL should follow the scheme
 *	http or https to be used by the content filter.
 */
NEFILTER_EXPORT NSString const *NEFilterProviderRemediationMapRemediationURLs API_AVAILABLE(ios(9.0)) API_UNAVAILABLE(macos, watchos, tvos);			// Key for RemediationURL
NEFILTER_EXPORT NSString const *NEFilterProviderRemediationMapRemediationButtonTexts API_AVAILABLE(ios(9.0)) API_UNAVAILABLE(macos, watchos, tvos);	// Key for Remediation button text

/*!
 *	Strings which can be appended or inserted into the remediation URL
 */
#define	NEFilterProviderRemediationURLFlowURLHostname			@"NE_FLOW_HOSTNAME"	// Browser flow URL Hostname
#define NEFilterProviderRemediationURLFlowURL					@"NE_FLOW_URL"		// Browser flow URL
#define NEFilterProviderRemediationURLOrganization				@"NE_ORGANIZATION"	// Organization in filter provider configuration
#define NEFilterProviderRemediationURLUsername					@"NE_USERNAME"		// Username in the filter provider configuration

/*!
 * @file NEFilterProvider.h
 * @discussion This file declares the NEFilterProvider API. The NEFilterProvider API is used to implement custom content
 * filtering solutions.
 */

/*!
 * @interface NEFilterProvider
 * @discussion The NEFilterProvider class is an abstract base class that declares the programmatic interface of an
 * object that implements a socket filter.
 *
 * NEFilterProvider is part of NetworkExtension.framework
 */
API_AVAILABLE(macos(10.15), ios(9.0)) API_UNAVAILABLE(watchos, tvos)
@interface NEFilterProvider : NEProvider

/*!
 * @method startFilterWithCompletionHandler:
 * @discussion This function is called by the framework when the content filter is being started. Subclasses must
 * override this method and perform whatever steps are necessary to start the filter.
 * @param completionHandler A block that must be called when the process of starting the filter is complete. If the
 * filter was started successfully, subclass implementations must pass the nil value to this block. If an error occurred
 * while starting the filter, sublcass implementations must pass a non-nil NSError containing more details about the error.
 */
- (void)startFilterWithCompletionHandler:(void (^)(NSError * __nullable error))completionHandler API_AVAILABLE(macos(10.15), ios(9.0)) API_UNAVAILABLE(watchos, tvos);

/*!
 * @method stopFilterWithReason:completionHandler:
 * @discussion This function is called by the framework when the content filter is being stopped. Subclasses must
 * override this method and perform whatever steps are necessary to stop the filter.
 * @param reason An NEProviderStopReason indicating why the filter is being stopped.
 * @param completionHandler A block that must be called when the process of stopping the filter is complete.
 */
- (void)stopFilterWithReason:(NEProviderStopReason)reason
		   completionHandler:(void (^)(void))completionHandler API_AVAILABLE(macos(10.15), ios(9.0)) API_UNAVAILABLE(watchos, tvos);

/*!
 * @property filterConfiguration
 * @discussion An NEContentFilterConfiguration object containing the current filter configuration. The value of this
 * property can change during the lifetime of a filter. Filter implementations can use KVO to be notified when the
 * configuration changes.
 */
@property (readonly) NEFilterProviderConfiguration *filterConfiguration API_AVAILABLE(macos(10.15), ios(9.0)) API_UNAVAILABLE(watchos, tvos);

/*!
 * @method handleReport:
 * @discussion This function is called by the framework when the data provider extension returns a verdict with the report property set to True.
 *     Subclass implementations may override this method to handle the flow report.
 * @param report The report being delivered.
 */
- (void)handleReport:(NEFilterReport *)report API_AVAILABLE(macos(10.15), ios(11.0)) API_UNAVAILABLE(watchos, tvos);

@end

/*!
 * @typedef NEFilterReportFrequency
 * @abstract A NEFilterReportFrequency controls the frequency of periodic reports.
 */
typedef NS_ENUM(NSInteger, NEFilterReportFrequency){
	/*! @const NEFilterReportFrequencyNone No frequency */
	NEFilterReportFrequencyNone,
	/*! @const NEFilterReportFrequencyLow Low frequency, approximately 5 seconds */
	NEFilterReportFrequencyLow,
	/*! @const NEFilterReportFrequencyMedium Medium frequency, approximately 1 second */
	NEFilterReportFrequencyMedium,
	/*! @const NEFilterReportFrequencyHigh High frequency, approximately half a second */
	NEFilterReportFrequencyHigh,
} NS_SWIFT_NAME(NEFilterReport.Frequency) API_AVAILABLE(macos(10.15.4)) API_UNAVAILABLE(ios, watchos, tvos);

/*!
 * @interface NEFilterVerdict
 * @discussion The NEFilterVerdict class declares the programmatic interface for an object that is the verdict for a
 * flow of network data.
 *
 * NEFilterVerdict is part of NetworkExtension.framework
 */
API_AVAILABLE(macos(10.15), ios(9.0)) API_UNAVAILABLE(watchos, tvos)
@interface NEFilterVerdict : NSObject <NSSecureCoding,NSCopying>

/*!
 * @property shouldReport
 * @discussion Whether or not to send a report to the control provider's -[NEFilterProvider handleReport:]
 * method when processing this verdict and when the flow is closed. Since the data provider does not need to wait
 * for a response from the control provider before continuing to process the flow, this is a more efficient way to
 * report a flow to the control provider than returning a "need rules" verdict. If the verdict originates in the
 * control provider, this property has no effect. This property applies when the action taken upon a flow is allow,
 * deny, remediate, or filterData (filterData for new flows only). Setting this flag on a verdict for a socket
 * flow will also cause the data provider's -[NEFilterProvider handleReport:] method to be called when the flow
 * is closed.
 */
@property BOOL shouldReport API_AVAILABLE(ios(11.0), macos(10.15)) API_UNAVAILABLE(watchos, tvos);

@end

/*!
 * @interface NEFilterNewFlowVerdict
 * @discussion The NEFilterNewFlowVerdict declares the programmatic interface of an object that is the verdict for a
 * new flow of network data before any of the flow's data has been seen by the filter.
 *
 * NEFilterNewFlowVerdict is part of NetworkExtension.framework
 */
API_AVAILABLE(macos(10.15), ios(9.0)) API_UNAVAILABLE(watchos, tvos)
@interface NEFilterNewFlowVerdict : NEFilterVerdict <NSSecureCoding,NSCopying>

/*!
 * @property statisticsReportFrequency
 * @discussion The frequency at which the data provider's -[NEFilterProvider handleReport:] method is called with a NEFilterReport instance with an event of NEFilterReportEventFlowStatistics.
 *     The default value is NEFilterReportFrequencyNone, so by default no statistics are reported.
 */
@property NEFilterReportFrequency statisticsReportFrequency API_AVAILABLE(macos(10.15.4)) API_UNAVAILABLE(ios, watchos, tvos);

/*!
 * @method needRulesVerdict
 * @discussion This class method returns a verdict indicating that control provider needs to be asked how to handle
 * the new flow. The control provider can either drop or allow the flow, or update the rules and ask the data provider
 * to decide on the new flow again.
 * @return The NEFilterNewFlowVerdict object.
 */
+ (NEFilterNewFlowVerdict *) needRulesVerdict API_AVAILABLE(ios(9.0)) API_UNAVAILABLE(macos, watchos, tvos);

/*!
 * @method allowVerdict
 * @discussion This class method returns a verdict indicating that the flow should be allowed.
 * @return The NEFilterNewFlowVerdict object.
 */
+ (NEFilterNewFlowVerdict *) allowVerdict API_AVAILABLE(macos(10.15), ios(9.0)) API_UNAVAILABLE(watchos, tvos);

/*!
 * @method dropVerdict
 * @discussion This class method returns a verdict indicating that the flow should be dropped.
 * @return The NEFilterNewFlowVerdict object.
 */
+ (NEFilterNewFlowVerdict *) dropVerdict API_AVAILABLE(macos(10.15), ios(9.0)) API_UNAVAILABLE(watchos, tvos);
/*!
 * @method remediateVerdictWithRemediationURLMapKey:remediationButtonTextMapKey:
 * @discussion This class method returns a verdict indicating that a "content blocked" page should be displayed to
 * the user. The block page should contain a link to the given URL.
 * @param remediationURLMapKey Remediation map key used by data plugin to get remediation url
 * @return The NEFilterNewFlowVerdict object.
 */
+ (NEFilterNewFlowVerdict *)remediateVerdictWithRemediationURLMapKey:(NSString *)remediationURLMapKey
										 remediationButtonTextMapKey:(NSString *)remediationButtonTextMapKey API_AVAILABLE(ios(9.0)) API_UNAVAILABLE(macos, watchos, tvos);

/*!
 * @method URLAppendStringVerdictWithMapKey
 * @discussion This class method returns a verdict indicating that safe search URL for the new should be specified
 * @param urlAppendMapKey URL Append map key to be used by the data plugin to notify what the url should be appended with
 * @return The NEFilterNewFlowVerdict object.
 */
+ (NEFilterNewFlowVerdict *)URLAppendStringVerdictWithMapKey:(NSString *)urlAppendMapKey API_AVAILABLE(ios(9.0)) API_UNAVAILABLE(macos, watchos, tvos);

/*!
 * @method filterDataVerdictWithFilterInbound:peekInboundBytes:filterOutbound:peekOutboundBytes:
 * @discussion This class method returns a new flow verdict indicating that the filter needs to make a decision about
 * a new flow after seeing a portion of the flow's data.
 * @param filterInbound A boolean indicating if the filter needs to see inbound data
 * @param peekInboundBytes The number of inbound bytes that the filter needs to see in the subsequent call to
 * -[NEFilterDataProvider handleInboundDataFromFlow:readBytesStartOffset:readBytes:].
 * @param filterOutbound  boolean indicating if the filter needs to see outbound data
 * @param peekOutboundBytes The number of outbound bytes that the filter needs to see in the subsequent call to
 * -[NEFilterDataProvider handleOutboundDataFromFlow:readBytesStartOffset:readBytes:].
 * @return The new flow verdict.
 */
+ (NEFilterNewFlowVerdict *)filterDataVerdictWithFilterInbound:(BOOL)filterInbound
											  peekInboundBytes:(NSUInteger)peekInboundBytes
												filterOutbound:(BOOL)filterOutbound
											 peekOutboundBytes:(NSUInteger)peekOutboundBytes API_AVAILABLE(macos(10.15), ios(9.0)) API_UNAVAILABLE(watchos, tvos);

/*!
 * @method pauseVerdict
 * @discussion This class method returns a verdict indicating that none of the data provider's handler callbacks shall be called for the flow until after the flow is resumed
 *     by a call to -[NEFilterDataProvider resumeFlow:withVerdict:]. TCP flows may be paused indefinitely. UDP flows will be dropped if not resumed within 10 seconds of
 *     being paused. It is invalid to pause a flow that is already paused.
 * @return The NEFilterNewFlowVerdict object.
 */
+ (NEFilterNewFlowVerdict *)pauseVerdict API_AVAILABLE(macos(10.15)) API_UNAVAILABLE(ios, watchos, tvos);

@end

/*!
 * @interface NEFilterControlVerdict
 * @discussion The NEFilterControlVerdict declares the programmatic interface of an object that is the verdict for a
 * new flow of network data by the control provider.
 *
 * NEFilterControlVerdict is part of NetworkExtension.framework
 */
API_AVAILABLE(ios(9.0)) API_UNAVAILABLE(macos, watchos, tvos)
@interface NEFilterControlVerdict : NEFilterNewFlowVerdict <NSSecureCoding,NSCopying>

/*!
 * @method allowVerdictWithUpdateRules:
 * @discussion This class method returns a verdict indicating that the flow should be allowed to go through, and also
 * tell the data provider whether to update its rules or not.
 * @param updateRules YES if the control provider has updated the rules and wants to communicate that to the data provider
 * @return The NEFilterControlVerdict object.
 */
+ (NEFilterControlVerdict *)allowVerdictWithUpdateRules:(BOOL)updateRules API_AVAILABLE(ios(9.0)) API_UNAVAILABLE(macos, watchos, tvos);

/*!
 * @method dropVerdictWithUpdateRules:
 * @discussion This class method returns a verdict indicating that the flow should be dropped, and also tell the data
 * provider whether to update its rules or not.
 * @param updateRules YES if the control provider has updated the rules and wants to communicate that to the data provider
 * @return The NEFilterControlVerdict object.
 */
+ (NEFilterControlVerdict *)dropVerdictWithUpdateRules:(BOOL)updateRules API_AVAILABLE(ios(9.0)) API_UNAVAILABLE(macos, watchos, tvos);

/*!
 * @method updateRules
 * @discussion This class method returns a verdict indicating that the flow should be handled by the data provider,
 * and the rules needed by the data provider have been set.
 * @return The NEFilterControlVerdict object.
 */
+ (NEFilterControlVerdict *)updateRules API_AVAILABLE(ios(9.0)) API_UNAVAILABLE(macos, watchos, tvos);

@end


/*!
 * @typedef NEFilterAction
 * @abstract A NEFilterAction represents the possible actions taken upon a NEFilterFlow that can be reported by the
 * data provider extension to the control provider extension.
 */
typedef NS_ENUM(NSInteger, NEFilterAction){
	/*! @const NEFilterActionInvalid Invalid action, represents an error */
	NEFilterActionInvalid API_AVAILABLE(macos(10.15), ios(11.0)) = 0,
	/*! @const NEFilterActionAllow Allowing the flow */
	NEFilterActionAllow API_AVAILABLE(macos(10.15), ios(11.0)) = 1,
	/*! @const NEFilterActionDrop Dropping the flow */
	NEFilterActionDrop API_AVAILABLE(macos(10.15), ios(11.0)) = 2,
	/*! @const NEFilterActionRemediate Remediating the flow (a "content blocked" page displayed to the user) */
	NEFilterActionRemediate API_AVAILABLE(ios(11.0)) = 3,
	/*! @const NEFilterActionFilterData Filtering data on the flow */
	NEFilterActionFilterData API_AVAILABLE(macos(10.15), ios(11.0)) = 4,
} API_AVAILABLE(macos(10.15), ios(11.0)) API_UNAVAILABLE(watchos, tvos);

/*!
 * @typedef NEFilterReportEvent
 * @abstract A NEFilterReportEvent represents the event that is being reported by the NEFilterReport.
 */
typedef NS_ENUM(NSInteger, NEFilterReportEvent) {
	/*! @const NEFilterReportEventNewFlow The report is reporting a new flow */
	NEFilterReportEventNewFlow = 1,
	/*! @const NEFilterReportEventDataDecision The report is reporting a pass/block decision made after analyzing some amount of a flow's data */
	NEFilterReportEventDataDecision = 2,
	/*! @const NEFilterReportEventFlowClosed The report is reporting that a flow has been closed */
	NEFilterReportEventFlowClosed = 3,
	/*! @const NEFilterReportEventStatistics The report is reporting the latest statistics of the flow */
	NEFilterReportEventStatistics API_AVAILABLE(macos(10.15.4)) API_UNAVAILABLE(ios, watchos, tvos) = 4,
} NS_SWIFT_NAME(NEFilterReport.Event) API_AVAILABLE(macos(10.15), ios(13.0)) API_UNAVAILABLE(watchos, tvos);

/*!
 * @interface NEFilterReport
 * @discussion The NEFilterReport declares the programmatic interface of an object that is a report of actions taken by
 * the data provider.
 *
 * NEFilterReport is part of NetworkExtension.framework
 */
API_AVAILABLE(macos(10.15), ios(11.0)) API_UNAVAILABLE(watchos, tvos)
@interface NEFilterReport : NSObject <NSSecureCoding,NSCopying>

/*!
 * @property flow
 * @discussion The flow on which the described action was taken.
 */
@property (readonly, nullable) NEFilterFlow *flow API_AVAILABLE(macos(10.15), ios(11.0)) API_UNAVAILABLE(watchos, tvos);

/*!
 * @property action
 * @discussion The action taken upon the reported flow.
 */
@property (readonly) NEFilterAction action API_AVAILABLE(macos(10.15), ios(11.0)) API_UNAVAILABLE(watchos, tvos);

/*!
 * @property event
 * @discussion The type of event that the report is reporting.
 */
@property (readonly) NEFilterReportEvent event API_AVAILABLE(macos(10.15), ios(13.0)) API_UNAVAILABLE(watchos, tvos);

/*!
 * @property bytesInboundCount
 * @discussion The number of inbound bytes received from the flow. This property is only non-zero when the report event is NEFilterReportEventFlowClosed or NEFilterReportEventFlowStatistics.
 */
@property (readonly) NSUInteger bytesInboundCount API_AVAILABLE(macos(10.15), ios(13.0)) API_UNAVAILABLE(watchos, tvos);

/*!
 * @property bytesOutboundCount
 * @discussion The number of outbound bytes sent on the flow. This property is only non-zero when the report event is NEFilterReportEventFlowClosed or NEFilterReportEventFlowStatistics.
 */
@property (readonly) NSUInteger bytesOutboundCount API_AVAILABLE(macos(10.15), ios(13.0)) API_UNAVAILABLE(watchos, tvos);

@end


NS_ASSUME_NONNULL_END

