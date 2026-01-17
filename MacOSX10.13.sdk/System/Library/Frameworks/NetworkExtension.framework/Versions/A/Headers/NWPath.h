//
//  NWPath.h
//  Network
//
//  Copyright (c) 2014-2016 Apple Inc. All rights reserved.
//

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
} NS_AVAILABLE(10_11, 9_0);

/*!
 * @interface NWPath
 * @discussion A network path, represented with NWPath, expresses the viability status and
 *		properties of the path that a networking connection will take on the device. For example,
 *		if the path status is NWPathStatusSatisfied, then a connection could use that path.
 */
NS_CLASS_AVAILABLE(10_11, 9_0)
@interface NWPath : NSObject

/*!
 * @property status
 * @discussion The evaluated NWPathStatus of the NWPath.
 */
@property (readonly) NWPathStatus status NS_AVAILABLE(10_11, 9_0);

/*!
 * @property expensive
 * @discussion Returns YES is the path is considered expensive, as when using a cellular data plan.
 */
@property (readonly, getter=isExpensive) BOOL expensive NS_AVAILABLE(10_11, 9_0);

/*!
 * @method isEqualToPath:
 * @param path An NWPath object to compare.
 * @return YES if the two path objects have the same content, NO otherwise.
 */
- (BOOL)isEqualToPath:(NWPath *)path NS_AVAILABLE(10_11, 9_0);

@end

NS_ASSUME_NONNULL_END

#endif // __NWPath_h_
