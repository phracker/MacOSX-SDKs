//
//  NWPath.h
//  Network
//
//  Copyright (c) 2014-2016, 2018 Apple Inc. All rights reserved.
//

#ifndef __NE_TAPI__

#ifndef __NE_INDIRECT__
#error "Please import the NetworkExtension module instead of this file directly."
#endif // __NE_INDIRECT__

#ifndef __NWPath_h_
#define __NWPath_h_


NS_ASSUME_NONNULL_BEGIN

/*!
 * @typedef NWPathStatus
 * @abstract Path status values
 */
typedef NS_ENUM(NSInteger, NWPathStatus) {
	/*! @const NWPathStatusInvalid The path cannot be evaluated. */
	NWPathStatusInvalid = 0,
	/*! @const NWPathStatusSatisfied The path is ready to be used for traffic. */
	NWPathStatusSatisfied = 1,
	/*! @const NWPathStatusUnsatisfied The network for this connection is not available. */
	NWPathStatusUnsatisfied = 2,
	/*! @const NWPathStatusSatisfiable The path may become satisfied upon
	 *		a connection attempt. */
	NWPathStatusSatisfiable = 3,
} API_AVAILABLE(macos(10.11), ios(9.0)) API_UNAVAILABLE(tvos) __WATCHOS_PROHIBITED;

/*!
 * @interface NWPath
 * @discussion A network path, represented with NWPath, expresses the viability status and
 *		properties of the path that a networking connection will take on the device. For example,
 *		if the path status is NWPathStatusSatisfied, then a connection could use that path.
 */
API_AVAILABLE(macos(10.11), ios(9.0)) API_UNAVAILABLE(tvos) __WATCHOS_PROHIBITED
@interface NWPath : NSObject

/*!
 * @property status
 * @discussion The evaluated NWPathStatus of the NWPath.
 */
@property (nonatomic, readonly) NWPathStatus status API_AVAILABLE(macos(10.11), ios(9.0)) API_UNAVAILABLE(tvos) __WATCHOS_PROHIBITED;

/*!
 * @property expensive
 * @discussion Returns YES if the path is considered expensive, as when using a cellular data plan.
 */
@property (nonatomic, readonly, getter=isExpensive) BOOL expensive API_AVAILABLE(macos(10.11), ios(9.0)) API_UNAVAILABLE(tvos) __WATCHOS_PROHIBITED;

/*!
 * @property constrained
 * @discussion Returns YES if the path is considered constrained, as when it is in save data mode.
 */
@property (nonatomic, readonly, getter=isConstrained) BOOL constrained API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0), tvos(13.0));

/*!
 * @method isEqualToPath:
 * @param path An NWPath object to compare.
 * @return YES if the two path objects have the same content, NO otherwise.
 */
- (BOOL)isEqualToPath:(NWPath *)path API_AVAILABLE(macos(10.11), ios(9.0)) API_UNAVAILABLE(tvos) __WATCHOS_PROHIBITED;

@end

NS_ASSUME_NONNULL_END

#endif // __NWPath_h_

#endif // __NE_TAPI__
