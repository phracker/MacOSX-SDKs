//
//  browser.h
//  Network
//
//  Copyright (c) 2016-2019 Apple Inc. All rights reserved.
//

#ifndef __NW_BROWSER_H__
#define __NW_BROWSER_H__

#ifndef __NW_INDIRECT__
#warning "Please include <Network/Network.h> instead of this file directly."
#endif // __NW_INDIRECT__

#include <Network/parameters.h>
#include <Network/browse_descriptor.h>
#include <Network/browse_result.h>
#include <Network/error.h>

NW_ASSUME_NONNULL_BEGIN

__BEGIN_DECLS

/*!
 * @typedef nw_browser_t
 * @abstract
 *		A Network Browser may be used to browse for endpoints described by a
 *		browse descriptor and a parameters object.
 *
 *		It will asynchronously provide callbacks through the browse results changed
 *		handler as endpoints are added, removed, or changed. These endpoints are
 *		presented to the user as browse result objects, which contain additional
 *		information about each endpoint gathered during browsing.
 *
 *		The browser will report its state, which represents if it is actively
 *		browsing or if it encounters an error, through the state changed handler
 *		callback.
 *
 *		This type supports ARC and the -[description] method. In non-ARC files, use
 *		nw_retain() and nw_release() to retain and release the object.
 */
#ifndef NW_BROWSER_IMPL
NW_OBJECT_DECL(nw_browser);
#endif // NW_BROWSER_IMPL

/*!
 * @typedef nw_browser_state_t
 * @abstract
 *		Browser states sent by nw_browser_set_state_changed_handler.
 *		States progress forward and do not move backwards.
 */
typedef enum {

	/*!
	 *	@const nw_browser_state_invalid The state of the browser is not valid.
	 * 		This state will never be delivered in the browser's state update
	 *		handler and can be treated as an unexpected value.
	 */
	nw_browser_state_invalid = 0,

	/*! @const nw_browser_state_ready The browser is ready and able to receive
	 *		endpoint updates. All callbacks from the browse_results_changed_handler
	 *		occur when the browser is in this state.
	 */
	nw_browser_state_ready = 1,

	/*! @const nw_browser_state_failed The browser has irrecoverably failed.
	 *		You should not try to call nw_browser_start() on the browser to restart
	 *		it. Instead, cancel the browser and create a new browser object.
	 */
	nw_browser_state_failed = 2,

	/*! @const nw_browser_state_cancelled The browser has been cancelled by
	 *		the caller. You should not try to call nw_browser_start() on the
	 *		browser to restart it. Instead, create a new browser object.
	 */
	nw_browser_state_cancelled = 3,
} nw_browser_state_t;

/*!
 * @function nw_browser_create
 *
 * @abstract
 *		Creates a new browser object, which can be used to browse for results
 *		matching a browse descriptor.
 *
 * @param descriptor
 *		A browse descriptor object that describes the type of service for which
 *		to browse.
 *
 * @param parameters
 *		Optional parameters to use for the new browser. If NULL, an empty parameters
 *		object is created internally.
 *
 * @result
 *		An instantiated browser object.
 */
API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0), tvos(13.0))
NW_RETURNS_RETAINED nw_browser_t
nw_browser_create(nw_browse_descriptor_t descriptor,
				  _Nullable nw_parameters_t parameters);

/*!
 * @function nw_browser_set_queue
 *
 * @abstract
 *		Sets the client callback queue, on which blocks for events will
 * 		be scheduled. This must be done before calling nw_browser_start().
 *
 * @param browser
 *		The browser object.
 *
 * @param queue
 *		The client's callback queue.
 */
API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0), tvos(13.0))
void
nw_browser_set_queue(nw_browser_t browser,
					 dispatch_queue_t queue);

#ifdef __BLOCKS__

/*!
 * @typedef nw_browser_browse_results_changed_handler_t
 *
 * @abstract
 *		A block called to notify the user of any browse results that changed. To get
 *		the specific list of changes that occurred, call nw_browse_result_get_changes()
 *		with the old and new result.
 *
 * @param old_result
 *		The old value of the browse result. This value was previously provided to
 *		an invocation of the browse_results_changed_handler().
 *
 * @param new_result
 *		The new value of the browse result. This is a new instance of the result
 *		and replaces old_result.
 *
 * @param batch_complete
 *		A flag indicating if this is the last change in this batch. If
 *		batch_complete is true, the browser has no more immediate changes to
 *		report to the user, who should perform any pending UI updates. If
 *		batch_complete is false, the browser has more updates queued, which will
 *		be delivered in subsequent invocations of the browse_results_changed_handler().
 */
typedef void (^nw_browser_browse_results_changed_handler_t) (nw_browse_result_t old_result,
															 nw_browse_result_t new_result,
															 bool batch_complete);

/*!
 * @function nw_browser_set_browse_results_changed_handler
 *
 * @abstract
 *		Sets a callback handler to be invoked when the browser gets an update
 *		for changed browse results. This function must be called before starting
 *		the browser and must not be called after starting the browser.
 *
 * @param browser
 *		The browser object.
 *
 * @param handler
 *		The callback handler that fires when the browser gets an update for a
 *		changed browse result.
 */
API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0), tvos(13.0))
void
nw_browser_set_browse_results_changed_handler(nw_browser_t browser,
												_Nullable nw_browser_browse_results_changed_handler_t handler);

/*!
 * @typedef nw_browser_state_changed_handler_t
 *
 * @abstract
 *		A block called when the browser changes state.
 *
 * @param state
 *		The new state of the browser.
 *
 * @param error
 *		An optional error that is associated with the new state. For example, if the
 *		browser encounters a DNS error, the callback will pass nw_browser_state_failed
 * 		as the new state and the DNS error as the error.
 */
typedef void (^nw_browser_state_changed_handler_t)(nw_browser_state_t state,
												   _Nullable nw_error_t error);

/*!
 * @function nw_browser_set_state_changed_handler
 *
 * @abstract
 *		Sets the state changed handler. For clients that need to perform cleanup
 *		when the browser has been cancelled, the nw_browser_state_cancelled state
 *		will be delivered last. This function must be called before starting the
 *		browser and must not be called after starting the browser.
 *
 * @param browser
 *		The browser object.
 *
 * @param state_changed_handler
 *		The state changed handler to call when the browser state changes.
 *		Pass NULL to remove the event handler.
 */
API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0), tvos(13.0))
void
nw_browser_set_state_changed_handler(nw_browser_t browser,
									 _Nullable nw_browser_state_changed_handler_t state_changed_handler);

#endif // __BLOCKS__

/*!
 * @function nw_browser_start
 *
 * @abstract
 *		Starts the browser, which begins browsing for available endpoints.
 * 		You must call nw_browser_set_queue() before starting the browser.
 *
 * @param browser
 *		The browser object.
 */
API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0), tvos(13.0))
void
nw_browser_start(nw_browser_t browser);

/*!
 * @function nw_browser_cancel
 *
 * @abstract
 *		Cancels the browser. The process of cancellation will be completed
 *		asynchronously, and the final callback event delivered to the caller
 *		will be a state update with a value of nw_browser_state_cancelled.
 *		Once this update is delivered, the caller may clean up any associated
 *		memory or objects.
 *
 * @param browser
 *		The browser object.
 */
API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0), tvos(13.0))
void
nw_browser_cancel(nw_browser_t browser);

/*!
 * @function nw_browser_copy_parameters
 *
 * @abstract
 *		Returns a copy of the parameters passed to nw_browser_create().
 *
 * @param browser
 *		The browser object.
 *
 * @result
 *		Returns an nw_parameters_t object.
 */
API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0), tvos(13.0))
NW_RETURNS_RETAINED nw_parameters_t
nw_browser_copy_parameters(nw_browser_t browser);

/*!
 * @function nw_browser_copy_browse_descriptor
 *
 * @abstract
 *		Returns a copy of the browse_descriptor passed to nw_browser_create().
 *
 * @param browser
 *		The browser object.
 *
 * @result
 *		Returns a copy of the browse_descriptor passed to nw_browser_create().
 */
API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0), tvos(13.0))
NW_RETURNS_RETAINED nw_browse_descriptor_t
nw_browser_copy_browse_descriptor(nw_browser_t browser);

__END_DECLS

NW_ASSUME_NONNULL_END

#endif /* defined(__NW_BROWSER_H__) */
