/*
 * Copyright (c) 1999 Apple Computer, Inc. All rights reserved.
 *
 * @APPLE_LICENSE_HEADER_START@
 * 
 * "Portions Copyright (c) 1999 Apple Computer, Inc.  All Rights
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
/* Copyright (c) 1991 NeXT Computer, Inc.  All rights reserved.
 * 
 *	File:	achitecture/adb_kb_codes.h
 *
 *	Scan code conversion table for standard Apple ADB keyboard.
 *
 * HISTORY
 * 07-Oct-91  Doug Mitchell at NeXT
 *	Created.
 */

#ifndef	_ARCHITECTURE_ADB_KB_CODES_
#define _ARCHITECTURE_ADB_KB_CODES_

#include <architecture/adb_kb_map.h>

#define inv KEY_INVALID

/*
 * These key codes are are shared by standard Apple keyboards (handler ID
 * 1) and Extended keyboards (ID 2).
 */
static const adb_key_t apple_keys[NUM_ADB_KEYCODES] = {
	
  /*   normal	shift	ctl	ctl-shift	keycode (hex) */
    { 	'a', 	'A',	soh,	soh	},	/* 00 */
    { 	's', 	'S',	dc3,	dc3	},	/* 01 */
    { 	'd', 	'D',	eot,	eot	},	/* 02 */
    { 	'f', 	'F',	ack,	ack	},	/* 03 */
    { 	'h', 	'H',	bs,	bs	},	/* 04 */
    { 	'g', 	'G',	bel,	bel	},	/* 05 */
    { 	'z', 	'Z',	sub,	sub	},	/* 06 */
    { 	'x', 	'X',	can,	can	},	/* 07 */
    { 	'c', 	'C',	etx,	etx	},	/* 08 */
    { 	'v', 	'V',	syn,	syn	},	/* 09 */
    { 	'<', 	'>',	inv,	inv	},	/* 0a */
    { 	'b', 	'B',	stx,	stx	},	/* 0b */
    { 	'q', 	'Q',	dc1,	dc1	},	/* 0c */
    { 	'w', 	'W',	etb,	etb	},	/* 0d */
    { 	'e', 	'E',	enq,	enq	},	/* 0e */
    { 	'r', 	'R',	dc2,	dc2	},	/* 0f */
    { 	'y', 	'Y',	em,	em	},	/* 10 */
    { 	't', 	'T',	dc4,	dc4	},	/* 11 */
    { 	'1', 	'!',	'1',	'!'	},	/* 12 */
    { 	'2', 	'@',	inv,	inv	},	/* 13 - why the inv's???*/
    { 	'3', 	'#',	'3',	'#'	},	/* 14 */
    { 	'4', 	'$',	'4',	'$'	},	/* 15 */
    { 	'6', 	'^',	rs,	rs	},	/* 16 */
    { 	'5', 	'%',	'5',	'%'	},	/* 17 */
    { 	'=', 	'+',	'=',	'+'	},	/* 18 */
    { 	'9', 	'(',	'9',	'('	},	/* 19 */
    { 	'7', 	'&',	'7',	'&'	},	/* 1a */
    { 	'-', 	'_',	us,	us	},	/* 1b */
    { 	'8', 	'*',	'8',	'*'	},	/* 1c */
    { 	'0', 	')',	'0',	')'	},	/* 1d */
    { 	']', 	'}',	gs,	gs	},	/* 1e */
    { 	'o', 	'O',	si,	si	},	/* 1f */
    { 	'u', 	'U',	nak,	nak	},	/* 20 */
    { 	'[', 	'{',	esc,	esc	},	/* 21 */
    { 	'i', 	'I',	'\t',	'\t'	},	/* 22 */
    { 	'p', 	'P',	dle,	dle	},	/* 23 */
    { 	'\r', 	'\r',	'\r',	'\r'	},	/* 24 */
    { 	'l', 	'L',	np,	np	},	/* 25 */
    { 	'j', 	'J',	'\n',	'\n'	},	/* 26 */
    { 	'\'', 	'\"',	inv,	inv	},	/* 27 */
    { 	'k', 	'K',	vt,	vt	},	/* 28 */
    { 	';', 	':',	';',	':'	},	/* 29 */
    { 	'\\', 	'|',	fs,	fs	},	/* 2a */
    { 	',', 	'<',	',',	'<'	},	/* 2b */
    { 	'/', 	'?',	'/',	'?'	},	/* 2c */
    { 	'n', 	'N',	so,	so	},	/* 2d */
    { 	'm', 	'M',	'\r',	'\r'	},	/* 2e */
    { 	'.', 	'>',	'.',	'>'	},	/* 2f */
    { 	'\t', 	'\t',	'\t',	'\t'	},	/* 30 */
    { 	' ', 	' ',	inv,	inv 	},	/* 31 */
    { 	'`', 	'~',	'`',	'~'	},	/* 32 */
    { 	del, 	bs,	inv,	inv	},	/* 33 */
    { 	inv, 	inv,	inv,	inv	},	/* 34 */
    { 	esc, 	esc,	esc,	esc	},	/* 35 */
    { 	CTL_LEFT,     CTL_LEFT,     CTL_LEFT,    CTL_LEFT    },	/* 36 */
    { 	APPLE_LEFT,   APPLE_LEFT,   APPLE_LEFT,	 APPLE_LEFT  },	/* 37 */
    { 	SHIFT_LEFT,   SHIFT_LEFT,   SHIFT_LEFT,	 SHIFT_LEFT  },	/* 38 */
    { 	CAPS_LOCK,    CAPS_LOCK,    CAPS_LOCK,	 CAPS_LOCK   },	/* 39 */
    { 	OPTION_LEFT,  OPTION_LEFT,  OPTION_LEFT, OPTION_LEFT },	/* 3a */
    { 	CURS_LEFT,    CURS_LEFT,    CURS_LEFT,	 CURS_LEFT   },	/* 3b */
    { 	CURS_RIGHT,   CURS_RIGHT,   CURS_RIGHT,	 CURS_RIGHT  },	/* 3c */
    { 	CURS_DOWN,    CURS_DOWN,    CURS_DOWN,	 CURS_DOWN   },	/* 3d */
    { 	CURS_UP,      CURS_UP,	    CURS_UP,	 CURS_UP     },	/* 3e */
    { 	inv, 	inv,	inv,	inv	},	/* 3f */
    { 	inv, 	inv,	inv,	inv	},	/* 40 */
    { 	'.', 	'.',	'.',	'.'	},	/* 41 (keypad) */
    { 	inv, 	inv,	inv,	inv	},	/* 42 */
    { 	'*', 	'*',	'*',	'*'	},	/* 43 (keypad) */
    { 	inv, 	inv,	inv,	inv	},	/* 44 */
    { 	'+', 	'+',	'+',	'+'	},	/* 45 (keypad) */
    { 	inv, 	inv,	inv,	inv	},	/* 46 */
    { 	np, 	np,	np,	np	},	/* 47 - clear == ff? */
    { 	inv, 	inv,	inv,	inv	},	/* 48 */
    { 	inv, 	inv,	inv,	inv	},	/* 49 */
    { 	inv, 	inv,	inv,	inv	},	/* 4a */
    { 	'/', 	'\\',	'/',	fs	},	/* 4b (keypad) */
    { 	'\r', 	'\r',	'\r',	'\r'	},	/* 4c (keypad) */
    { 	inv, 	inv,	inv,	inv	},	/* 4d */
    { 	inv, 	inv,	inv,	inv	},	/* 4e */
    { 	inv, 	inv,	inv,	inv	},	/* 4f */
    { 	inv, 	inv,	inv,	inv	},	/* 50 */
    { 	'=', 	'|',	'=',	fs	},	/* 51 (keypad) */
    { 	'0', 	'0',	'0',	'0'	},	/* 52 (keypad) */
    { 	'1', 	'1',	'1',	'1'	},	/* 53 (keypad) */
    { 	'2', 	'2',	'2',	'2'	},	/* 54 (keypad) */
    { 	'3', 	'3',	'3',	'3'	},	/* 55 (keypad) */
    { 	'4', 	'4',	'4',	'4'	},	/* 56 (keypad) */
    { 	'5', 	'5',	'5',	'5'	},	/* 57 (keypad) */
    { 	'6', 	'6',	'6',	'6'	},	/* 58 (keypad) */
    { 	'7', 	'7',	'7',	'7'	},	/* 59 (keypad) */
    { 	inv, 	inv,	inv,	inv	},	/* 5a */
    { 	'8', 	'8',	'8',	'8'	},	/* 5b (keypad) */
    { 	'9', 	'9',	'9',	'9'	},	/* 5c (keypad) */
    { 	inv, 	inv,	inv,	inv	},	/* 5d */
    { 	inv, 	inv,	inv,	inv	},	/* 5e */
    { 	inv, 	inv,	inv,	inv	},	/* 5f */
    { 	inv, 	inv,	inv,	inv	},	/* 60 */
    { 	inv, 	inv,	inv,	inv	},	/* 61 */
    { 	inv, 	inv,	inv,	inv	},	/* 62 */
    { 	inv, 	inv,	inv,	inv	},	/* 63 */
    { 	inv, 	inv,	inv,	inv	},	/* 64 */
    { 	inv, 	inv,	inv,	inv	},	/* 65 */
    { 	inv, 	inv,	inv,	inv	},	/* 66 */
    { 	inv, 	inv,	inv,	inv	},	/* 67 */
    { 	inv, 	inv,	inv,	inv	},	/* 68 */
    { 	inv, 	inv,	inv,	inv	},	/* 69 */
    { 	inv, 	inv,	inv,	inv	},	/* 6a */
    { 	inv, 	inv,	inv,	inv	},	/* 6b */
    { 	inv, 	inv,	inv,	inv	},	/* 6c */
    { 	inv, 	inv,	inv,	inv	},	/* 6d */
    { 	inv, 	inv,	inv,	inv	},	/* 6e */
    { 	inv, 	inv,	inv,	inv	},	/* 6f */
    { 	inv, 	inv,	inv,	inv	},	/* 70 */
    { 	inv, 	inv,	inv,	inv	},	/* 71 */
    { 	inv, 	inv,	inv,	inv	},	/* 72 */
    { 	VOLUME_UP, VOLUME_UP, VOLUME_UP, VOLUME_UP },		/* 73 */
    { 	BRIGHT_UP, BRIGHT_UP, BRIGHT_UP, BRIGHT_UP },		/* 74 */
    { 	inv, 	inv,	inv,	inv	},	/* 75 */
    { 	inv, 	inv,	inv,	inv	},	/* 76 */
    { 	VOLUME_DOWN, VOLUME_DOWN, VOLUME_DOWN, VOLUME_DOWN },	/* 77 */
    { 	inv, 	inv,	inv,	inv	},	/* 78 */
    { 	BRIGHT_DOWN, BRIGHT_DOWN, BRIGHT_DOWN, BRIGHT_DOWN },	/* 79 */
    { 	inv, 	inv,	inv,	inv	},	/* 7a */
    { 	inv, 	inv,	inv,	inv	},	/* 7b */
    { 	inv, 	inv,	inv,	inv	},	/* 7c */
    { 	inv, 	inv,	inv,	inv	},	/* 7d */
    { 	inv, 	inv,	inv,	inv	},	/* 7e */
    { 	ADB_RESET, ADB_RESET, ADB_RESET, ADB_RESET },	/* 7f */
};

/*
 * Standard apple keyboard.
 */
static const adb_kb_map_t std_adb_kb_map = {

	1,			// handler_id, US Apple, standard
	apple_keys
};

static const adb_kb_map_t iso_std_adb_kb_map = {

	4,			// handler_id, ISO Apple, standard
	apple_keys
};

/*
 * Extended apple keyboard.
 */
static const adb_kb_map_t extend_adb_kb_map = {

	2,			// handler_id, US Apple, extended
	apple_keys
};

static const adb_kb_map_t iso_extend_adb_kb_map = {

	5,			// handler_id, ISO Apple, extended
	apple_keys
};


/*
 * Format of keyboard data in register 0. Each event has two bytes
 * in this format.
 */
#define KEY_DIR_MASK		0x80
#define KEY_DIR_UP		0x80
#define KEY_CODE_MASK		0x7f
#define KEY_CODE_NULL		0xff

/*
 * Format of register 2. Bit positions are relative to the keyboard's
 * 16-bit register.
 */
typedef struct {
	unsigned	rsvd1:1,		// bit 15 - reserved
			delete:1,
			caps_lock:1,
			reset:1,
			control:1,
			shift:1,
			option:1,
			open_apple:1,
			rsvd2:8,		// bits 7..0 - reserved
			rsvd3:16;		// fill word
} adb_kb_reg2_t;

#endif	/* _ARCHITECTURE_ADB_KB_CODES_ */
