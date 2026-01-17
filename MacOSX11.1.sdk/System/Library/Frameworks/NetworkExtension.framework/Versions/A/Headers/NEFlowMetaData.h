/*
 * Copyright (c) 2016-2018 Apple Inc.
 * All rights reserved.
 */

#ifndef __NE_INDIRECT__
#error "Please import the NetworkExtension module instead of this file directly."
#endif

NS_ASSUME_NONNULL_BEGIN

/*!
 * @interface NEFlowMetaData
 * @discussion The NEFlowMetaData class declares the programmatic interface for an object that contains extra information about a flow.
 */
API_AVAILABLE(macos(10.11), ios(9.0)) API_UNAVAILABLE(tvos) __WATCHOS_PROHIBITED
@interface NEFlowMetaData : NSObject <NSCopying,NSSecureCoding>

/*!
 * @property sourceAppUniqueIdentifier
 * @discussion A byte string that uniquely identifies the binary for each build of the source application of the flow. The data object may be empty in cases where the flow originates from a system process.
 */
@property (readonly) NSData *sourceAppUniqueIdentifier API_AVAILABLE(macos(10.11), ios(9.0)) API_UNAVAILABLE(tvos) __WATCHOS_PROHIBITED;

/*!
 * @property sourceAppSigningIdentifier
 * @discussion A string containing the signing identifier (almost always equivalent to the bundle identifier) of the source app of the flow. The string may be empty in cases where the flow originates from a system process.
 */
@property (readonly) NSString *sourceAppSigningIdentifier API_AVAILABLE(macos(10.11), ios(9.0)) API_UNAVAILABLE(tvos) __WATCHOS_PROHIBITED;

/*!
 *	@property sourceAppAuditToken
 *	@discussion Audit token of the source application of the flow.
 */
@property (readonly, nullable) NSData *sourceAppAuditToken API_AVAILABLE(macos(10.15)) API_UNAVAILABLE(ios, tvos) __WATCHOS_PROHIBITED;

/*!
 * @property filterFlowIdentifier
 * @discussion The identifier of the content filter flow corresponding to this flow.
 */
@property (readonly, nullable) NSUUID *filterFlowIdentifier API_AVAILABLE(macos(10.15.4)) API_UNAVAILABLE(ios, tvos) __WATCHOS_PROHIBITED;

@end

NS_ASSUME_NONNULL_END
