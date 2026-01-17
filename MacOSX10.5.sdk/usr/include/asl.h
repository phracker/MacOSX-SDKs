/*
 * Copyright (c) 2004 Apple Computer, Inc. All rights reserved.
 *
 * @APPLE_LICENSE_HEADER_START@
 * 
 * "Portions Copyright (c) 2004 Apple Computer, Inc.  All Rights
 * Reserved.  This file contains Original Code and/or Modifications of
 * Original Code as defined in and that are subject to the Apple Public
 * Source License Version 1.0 (the 'License').  You may not use this file
 * except in compliance with the License.  Please obtain a copy of the
 * License at http://www.apple.com/publicsource and read it before using
 * this file.
 * 
 * The Original Code and all software distributed under the License are
 * distributed on an 'AS IS' basis, WITHOUT WARRANTY OF ANY KIND, EITHER
 * EXPRESS OR IMPLIED, AND APPLE HEREBY DISCLAIMS ALL SUCH WARRANTIES,
 * INCLUDING WITHOUT LIMITATION, ANY WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE OR NON-INFRINGEMENT.  Please see the
 * License for the specific language governing rights and limitations
 * under the License."
 * 
 * @APPLE_LICENSE_HEADER_END@
 */

#ifndef __ASL_H__
#define __ASL_H__

#include <stdint.h>
#include <stdarg.h>
#include <sys/cdefs.h>

typedef struct __aslclient *aslclient;
typedef struct __aslmsg *aslmsg;
typedef struct __aslresponse *aslresponse;

/*
 * Log levels of the message
 */
#define ASL_LEVEL_EMERG   0
#define ASL_LEVEL_ALERT   1
#define ASL_LEVEL_CRIT    2
#define ASL_LEVEL_ERR     3
#define ASL_LEVEL_WARNING 4
#define ASL_LEVEL_NOTICE  5
#define ASL_LEVEL_INFO    6
#define ASL_LEVEL_DEBUG   7

/*
 * Corresponding level strings
 */
#define ASL_STRING_EMERG	"Emergency"
#define ASL_STRING_ALERT	"Alert"
#define ASL_STRING_CRIT		"Critical"
#define ASL_STRING_ERR		"Error"
#define ASL_STRING_WARNING  "Warning"
#define ASL_STRING_NOTICE   "Notice"
#define ASL_STRING_INFO		"Info"
#define ASL_STRING_DEBUG	"Debug"

/*
 * Attribute value comparison operations
 */
#define ASL_QUERY_OP_CASEFOLD      0x0010
#define ASL_QUERY_OP_PREFIX		   0x0020
#define ASL_QUERY_OP_SUFFIX		   0x0040
#define ASL_QUERY_OP_SUBSTRING     0x0060
#define ASL_QUERY_OP_NUMERIC       0x0080
#define ASL_QUERY_OP_REGEX         0x0100

#define ASL_QUERY_OP_EQUAL         0x0001
#define ASL_QUERY_OP_GREATER       0x0002
#define ASL_QUERY_OP_GREATER_EQUAL 0x0003
#define ASL_QUERY_OP_LESS          0x0004
#define ASL_QUERY_OP_LESS_EQUAL    0x0005
#define ASL_QUERY_OP_NOT_EQUAL     0x0006
#define ASL_QUERY_OP_TRUE          0x0007

/* 
 * Attributes of all messages.
 * The following attributes are attached to log messages,
 * and are preserved in the order listed.
 * Additional attributes may be added as desired, and are
 * appended in the order that they are defined.
 */
#define ASL_KEY_TIME      "Time"     /* Timestamp (see ctime(3)).  Set automatically */
#define ASL_KEY_HOST      "Host"     /* Sender's address (set by the server) */
#define ASL_KEY_SENDER    "Sender"   /* Sender's identification string.  Default is process name */
#define ASL_KEY_FACILITY  "Facility" /* Sender's facility.  Default is "user". */
#define ASL_KEY_PID       "PID"      /* Sending process ID encoded as a string.  Set automatically */
#define ASL_KEY_UID       "UID"      /* UID that sent the log message (set by the server) */
#define ASL_KEY_GID       "GID"      /* GID that sent the log message (set by the server) */
#define ASL_KEY_LEVEL     "Level"    /* Log level number encoded as a string.  See levels above */
#define ASL_KEY_MSG       "Message"  /* Actual message that will be logged */

/* 
 * Message Types
 */
#define ASL_TYPE_MSG    0
#define ASL_TYPE_QUERY  1

/* Macros to create bitmasks for filter settings - see asl_set_filter */
#define	ASL_FILTER_MASK(level) (1 << (level))
#define	ASL_FILTER_MASK_UPTO(level) ((1 << ((level) + 1)) - 1)

/* Individual filter masks */
#define ASL_FILTER_MASK_EMERG   0x01
#define ASL_FILTER_MASK_ALERT   0x02
#define ASL_FILTER_MASK_CRIT    0x04
#define ASL_FILTER_MASK_ERR     0x08
#define ASL_FILTER_MASK_WARNING 0x10
#define ASL_FILTER_MASK_NOTICE  0x20
#define ASL_FILTER_MASK_INFO    0x40
#define ASL_FILTER_MASK_DEBUG   0x80

/* Options to asl_open */
#define ASL_OPT_STDERR		0x00000001
#define ASL_OPT_NO_DELAY    0x00000002
#define ASL_OPT_NO_REMOTE   0x00000004

__BEGIN_DECLS

/*
 * asl_open: initialize a syslog connection
 * This call is optional in most cases.  The library will perform any
 * necessary initializations on the fly.  A call to asl_open() is required
 * if optional settings must be made before messages are sent to the server.
 * These include setting the client filter and managing additional output
 * file descriptors.  Note that the default setting of the client filter is
 * ASL_FILTER_MASK_UPTO(ASL_LEVEL_NOTICE), so ASL_LEVEL_DEBUG and ASL_LEVEL_INFO
 * messages are not sent to the server by default.
 * 
 * Options (defined above) may be set using the opts parameter. They are:
 *   ASL_OPT_STDERR    - adds stderr as an output file descriptor
 *   ASL_OPT_NO_DELAY  - connects to the server immediately
 *   ASL_OPT_NO_REMOTE - disables the remote-control mechanism for adjusting
 *                       filter levers for processes using e.g. syslog -c ...
 */
aslclient asl_open(const char *ident, const char *facility, uint32_t opts);

/*
 * Shuts down the current connection to the server.
 */
void asl_close(aslclient asl);

/*
 * asl_add_file: write log messages to the given file descriptor
 * Log messages will be written to this file as well as to the server.
 */
int asl_add_log_file(aslclient asl, int fd);

/*
 * asl_remove_file: stop writing log messages to the given file descriptor
 * The file descripter is not closed by this routine.
 */
int asl_remove_log_file(aslclient asl, int fd);

/*
 * Set a filter for messages being sent to the server
 * The filter is a bitmask representing priorities.  The ASL_FILTER_MASK
 * macro may be used to convert a priority level into a bitmask for that
 * level.  The ASL_FILTER_MASK_UPTO macro creates a bitmask for all
 * priorities up to and including a given priority.
 * Messages with priority levels that do not have a corresponding bit 
 * set in the filter are not sent to the server, although they will be
 * sent to any file descripters added with asl_add_log_file().
 * The default setting is ASL_FILTER_MASK_UPTO(ASL_LEVEL_NOTICE).
 * Returns the previous filter value.
 */
int asl_set_filter(aslclient asl, int f);

/*
 * asl_key: examine attribute keys
 * returns the key of the nth attribute in a message (beginning at zero)
 * returns NULL if the message has fewer attributes
 */
const char *asl_key(aslmsg msg, uint32_t n);

/*
 * asl_new: create a new log message.
 */
aslmsg asl_new(uint32_t type);

/*
 * asl_set: set attributes of a message 
 * msg:  an aslmsg
 * key:  attribute key 
 * value:  attribute value
 * returns 0 for success, non-zero for failure
 */
int asl_set(aslmsg msg, const char *key, const char *value);

/*
 * asl_unset: remove attributes of a message 
 * msg:  an aslmsg
 * key:  attribute key 
 * returns 0 for success, non-zero for failure
 */
int asl_unset(aslmsg msg, const char *key);

/*
 * asl_get: get attribute values from a message 
 * msg:  an aslmsg
 * key:  attribute key 
 * returns the attribute value
 * returns NULL if the message does not contain the key
 */
const char *asl_get(aslmsg msg, const char *key);

/*
 * asl_log: log a message with a particular log level 
 * msg:  an aslmsg
 *       msg may be NULL, in which case a new message will be
 *       created and sent using default attributes.
 * level: the log level
 * format: A formating string followed by a list of arguments, like printf()
 * returns 0 for success, non-zero for failure
 */
#ifdef __DARWIN_LDBL_COMPAT2
int asl_log(aslclient asl, aslmsg msg, int level, const char *format, ...) __DARWIN_LDBL_COMPAT2(asl_log) __printflike(4, 5);
#else
int asl_log(aslclient asl, aslmsg msg, int level, const char *format, ...) __printflike(4, 5);
#endif

/*
 * asl_vlog: Similar to asl_log, but taking a va_list instead of a list of
 * arguments.
 * msg:  an aslmsg
 *       msg may be NULL, in which case a new message will be
 *       created and sent using default attributes.
 * level: the log level of the associated message
 * format: A formating string followed by a list of arguments, like vprintf()
 * returns 0 for success, non-zero for failure
 */
#ifdef __DARWIN_LDBL_COMPAT2
int asl_vlog(aslclient asl, aslmsg msg, int level, const char *format, va_list ap) __DARWIN_LDBL_COMPAT2(asl_vlog) __printflike(4, 0);
#else
int asl_vlog(aslclient asl, aslmsg msg, int level, const char *format, va_list ap) __printflike(4, 0);
#endif

/*
 * asl_send: send a message 
 * This routine may be used instead of asl_log() or asl_vlog() if asl_set() 
 * has been used to set all of a message's attributes.
 * msg:  an aslmsg
 * returns 0 for success, non-zero for failure
 */
int asl_send(aslclient asl, aslmsg msg);

/*
 * asl_free: free a message 
 * msg:  an aslmsg to free
 */
void asl_free(aslmsg msg);

/*
 * asl_set_query: set arbitrary parameters of a query
 * Similar to als_set, but allows richer query operations.
 * See ASL_QUERY_OP_* above.
 * msg:  an aslmsg
 * key:  attribute key 
 * value:  attribute value
 * op:  an operation from the set above.
 * returns 0 for success, non-zero for failure
 */
int asl_set_query(aslmsg msg, const char *key, const char *value, uint32_t op);

/*
 * asl_search: Search for messages matching the criteria described
 * by the aslmsg .  The caller should set the attributes to match using
 * asl_set_query() or asl_set().  The operatoin ASL_QUERY_OP_EQUAL is
 * used for attributes set with asl_set().
 * a:  an aslmsg
 * returns: a set of messages that can be iterated over using aslresp_next(),
 * and the values can be retrieved using aslresp_get.
 */
aslresponse asl_search(aslclient asl, aslmsg msg);

/*
 * aslresponse_next: Iterate over responses returned from asl_search()
 * a: a response returned from asl_search();
 * returns: The next log message (an aslmsg) or NULL on failure
 */
aslmsg aslresponse_next(aslresponse r);

/*
 * aslresponse_free: Free a response returned from asl_search() 
 * a: a response returned from asl_search()
 */
void aslresponse_free(aslresponse a);

__END_DECLS

#endif /* __ASL_H__ */
