/*
 * Copyright (C) 2001-2004 Bart Massey and Jamey Sharp.
 * All Rights Reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 * 
 * Except as contained in this notice, the names of the authors or their
 * institutions shall not be used in advertising or otherwise to promote the
 * sale, use or other dealings in this Software without prior written
 * authorization from the authors.
 */

#ifndef __XCBEXT_H
#define __XCBEXT_H

#include "xcb.h"

#ifdef __cplusplus
extern "C" {
#endif

/* xcb_ext.c */

struct xcb_extension_t {
    const char *name;
    int global_id;
};


/* xcb_out.c */

typedef struct {
    size_t count;
    xcb_extension_t *ext;
    uint8_t opcode;
    uint8_t isvoid;
} xcb_protocol_request_t;

enum xcb_send_request_flags_t {
    XCB_REQUEST_CHECKED = 1 << 0,
    XCB_REQUEST_RAW = 1 << 1,
    XCB_REQUEST_DISCARD_REPLY = 1 << 2
};

unsigned int xcb_send_request(xcb_connection_t *c, int flags, struct iovec *vector, const xcb_protocol_request_t *request);


/* xcb_in.c */

void *xcb_wait_for_reply(xcb_connection_t *c, unsigned int request, xcb_generic_error_t **e);
int xcb_poll_for_reply(xcb_connection_t *c, unsigned int request, void **reply, xcb_generic_error_t **error);


/* xcb_util.c */

int xcb_popcount(uint32_t mask);

#ifdef __cplusplus
}
#endif

#endif
