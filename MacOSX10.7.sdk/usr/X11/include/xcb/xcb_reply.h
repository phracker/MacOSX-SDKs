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
 * @defgroup xcb__reply_t XCB Reply Functions
 *
 * These functions ease the usage of asynchronous possibility of XCB about
 * the reply retrieve of sent requests.
 *
 * @{
 */

#ifndef __XCB_REPLY_H__
#define __XCB_REPLY_H__

#include <xcb/xcb.h>
#include <pthread.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef void (*xcb_generic_reply_handler_t)(void *data, xcb_connection_t *c, xcb_generic_reply_t *reply, xcb_generic_error_t *error);

struct xcb_reply_node
{
    struct xcb_reply_node *next;
    unsigned int request;
    xcb_generic_reply_handler_t handler;
    void *data;
    char handled;
};

struct xcb_reply_handlers
{
    pthread_mutex_t lock;
    pthread_cond_t cond;
    struct xcb_reply_node *head;
    xcb_connection_t *c;
    pthread_t thread;
};

typedef struct xcb_reply_handlers xcb_reply_handlers_t;

/**
 * @brief Initialize a reply handlers structure.
 * @param c The connection to the X server.
 * @param h The reply handlers.
 */
void xcb_reply_handlers_init(xcb_connection_t *c, xcb_reply_handlers_t *h);

/**
 * @brief Get the connection to the X server used in reply handlers.
 * @param h The reply handlers data structure.
 * @return The connection to the X server.
 */
xcb_connection_t *xcb_reply_get_xcb_connection(xcb_reply_handlers_t *h);

/**
 * @brief Poll for reply using reply handlers.
 * @param h The reply handlers data structure.
 * @return The value return by the handler callback function, or 0 if no
 * handler was found.
 */
int xcb_reply_poll_for_reply(xcb_reply_handlers_t *h);

/**
 * @brief Start reply handling thread.
 * This thread will run forever until it is stop with xcb_reply_stop_thread.
 * @param h The reply handlers.
 */
void xcb_reply_start_thread(xcb_reply_handlers_t *h);

/**
 * @brief Stop reply handling thread.
 * @param h The reply handlers.
 */
void xcb_reply_stop_thread(xcb_reply_handlers_t *h);

/**
 * @brief Add a reply handler.
 * @param h The reply handlers data structure to fill.
 * @param request The request identifier.
 * @param handler The handler to call for this request.
 * @param data Optional data passed to the callback function handling request.
 */
void xcb_reply_add_handler(xcb_reply_handlers_t *h, unsigned int request, xcb_generic_reply_handler_t handler, void *data);

#ifdef __cplusplus
}
#endif

/**
 * @}
 */

#endif /* __XCB_REPLY_H__ */
