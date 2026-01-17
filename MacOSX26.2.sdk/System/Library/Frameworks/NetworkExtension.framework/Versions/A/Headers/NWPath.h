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

/**
 * DEPRECATION NOTICE
 *
 * NW object wrappers are hidden in Swift 6. To continue accessing them, you
 * can prepend double underscores to the symbol name.
 */

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
}
API_DEPRECATED("Use `nw_path_status_t` in Network framework instead, see deprecation notice in <NetworkExtension/NWPath.h>", macos(10.11, 15.0), ios(9.0, 18.0), tvos(17.0, 18.0), visionos(1.0, 2.0))
API_UNAVAILABLE(watchos);

/*!
 * @interface NWPath
 * @discussion A network path, represented with NWPath, expresses the viability status and
 *		properties of the path that a networking connection will take on the device. For example,
 *		if the path status is NWPathStatusSatisfied, then a connection could use that path.
 */
API_DEPRECATED("Use `nw_path_t` in Network framework instead, see deprecation notice in <NetworkExtension/NWPath.h>", macos(10.11, 15.0), ios(9.0, 18.0), tvos(17.0, 18.0), visionos(1.0, 2.0))
API_UNAVAILABLE(watchos)
@interface NWPath : NSObject

/*!
 * @property status
 * @discussion The evaluated NWPathStatus of the NWPath.
 */
@property (nonatomic, readonly) NWPathStatus status
API_DEPRECATED("Use `nw_path_get_status` in Network framework instead, see deprecation notice in <NetworkExtension/NWPath.h>", macos(10.11, 15.0), ios(9.0, 18.0), tvos(17.0, 18.0), visionos(1.0, 2.0))
API_UNAVAILABLE(watchos);

/*!
 * @property expensive
 * @discussion Returns YES if the path is considered expensive, as when using a cellular data plan.
 */
@property (nonatomic, readonly, getter=isExpensive) BOOL expensive
API_DEPRECATED("Use `nw_path_is_expensive` in Network framework instead, see deprecation notice in <NetworkExtension/NWPath.h>", macos(10.11, 15.0), ios(9.0, 18.0), tvos(17.0, 18.0), visionos(1.0, 2.0))
API_UNAVAILABLE(watchos);

/*!
 * @property constrained
 * @discussion Returns YES if the path is considered constrained, as when it is in save data mode.
 */
@property (nonatomic, readonly, getter=isConstrained) BOOL constrained
API_DEPRECATED("Use `nw_path_is_constrained` in Network framework instead, see deprecation notice in <NetworkExtension/NWPath.h>", macos(10.11, 15.0), ios(9.0, 18.0), tvos(17.0, 18.0), visionos(1.0, 2.0))
API_UNAVAILABLE(watchos);

/*!
 * @method isEqualToPath:
 * @param path An NWPath object to compare.
 * @return YES if the two path objects have the same content, NO otherwise.
 */
- (BOOL)isEqualToPath:(NWPath *)path
API_DEPRECATED("Use `nw_path_is_equal` in Network framework instead, see deprecation notice in <NetworkExtension/NWPath.h>", macos(10.11, 15.0), ios(9.0, 18.0), tvos(17.0, 18.0), visionos(1.0, 2.0))
API_UNAVAILABLE(watchos);

@end

NS_ASSUME_NONNULL_END

#endif // __NWPath_h_

#endif // __NE_TAPI__
