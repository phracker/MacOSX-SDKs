/*
 * Copyright (C) 2008 Julien Danjou <julien@danjou.info>
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use, copy,
 * modify, merge, publish, distribute, sublicense, and/or sell copies
 * of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY
 * CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF
 * CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
 * WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * Except as contained in this notice, the names of the authors or
 * their institutions shall not be used in advertising or otherwise to
 * promote the sale, use or other dealings in this Software without
 * prior written authorization from the authors.
 */

/**
 * @defgroup xcb__property_t XCB Property Functions
 *
 * These functions ease the handling of X propertiess received.
 *
 * @{
 */

#ifndef __XCB_PROPERTY_H__
#define __XCB_PROPERTY_H__

#include "xcb_event.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct xcb_property_handlers xcb_property_handlers_t;
typedef int (*xcb_generic_property_handler_t)(void *data, xcb_connection_t *c, uint8_t state, xcb_window_t window, xcb_atom_t atom, xcb_get_property_reply_t *property);

typedef struct {
	uint32_t                       long_len;
	xcb_generic_property_handler_t handler;
	void                          *data;
} xcb_property_handler_t;

typedef struct xcb_property_handler_node xcb_property_handler_node_t;
struct xcb_property_handler_node {
	xcb_property_handler_node_t *next;
	xcb_atom_t     name;
	xcb_property_handler_t h;
};

struct xcb_property_handlers {
	xcb_property_handler_node_t *head;
	xcb_property_handler_t      def;
	xcb_event_handlers_t        *evenths;
};

/**
 * @brief Get any property from a window, from any format.
 * @param c The connection to the X server.
 * @param del Boolean value that determines whether the property is deleted.
 * @param window The window to get property from.
 * @param name The property atom name.
 * @param long_len The maximum length of the property.
 * @return A cookie.
 */
xcb_get_property_cookie_t xcb_get_any_property(xcb_connection_t *c,
                                               uint8_t del,
                                               xcb_window_t window,
                                               xcb_atom_t name,
                                               uint32_t long_len);

/**
 * @see xcb_get_any_property
 */
xcb_get_property_cookie_t xcb_get_any_property_unchecked(xcb_connection_t *c,
                                                         uint8_t del,
                                                         xcb_window_t window,
                                                         xcb_atom_t name,
                                                         uint32_t long_len);
/**
 * @brief Initialize a property handlers structure.
 * @param prophs The property handlers data structure pointer.
 * @param evenths The event handlers.
 */
void xcb_property_handlers_init(xcb_property_handlers_t *prophs, xcb_event_handlers_t *evenths);

/**
 * @brief Wipe a property handler structure.
 * @param prophs The property handlers data structure pointer.
 */
void xcb_property_handlers_wipe(xcb_property_handlers_t *prophs);

/**
 * @brief Get a event handlers from a property handlers data structure.
 * @param prophs The property handlers.
 * @return The event handlers data structure which was set if any, NULL
 * otherwise.
 */
xcb_event_handlers_t *xcb_property_get_event_handlers(xcb_property_handlers_t *prophs);

/**
 * @brief Set a property handler for an event.
 * @param prophs The property handlers.
 * @param name The property atom name.
 * @param long_len The maximum length of the property value that will be
 * handled.
 * @param handler The handler callback function.
 * @param data Optional data that will be passed as argument of the handler
 * callback function. Can be NULL safely if you do not need it.
 * @return Return 1 on success, 0 otherwise.
 */
uint8_t xcb_property_set_handler(xcb_property_handlers_t *prophs,
                                 xcb_atom_t name,
                                 uint32_t long_len,
                                 xcb_generic_property_handler_t handler,
                                 void *data);

/**
 * @brief Set the default property handler.
 * If a property does not have its own handler function, this one will be
 * used.
 * @param prophs The property handlers.
 * @param name The property atom name.
 * @param long_len The maximum length of the property value that will be
 * handled.
 * @param handler The handler callback function.
 * @param data Optional data that will be passed as argument of the handler
 * callback function. Can be NULL safely if you do not need it.
 * @return Return 1 on success, 0 otherwise.
 */
uint8_t xcb_property_set_default_handler(xcb_property_handlers_t *prophs, uint32_t long_len, xcb_generic_property_handler_t handler, void *data);

/**
 * @brief Notify that a property has changed and call handler function callback as needed.
 * @param prophs The property handlers.
 * @param state The property state.
 * @param window The window.
 * @param atom The property atom name.
 */
int xcb_property_changed(xcb_property_handlers_t *prophs, uint8_t state, xcb_window_t window, xcb_atom_t atom);

#ifdef __cplusplus
}
#endif

/**
 * @}
 */

#endif /* __XCB_PROPERTY_H__ */
