/*
 * Copyright (c) 2015-2018 Apple Inc.
 * All rights reserved.
 */

#ifndef __NE_INDIRECT__
#error "Please import the NetworkExtension module instead of this file directly."
#endif

#import <NetworkExtension/NEFilterProvider.h>

@class NEFilterFlow;

NS_ASSUME_NONNULL_BEGIN

/*!
 * @file NEFilterControlProvider.h
 * @discussion This file declares the NEFilterControlProvider API. The NEFilterControlProvider API is used to implement the portion of a custom content filter that is responsible for installing the filtering rules on the device.
 */

/*!
 * @interface NEFilterControlProvider
 * @discussion The NEFilterControlProvider class declares the programmatic interface for an object that is responsible for installing filtering rules on the device.
 */
API_AVAILABLE(ios(9.0)) API_UNAVAILABLE(macos, tvos) __WATCHOS_PROHIBITED
@interface NEFilterControlProvider : NEFilterProvider

/*!
 * @property remediationMap
 * @discussion A dictionary containing custom strings to be inserted into the "content blocked" page displayed in WebKit. Each key in this dictionary corresponds to a string in the "content blocked" page. The value of each key is a dictionary that maps keys to the custom strings to be inserted into the "content blocked" page. The keys for the sub-dictionaries are defined by the control provider. When the data provider creates a "remediate" verdict using [NEFilterDataVerdict remediateVerdictWithRemediationURLMapKey:remediationButtonTextMapKey:], it passes the key corresponding to the custom string to be inserted into the "content blocked" page.

	Here is a sample remediationMap dictionary:

	remediationMap = @{ NEFilterProviderRemediationMapRemediationURLs :
							@{
								@"RemediateKey1" : @"http://www.remediation_url_1.com",
								@"RemediateKey2" : @"http://www.remediation_url_2.com"
							 },
						NEFilterProviderRemediationMapRemediationButtonTexts :
							@{
								@"RemediationButtonText1" : @"Remediate URL"
							 }
					  };

 */
@property (copy, nullable) NSDictionary<NSString *, NSDictionary<NSString *, NSObject *> *> *remediationMap API_AVAILABLE(ios(9.0)) API_UNAVAILABLE(macos, tvos) __WATCHOS_PROHIBITED;

/*!
 * @property URLAppendStringMap
 * @discussion A dictionary containing strings to be appended to URLs.
 */
@property (copy, nullable) NSDictionary<NSString *, NSString *> *URLAppendStringMap API_AVAILABLE(ios(9.0)) API_UNAVAILABLE(macos, tvos) __WATCHOS_PROHIBITED;

/*!
 * @method handleRemediationForFlow:completionHandler:
 * @discussion This function is called by the framework when the NEFilterDataProvider indicates that the filtering verdict for the given flow is NEFilterRemediateVerdictNeedRules. Subclass implementations must override this method and implement whatever steps are necessary to remediate the given flow.
 * @param flow An NEFilterFlow object containing details about the flow that requires remediation.
 * @param completionHandler A block that must be called when the NEFilterControlProvider is ready for the NEFilterDataProvider to re-process the new flow. NEFilterControlVerdict stores the verdict through which the control provider determines if a flow needs to be dropped or allowed. The verdict also indicates if the control plugin wants the data plugin to update its rules and handle the verdict.
 */
- (void)handleRemediationForFlow:(NEFilterFlow *)flow completionHandler:(void (^)(NEFilterControlVerdict *))completionHandler API_AVAILABLE(ios(9.0)) API_UNAVAILABLE(macos, tvos) __WATCHOS_PROHIBITED;


/*!
 * @method handleNewFlow:completionHandler:
 * @discussion This function is called by the framework when the NEFilterDataProvider indicates that the filtering verdict for the given flow is NEFilterNewFlowVerdictNeedRules. Subclass implementations must override this method and implement whatever steps are necessary to fetch new rules pertaining to the given flow and place them on disk in a location accessible by the NEFilterDataProvider.
 * @param flow An NEFilterFlow object containing details about the flow that requires a rules update.
 * @param completionHandler A block that must be called when the NEFilterControlProvider is ready for the NEFilterDataProvider to re-process the new flow. NEFilterControlVerdict stores the verdict through which the control provider determines if a flow needs to be dropped or allowed. The verdict also indicates if the control plugin wants the data plugin to update its rules and handle the verdict.
 */
- (void)handleNewFlow:(NEFilterFlow *)flow completionHandler:(void (^)(NEFilterControlVerdict *))completionHandler API_AVAILABLE(macos(10.15), ios(9.0)) API_UNAVAILABLE(tvos) __WATCHOS_PROHIBITED;

/*!
 * @method notifyRulesChanged
 * @discussion This function is called by filter control implementations to notify the data provider "out of band" that the rules changed.
 */
- (void)notifyRulesChanged API_AVAILABLE(ios(9.0)) API_UNAVAILABLE(macos, tvos) __WATCHOS_PROHIBITED;

@end

NS_ASSUME_NONNULL_END

