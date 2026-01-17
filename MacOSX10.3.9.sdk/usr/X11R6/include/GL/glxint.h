#ifndef __GLX_glxint_h__
#define __GLX_glxint_h__

/* $XFree86: xc/include/GL/glxint.h,v 1.4 2001/08/01 00:44:34 tsi Exp $ */
/*
** The contents of this file are subject to the GLX Public License Version 1.0
** (the "License"). You may not use this file except in compliance with the
** License. You may obtain a copy of the License at Silicon Graphics, Inc.,
** attn: Legal Services, 2011 N. Shoreline Blvd., Mountain View, CA 94043
** or at http://www.sgi.com/software/opensource/glx/license.html.
**
** Software distributed under the License is distributed on an "AS IS"
** basis. ALL WARRANTIES ARE DISCLAIMED, INCLUDING, WITHOUT LIMITATION, ANY
** IMPLIED WARRANTIES OF MERCHANTABILITY, OF FITNESS FOR A PARTICULAR
** PURPOSE OR OF NON- INFRINGEMENT. See the License for the specific
** language governing rights and limitations under the License.
**
** The Original Software is GLX version 1.2 source code, released February,
** 1999. The developer of the Original Software is Silicon Graphics, Inc.
** Those portions of the Subject Software created by Silicon Graphics, Inc.
** are Copyright (c) 1991-9 Silicon Graphics, Inc. All Rights Reserved.
**
** $SGI$
*/

#include <X11/X.h>
#include <X11/Xdefs.h>

typedef struct __GLXvisualConfigRec __GLXvisualConfig;

struct __GLXvisualConfigRec {
    VisualID vid;
    int class;
    Bool rgba;
    int redSize, greenSize, blueSize, alphaSize;
    unsigned long redMask, greenMask, blueMask, alphaMask;
    int accumRedSize, accumGreenSize, accumBlueSize, accumAlphaSize;
    Bool doubleBuffer;
    Bool stereo;
    int bufferSize;
    int depthSize;
    int stencilSize;
    int auxBuffers;
    int level;
    /* Start of Extended Visual Properties */
    int visualRating;		/* visual_rating extension */
    int transparentPixel;	/* visual_info extension */
				/*    colors are floats scaled to ints */
    int transparentRed, transparentGreen, transparentBlue, transparentAlpha;
    int transparentIndex;
};

#define __GLX_MIN_CONFIG_PROPS	18
#define __GLX_MAX_CONFIG_PROPS	500

#define __GLX_EXT_CONFIG_PROPS 	7

/*
** Since we send all non-core visual properties as token, value pairs,
** we require 2 words across the wire. In order to maintain backwards
** compatibility, we need to send the total number of words that the
** VisualConfigs are sent back in so old libraries can simply "ignore"
** the new properties. 
*/
#define __GLX_TOTAL_CONFIG       (__GLX_MIN_CONFIG_PROPS +      \
                                    2 * __GLX_EXT_CONFIG_PROPS)

#endif /* !__GLX_glxint_h__ */
