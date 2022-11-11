//
//  path_monitor.h
//  Network
//
//  Copyright (c) 2017-2020 Apple Inc. All rights reserved.
//

#ifndef __NW_PATH_MONITOR_H__
#define __NW_PATH_MONITOR_H__

#ifndef __NW_INDIRECT__
#warning "Please include <Network/Network.h> instead of this file directly."
#endif // __NW_INDIRECT__

#include <Network/path.h>
#include <Network/interface.h>
#include <Network/nw_object.h>

#include <dispatch/dispatch.h>


__BEGIN_DECLS

NW_ASSUME_NONNULL_BEGIN

/*!
 * @typedef nw_path_monitor_t
 * @abstract
 *		The Network Path Monitor allows the caller to fetch the current global path (or
 *		a path restricted to a specific network interface type). The path is delivered
 *		in a block that is called every time the network path changes.
 *
 *		This type supports ARC and the -[description] method. In non-ARC files, use
 *		nw_retain() and nw_release() to retain and release the object.
 */
#ifndef NW_PATH_MONITOR_IMPL
NW_OBJECT_DECL(nw_path_monitor);
#endif // NW_PATH_MONITOR_IMPL

/*!
 * @function nw_path_monitor_create
 *
 * @abstract
 *		Create a default path monitor, that will allow the enumeration of all available
 *		interfaces on the system.
 *
 * @result
 *		Returns an allocated nw_path_monitor_t object on success.
 *		Callers are responsible for deallocating using nw_release(obj) or [obj release].
 *		These objects support ARC.
 *		Returns NULL on failure. Fails due to invalid parameters.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
NW_RETURNS_RETAINED nw_path_monitor_t
nw_path_monitor_create(void);

/*!
 * @function nw_path_monitor_create_with_type
 *
 * @abstract
 *		Create a path monitor specific to an interface type, that will allow the enumeration
 *		of any interface that matches the type on the system.
 *
 * @param required_interface_type
 *		An interface type that will filter any results that the path monitor returns.
 *
 * @result
 *		Returns an allocated nw_path_monitor_t object on success.
 *		Callers are responsible for deallocating using nw_release(obj) or [obj release].
 *		These objects support ARC.
 *		Returns NULL on failure. Fails due to invalid parameters.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
NW_RETURNS_RETAINED nw_path_monitor_t
nw_path_monitor_create_with_type(nw_interface_type_t required_interface_type);

/*!
 * @function nw_path_monitor_prohibit_interface_type
 *
 * @abstract
 *		Prohibit this path monitor from using the provided network interface type.
 *		Call before calling nw_path_monitor_start.
 *
 * @param monitor
 *		The path monitor object.
 *
 * @param interface_type
 *		The interface type to prohibit for the path monitor.
 */
API_AVAILABLE(macos(11.0), ios(14.0), watchos(7.0), tvos(14.0))
void
nw_path_monitor_prohibit_interface_type(nw_path_monitor_t monitor,
										nw_interface_type_t interface_type);

#ifdef __BLOCKS__

/*!
 * @typedef nw_path_monitor_cancel_handler_t
 * @abstract
 *		A block handler to be called when a path monitor is cancelled. This
 *		is used to allow clients to release any objects they have retained in
 *		association with the path monitor.
 */
typedef void (^nw_path_monitor_cancel_handler_t)(void);

/*!
 * @function nw_path_monitor_set_cancel_handler
 * @abstract
 *		Set a handler to be called on the queue provided to nw_path_monitor_set_queue
 *		once cancellation has completed. Once the cancel handler has been called, the
 *		update handler will not fire again.
 *
 * @param monitor
 *		The path monitor object.
 *
 * @param cancel_handler
 *		The block to call upon cancellation. Pass NULL to remove the cancel handler.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
void
nw_path_monitor_set_cancel_handler(nw_path_monitor_t monitor,
								   nw_path_monitor_cancel_handler_t cancel_handler);

/*!
 * @typedef nw_path_monitor_update_handler_t
 * @abstract
 *		A block handler to be called whenever a path monitor has a new snapshot.
 *		This will be called one or more times after calling nw_path_monitor_start.
 */
typedef void (^nw_path_monitor_update_handler_t) (nw_path_t path);

/*!
 * @function nw_path_monitor_set_update_handler
 * @abstract
 *		Sets the client update handler. This block will be called with the
 *		current path when start is called and any time the path changes.
 *
 * @param monitor
 *		The path monitor object.
 *
 * @param update_handler
 *		The block to call when the path changes.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
void
nw_path_monitor_set_update_handler(nw_path_monitor_t monitor,
								   nw_path_monitor_update_handler_t update_handler);

#endif // __BLOCKS__

/*!
 * @function nw_path_monitor_set_queue
 * @abstract
 *		Sets the client update queue. All blocks will be scheduled on
 *		this queue. Call before calling nw_path_monitor_start.
 *
 * @param monitor
 *		The path monitor object.
 *
 * @param queue
 *		The dispatch queue on which to call the update and cancel handlers.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
void
nw_path_monitor_set_queue(nw_path_monitor_t monitor,
						  dispatch_queue_t queue);

/*!
 * @function nw_path_monitor_start
 * @abstract
 *		Starts the path monitor.
 *
 * @param monitor
 *		The path monitor object.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
void
nw_path_monitor_start(nw_path_monitor_t monitor);

/*!
 * @function nw_path_monitor_cancel
 *
 * @abstract
 *		Cancel the path monitor.
 *
 * @param monitor
 *		The path monitor object.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
void
nw_path_monitor_cancel(nw_path_monitor_t monitor);

NW_ASSUME_NONNULL_END

__END_DECLS

#endif /* defined(__NW_PATH_MONITOR_H__) */


