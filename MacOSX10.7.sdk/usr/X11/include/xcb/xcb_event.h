/*
 * Copyright (C) 2008-2009 Julien Danjou <julien@danjou.info>
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
 * @defgroup xcb__event_t XCB Event Functions
 *
 * These functions ease the handling of X events received.
 *
 * @{
 */

#ifndef __XCB_EVENT_H__
#define __XCB_EVENT_H__

#include <xcb/xcb.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Bit mask to find event type regardless of event source.
 *
 * Each event in the X11 protocol contains an 8-bit type code.
 * The most-significant bit in this code is set if the event was
 * generated from a SendEvent request. This mask can be used to
 * determine the type of event regardless of how the event was
 * generated. See the X11R6 protocol specification for details.
 */
#define XCB_EVENT_RESPONSE_TYPE_MASK (0x7f)
#define XCB_EVENT_RESPONSE_TYPE(e)   (e->response_type &  XCB_EVENT_RESPONSE_TYPE_MASK)
#define XCB_EVENT_SENT(e)            (e->response_type & ~XCB_EVENT_RESPONSE_TYPE_MASK)

typedef int (*xcb_generic_event_handler_t)(void *data, xcb_connection_t *c, xcb_generic_event_t *event);
typedef int (*xcb_generic_error_handler_t)(void *data, xcb_connection_t *c, xcb_generic_error_t *error);

typedef struct xcb_event_handler xcb_event_handler_t;
struct xcb_event_handler
{
    xcb_generic_event_handler_t handler;
    void *data;
};

typedef struct xcb_event_handlers xcb_event_handlers_t;
struct xcb_event_handlers
{
    xcb_event_handler_t event[126];
    xcb_event_handler_t error[256];
    xcb_connection_t *c;
};

/**
 * @brief Initialize event handlers data structure.
 * @param c The connection to the X server.
 * @param evenths A pointer to the event handler data structure to initialize.
 */
void xcb_event_handlers_init(xcb_connection_t *c, xcb_event_handlers_t *evenths);

/**
 * @brief Get X connection used in event handlers.
 * @param evenths The event handlers.
 * @return The connection to the X server.
 */
xcb_connection_t *xcb_event_get_xcb_connection(xcb_event_handlers_t *evenths);

/**
 * @brief Wait for event and handle it with event handler.
 * @param evenths The event handlers.
 */
void xcb_event_wait_for_event_loop(xcb_event_handlers_t *evenths);

/**
 * @brief Poll for event and handle it with event handler.
 * @param evenths The event handlers.
 */
void xcb_event_poll_for_event_loop(xcb_event_handlers_t *evenths);

/**
 * @brief Handle an event using event handlers from event handlers data
 * structure.
 * @param evenths The event handlers.
 * @param event The event to handle.
 * @return The return value of the handler, or 0 if no handler exists for this
 * event.
 */
int xcb_event_handle(xcb_event_handlers_t *evenths, xcb_generic_event_t *event);

/**
 * @brief Set an event handler for an event type.
 * @param evenths The event handlers data structure.
 * @param event The event type.
 * @param handler The callback function to call for this event type.
 * @param data Optional data pointer to pass to handler callback function.
 */
void xcb_event_set_handler(xcb_event_handlers_t *evenths, int event, xcb_generic_event_handler_t handler, void *data);

/**
 * @brief Set an error handler for an error type.
 * @param evenths The error handlers data structure.
 * @param error The error type.
 * @param handler The callback function to call for this error type.
 * @param data Optional data pointer to pass to handler callback function.
 */
void xcb_event_set_error_handler(xcb_event_handlers_t *evenths, int error, xcb_generic_error_handler_t handler, void *data);

#define XCB_EVENT_MAKE_EVENT_HANDLER(lkind, ukind) \
static inline void xcb_event_set_##lkind##_handler(xcb_event_handlers_t *evenths, int (*handler)(void *, xcb_connection_t *, xcb_##lkind##_event_t *), void *data) \
{ \
    xcb_event_set_handler(evenths, XCB_##ukind, (xcb_generic_event_handler_t) handler, data); \
}

XCB_EVENT_MAKE_EVENT_HANDLER(key_press, KEY_PRESS)
XCB_EVENT_MAKE_EVENT_HANDLER(key_release, KEY_RELEASE)
XCB_EVENT_MAKE_EVENT_HANDLER(button_press, BUTTON_PRESS)
XCB_EVENT_MAKE_EVENT_HANDLER(button_release, BUTTON_RELEASE)
XCB_EVENT_MAKE_EVENT_HANDLER(motion_notify, MOTION_NOTIFY)
XCB_EVENT_MAKE_EVENT_HANDLER(enter_notify, ENTER_NOTIFY)
XCB_EVENT_MAKE_EVENT_HANDLER(leave_notify, LEAVE_NOTIFY)
XCB_EVENT_MAKE_EVENT_HANDLER(focus_in, FOCUS_IN)
XCB_EVENT_MAKE_EVENT_HANDLER(focus_out, FOCUS_OUT)
XCB_EVENT_MAKE_EVENT_HANDLER(keymap_notify, KEYMAP_NOTIFY)
XCB_EVENT_MAKE_EVENT_HANDLER(expose, EXPOSE)
XCB_EVENT_MAKE_EVENT_HANDLER(graphics_exposure, GRAPHICS_EXPOSURE)
XCB_EVENT_MAKE_EVENT_HANDLER(no_exposure, NO_EXPOSURE)
XCB_EVENT_MAKE_EVENT_HANDLER(visibility_notify, VISIBILITY_NOTIFY)
XCB_EVENT_MAKE_EVENT_HANDLER(create_notify, CREATE_NOTIFY)
XCB_EVENT_MAKE_EVENT_HANDLER(destroy_notify, DESTROY_NOTIFY)
XCB_EVENT_MAKE_EVENT_HANDLER(unmap_notify, UNMAP_NOTIFY)
XCB_EVENT_MAKE_EVENT_HANDLER(map_notify, MAP_NOTIFY)
XCB_EVENT_MAKE_EVENT_HANDLER(map_request, MAP_REQUEST)
XCB_EVENT_MAKE_EVENT_HANDLER(reparent_notify, REPARENT_NOTIFY)
XCB_EVENT_MAKE_EVENT_HANDLER(configure_notify, CONFIGURE_NOTIFY)
XCB_EVENT_MAKE_EVENT_HANDLER(configure_request, CONFIGURE_REQUEST)
XCB_EVENT_MAKE_EVENT_HANDLER(gravity_notify, GRAVITY_NOTIFY)
XCB_EVENT_MAKE_EVENT_HANDLER(resize_request, RESIZE_REQUEST)
XCB_EVENT_MAKE_EVENT_HANDLER(circulate_notify, CIRCULATE_NOTIFY)
XCB_EVENT_MAKE_EVENT_HANDLER(circulate_request, CIRCULATE_REQUEST)
XCB_EVENT_MAKE_EVENT_HANDLER(property_notify, PROPERTY_NOTIFY)
XCB_EVENT_MAKE_EVENT_HANDLER(selection_clear, SELECTION_CLEAR)
XCB_EVENT_MAKE_EVENT_HANDLER(selection_request, SELECTION_REQUEST)
XCB_EVENT_MAKE_EVENT_HANDLER(selection_notify, SELECTION_NOTIFY)
XCB_EVENT_MAKE_EVENT_HANDLER(colormap_notify, COLORMAP_NOTIFY)
XCB_EVENT_MAKE_EVENT_HANDLER(client_message, CLIENT_MESSAGE)
XCB_EVENT_MAKE_EVENT_HANDLER(mapping_notify, MAPPING_NOTIFY)

/** Everyting is ok */
#define XCB_EVENT_ERROR_SUCESS 0
/** Bad request code */
#define XCB_EVENT_ERROR_BAD_REQUEST 1
/** Int parameter out of range */
#define XCB_EVENT_ERROR_BAD_VALUE 2
/** Parameter not a Window */
#define XCB_EVENT_ERROR_BAD_WINDOW 3
/** Parameter not a Pixmap */
#define XCB_EVENT_ERROR_BAD_PIXMAP 4
/** Parameter not an Atom */
#define XCB_EVENT_ERROR_BAD_ATOM 5
/** Parameter not a Cursor */
#define XCB_EVENT_ERROR_BAD_CURSOR 6
/** Parameter not a Font */
#define XCB_EVENT_ERROR_BAD_FONT 7
/** Parameter mismatch */
#define XCB_EVENT_ERROR_BAD_MATCH 8
/** Parameter not a Pixmap or Window */
#define XCB_EVENT_ERROR_BAD_DRAWABLE 9
/* Depending on context:
   - key/button already grabbed
   - attempt to free an illegal
     cmap entry
   - attempt to store into a read-only
     color map entry.
   - attempt to modify the access control
     list from other than the local host.
*/
#define XCB_EVENT_ERROR_BAD_ACCESS 10
/** Insufficient resources */
#define XCB_EVENT_ERROR_BAD_ALLOC 11
/** No such colormap */
#define XCB_EVENT_ERROR_BAD_COLOR 12
/** Parameter not a GC */
#define XCB_EVENT_ERROR_BAD_GC 13
/** Choice not in range or already used */
#define XCB_EVENT_ERROR_BAD_ID_CHOICE 14
/** Font or color name doesn't exist */
#define XCB_EVENT_ERROR_BAD_NAME 15
/** Request length incorrect */
#define XCB_EVENT_ERROR_BAD_LENGTH 16
/** Server is defective */
#define XCB_EVENT_ERROR_BAD_IMPLEMENTATION 17

/**
 * @brief Convert an event reponse type to a label.
 * @param type The event type.
 * @return A string with the event name, or NULL if unknown.
 */
const char * xcb_event_get_label(uint8_t type);

/**
 * @brief Convert an event error type to a label.
 * @param type The erro type.
 * @return A string with the event name, or NULL if unknown or if the event is
 * not an error.
 */
const char * xcb_event_get_error_label(uint8_t type);

/**
 * @brief Convert an event request type to a label.
 * @param type The request type.
 * @return A string with the event name, or NULL if unknown or if the event is
 * not an error.
 */
const char * xcb_event_get_request_label(uint8_t type);

#ifdef __cplusplus
}
#endif

/**
 * @}
 */

#endif /* __XCB_EVENT_H__ */
