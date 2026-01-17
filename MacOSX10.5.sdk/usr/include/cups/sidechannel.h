/*
 * "$Id: sidechannel.h 6649 2007-07-11 21:46:42Z mike $"
 *
 *   Side-channel API definitions for the Common UNIX Printing System (CUPS).
 *
 *   Copyright 2007 by Apple Inc.
 *   Copyright 2006 by Easy Software Products.
 *
 *   These coded instructions, statements, and computer programs are the
 *   property of Apple Inc. and are protected by Federal copyright
 *   law.  Distribution and use rights are outlined in the file "LICENSE.txt"
 *   which should have been included with this file.  If this file is
 *   file is missing or damaged, see the license at "http://www.cups.org/".
 *
 *   This file is subject to the Apple OS-Developed Software exception.
 */

#ifndef _CUPS_SIDECHANNEL_H_
#  define _CUPS_SIDECHANNEL_H_

/*
 * C++ magic...
 */

#  ifdef __cplusplus
extern "C" {
#  endif /* __cplusplus */


/*
 * Constants...
 */

#define CUPS_SC_FD	4		/* File descriptor for select/poll */


/*
 * Enumerations...
 */

typedef enum				/**** Bidirectional capabilities ****/
{
  CUPS_SC_BIDI_NOT_SUPPORTED = 0,	/* Bidirectional I/O is not supported */
  CUPS_SC_BIDI_SUPPORTED = 1		/* Bidirectional I/O is supported */
} cups_sc_bidi_t;

typedef enum				/**** Request command codes ****/
{
  CUPS_SC_CMD_SOFT_RESET = 1,		/* Do a soft reset */
  CUPS_SC_CMD_DRAIN_OUTPUT = 2,		/* Drain all pending output */
  CUPS_SC_CMD_GET_BIDI = 3,		/* Return bidirectional capabilities */
  CUPS_SC_CMD_GET_DEVICE_ID = 4,	/* Return the IEEE-1284 device ID */
  CUPS_SC_CMD_GET_STATE = 5		/* Return the device state */
} cups_sc_command_t;

typedef enum				/**** Printer state bits ****/
{
  CUPS_SC_STATE_OFFLINE = 0,		/* Device is off-line */
  CUPS_SC_STATE_ONLINE = 1,		/* Device is on-line */
  CUPS_SC_STATE_BUSY = 2,		/* Device is busy */
  CUPS_SC_STATE_ERROR = 4,		/* Other error condition */
  CUPS_SC_STATE_MEDIA_LOW = 16,		/* Paper low condition */
  CUPS_SC_STATE_MEDIA_EMPTY = 32,	/* Paper out condition */
  CUPS_SC_STATE_MARKER_LOW = 64,	/* Toner/ink low condition */
  CUPS_SC_STATE_MARKER_EMPTY = 128	/* Toner/ink out condition */
} cups_sc_state_t;

typedef enum				/**** Response status codes ****/
{
  CUPS_SC_STATUS_NONE,			/* No status */
  CUPS_SC_STATUS_OK,			/* Operation succeeded */
  CUPS_SC_STATUS_IO_ERROR,		/* An I/O error occurred */
  CUPS_SC_STATUS_TIMEOUT,		/* The backend did not respond */
  CUPS_SC_STATUS_NO_RESPONSE,		/* The device did not respond */
  CUPS_SC_STATUS_BAD_MESSAGE,		/* The command/response message was invalid */
  CUPS_SC_STATUS_TOO_BIG,		/* Response too big */
  CUPS_SC_STATUS_NOT_IMPLEMENTED	/* Command not implemented */
} cups_sc_status_t;


/*
 * Prototypes...
 */

extern cups_sc_status_t	cupsSideChannelDoRequest(cups_sc_command_t command,
			                         char *data, int *datalen,
						 double timeout);
extern int		cupsSideChannelRead(cups_sc_command_t *command,
			                    cups_sc_status_t *status,
					    char *data, int *datalen,
					    double timeout);
extern int		cupsSideChannelWrite(cups_sc_command_t command,
			                     cups_sc_status_t status,
					     const char *data, int datalen,
					     double timeout);


#  ifdef __cplusplus
}
#  endif /* __cplusplus */

#endif /* !_CUPS_SIDECHANNEL_H_ */

/*
 * End of "$Id: sidechannel.h 6649 2007-07-11 21:46:42Z mike $".
 */
