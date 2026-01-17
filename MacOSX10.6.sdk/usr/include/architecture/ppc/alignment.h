/*
 * Copyright (c) 1999 Apple Computer, Inc. All rights reserved.
 *
 * @APPLE_LICENSE_HEADER_START@
 * 
 * This file contains Original Code and/or Modifications of Original Code
 * as defined in and that are subject to the Apple Public Source License
 * Version 2.0 (the 'License'). You may not use this file except in
 * compliance with the License. Please obtain a copy of the License at
 * http://www.opensource.apple.com/apsl/ and read it before using this
 * file.
 * 
 * The Original Code and all software distributed under the License are
 * distributed on an 'AS IS' basis, WITHOUT WARRANTY OF ANY KIND, EITHER
 * EXPRESS OR IMPLIED, AND APPLE HEREBY DISCLAIMS ALL SUCH WARRANTIES,
 * INCLUDING WITHOUT LIMITATION, ANY WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE, QUIET ENJOYMENT OR NON-INFRINGEMENT.
 * Please see the License for the specific language governing rights and
 * limitations under the License.
 * 
 * @APPLE_LICENSE_HEADER_END@
 */
/*
 * Copyright (c) 1996 NeXT Software, Inc.
 *
 *	File:	architecture/ppc/alignment.h

 * Natural alignment of shorts and longs (for ppc)
 *
 * HISTORY
 *
 * 29-Dec-96  Umesh Vaishampayan  (umeshv@NeXT.com)
 *	Ported from m98k.
 * 2 Sept 1992 Brian Raymor at NeXT
 *      Moved over to architecture.
 * 17 August 1992 Jack Greenfield at NeXT
 *	Created.
 */

__inline__ static unsigned short 
get_align_short(void *ivalue)
{
    unsigned short	ovalue = ((unsigned char *) ivalue)[0];

    ovalue <<= 8 * sizeof(unsigned char);
    return ovalue + ((unsigned char *) ivalue)[1];
}

__inline__ static unsigned short 
put_align_short(unsigned short ivalue, void *ovalue)
{
    unsigned short	*tvalue = &ivalue;

    ((unsigned char *) ovalue)[0] = ((unsigned char *) tvalue)[0];
    ((unsigned char *) ovalue)[1] = ((unsigned char *) tvalue)[1];
    return ivalue;
}

__inline__ static unsigned long 
get_align_long(void *ivalue)
{
    unsigned long	ovalue = get_align_short(ivalue);

    ovalue <<= 8 * sizeof(unsigned short);
    return ovalue + get_align_short(((unsigned char *) ivalue) + sizeof(short));
}

__inline__ static unsigned long 
put_align_long(unsigned long ivalue, void *ovalue)
{
    unsigned long	*tvalue = &ivalue;

    ((unsigned char *) ovalue)[0] = ((unsigned char *) tvalue)[0];
    ((unsigned char *) ovalue)[1] = ((unsigned char *) tvalue)[1];
    ((unsigned char *) ovalue)[2] = ((unsigned char *) tvalue)[2];
    ((unsigned char *) ovalue)[3] = ((unsigned char *) tvalue)[3];
    return ivalue;
}

