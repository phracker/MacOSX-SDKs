/***********************************************************
Copyright 1991 by Digital Equipment Corporation, Maynard, Massachusetts,
and the Massachusetts Institute of Technology, Cambridge, Massachusetts.

                        All Rights Reserved

Permission to use, copy, modify, and distribute this software and its 
documentation for any purpose and without fee is hereby granted, 
provided that the above copyright notice appear in all copies and that
both that copyright notice and this permission notice appear in 
supporting documentation, and that the names of Digital or MIT not be
used in advertising or publicity pertaining to distribution of the
software without specific, written prior permission.  

DIGITAL DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE, INCLUDING
ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS, IN NO EVENT SHALL
DIGITAL BE LIABLE FOR ANY SPECIAL, INDIRECT OR CONSEQUENTIAL DAMAGES OR
ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS,
WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION,
ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS
SOFTWARE.

******************************************************************/
/* $XFree86: xc/include/extensions/Xvlib.h,v 1.4 2003/11/17 22:20:03 dawes Exp $ */

#ifndef XVLIB_H
#define XVLIB_H
/*
** File: 
**
**   Xvlib.h --- Xv library public header file
**
** Author: 
**
**   David Carver (Digital Workstation Engineering/Project Athena)
**
** Revisions:
**
**   26.06.91 Carver
**     - changed XvFreeAdaptors to XvFreeAdaptorInfo
**     - changed XvFreeEncodings to XvFreeEncodingInfo
**
**   11.06.91 Carver
**     - changed SetPortControl to SetPortAttribute
**     - changed GetPortControl to GetPortAttribute
**     - changed QueryBestSize
**
**   05.15.91 Carver
**     - version 2.0 upgrade
**
**   01.24.91 Carver
**     - version 1.4 upgrade
**
*/

#include <X11/Xfuncproto.h>
#include <X11/extensions/Xv.h>

typedef struct {
  int numerator;
  int denominator;
} XvRational;

typedef struct {
  int flags;	/* XvGettable, XvSettable */
  int min_value;
  int max_value;
  char *name;
} XvAttribute;

typedef struct {
  XvEncodingID encoding_id;
  char *name;
  unsigned long width;
  unsigned long height;
  XvRational rate;
  unsigned long num_encodings;
} XvEncodingInfo;

typedef struct {
  char depth;
  unsigned long visual_id;
} XvFormat;

typedef struct {
  XvPortID base_id;
  unsigned long num_ports;
  char type;
  char *name;
  unsigned long num_formats;
  XvFormat *formats;
  unsigned long num_adaptors;
} XvAdaptorInfo;

typedef struct {
  int type;
  unsigned long serial;	   /* # of last request processed by server */
  Bool send_event;	   /* true if this came from a SendEvent request */
  Display *display;	   /* Display the event was read from */
  Drawable drawable;       /* drawable */
  unsigned long reason;    /* what generated this event */
  XvPortID port_id;        /* what port */
  Time time;		   /* milliseconds */
} XvVideoNotifyEvent;

typedef struct {
  int type;
  unsigned long serial;	   /* # of last request processed by server */
  Bool send_event;	   /* true if this came from a SendEvent request */
  Display *display;	   /* Display the event was read from */
  XvPortID port_id;        /* what port */
  Time time;		   /* milliseconds */
  Atom attribute;           /* atom that identifies attribute */
  long value;              /* value of attribute */
} XvPortNotifyEvent;

typedef union {
  int type;
  XvVideoNotifyEvent xvvideo;
  XvPortNotifyEvent xvport;
  long pad[24];
} XvEvent;

typedef struct {
  int id;                      /* Unique descriptor for the format */
  int type;                    /* XvRGB, XvYUV */
  int byte_order;              /* LSBFirst, MSBFirst */
  char guid[16];               /* Globally Unique IDentifier */
  int bits_per_pixel;
  int format;                  /* XvPacked, XvPlanar */
  int num_planes;

  /* for RGB formats only */
  int depth;
  unsigned int red_mask;       
  unsigned int green_mask;   
  unsigned int blue_mask;   

  /* for YUV formats only */
  unsigned int y_sample_bits;
  unsigned int u_sample_bits;
  unsigned int v_sample_bits;   
  unsigned int horz_y_period;
  unsigned int horz_u_period;
  unsigned int horz_v_period;
  unsigned int vert_y_period;
  unsigned int vert_u_period;
  unsigned int vert_v_period;
  char component_order[32];    /* eg. UYVY */
  int scanline_order;          /* XvTopToBottom, XvBottomToTop */
} XvImageFormatValues; 

typedef struct {
  int id;
  int width, height;
  int data_size;              /* bytes */
  int num_planes;
  int *pitches;               /* bytes */
  int *offsets;               /* bytes */
  char *data;
  XPointer obdata;     
} XvImage;

_XFUNCPROTOBEGIN

extern int XvQueryExtension(
  Display*                 /* display */,
  unsigned int*            /* p_version */,
  unsigned int*            /* p_revision */,
  unsigned int*            /* p_requestBase */,
  unsigned int*            /* p_eventBase */, 
  unsigned int*            /* p_errorBase */
);

extern int XvQueryAdaptors(
  Display*                 /* display */,
  Window                   /* window */,
  unsigned int*            /* p_nAdaptors */,
  XvAdaptorInfo**          /* p_pAdaptors */
);

extern int XvQueryEncodings(
  Display*                 /* display */,
  XvPortID                 /* port */,
  unsigned int*            /* p_nEncoding */,
  XvEncodingInfo**         /* p_pEncoding */
);

extern int XvPutVideo(
  Display*                 /* display */,
  XvPortID                 /* port */,
  Drawable                 /* d */,
  GC                       /* gc */,
  int                      /* vx */, 
  int                      /* vy */,
  unsigned int             /* vw */, 
  unsigned int             /* vh */,
  int                      /* dx */, 
  int                      /* dy */,
  unsigned int             /* dw */,
  unsigned int             /* dh */
);

extern int XvPutStill(
  Display*                 /* display */,
  XvPortID                 /* port */,
  Drawable                 /* d */,
  GC                       /* gc */,
  int                      /* vx */, 
  int                      /* vy */,
  unsigned int             /* vw */, 
  unsigned int             /* vh */,
  int                      /* dx */, 
  int                      /* dy */,
  unsigned int             /* dw */,
  unsigned int             /* dh */
);

extern int XvGetVideo(
  Display*                 /* display */,
  XvPortID                 /* port */,
  Drawable                 /* d */,
  GC                       /* gc */,
  int                      /* vx */, 
  int                      /* vy */,
  unsigned int             /* vw */, 
  unsigned int             /* vh */,
  int                      /* dx */, 
  int                      /* dy */,
  unsigned int             /* dw */,
  unsigned int             /* dh */
);

extern int XvGetStill(
  Display*                 /* display */,
  XvPortID                 /* port */,
  Drawable                 /* d */,
  GC                       /* gc */,
  int                      /* vx */, 
  int                      /* vy */,
  unsigned int             /* vw */, 
  unsigned int             /* vh */,
  int                      /* dx */, 
  int                      /* dy */,
  unsigned int             /* dw */,
  unsigned int             /* dh */
);

extern int XvStopVideo(
  Display*                /* display */,
  XvPortID                /* port */,
  Drawable                /* drawable */
);

extern int XvGrabPort(
  Display*                /* display */,
  XvPortID                /* port */,
  Time                    /* time */
);

extern int XvUngrabPort(
  Display*                /* display */,
  XvPortID                /* port */,
  Time                    /* time */
);

extern int XvSelectVideoNotify(
  Display*                /* display */,
  Drawable                /* drawable */,
  Bool                    /* onoff */
);

extern int XvSelectPortNotify(
  Display*                /* display */,
  XvPortID                /* port */,
  Bool                    /* onoff */
);

extern int XvSetPortAttribute(
  Display*                /* display */,
  XvPortID                /* port */,
  Atom                    /* attribute */,
  int                     /* value */
);

extern int XvGetPortAttribute(
  Display*                /* display */,
  XvPortID                /* port */,
  Atom                    /* attribute */,
  int*                    /* p_value */
);

extern int XvQueryBestSize(
  Display*                /* display */,
  XvPortID                /* port */,
  Bool                    /* motion */,
  unsigned int            /* vid_w */, 
  unsigned int            /* vid_h */,
  unsigned int            /* drw_w */, 
  unsigned int            /* drw_h */,
  unsigned int*           /* p_actual_width */, 
  unsigned int*           /* p_actual_width */
);

extern XvAttribute* XvQueryPortAttributes(
  Display*                /* display */,
  XvPortID                /* port */,
  int*                    /* number */
);


extern void XvFreeAdaptorInfo(
  XvAdaptorInfo*          /* adaptors */
);

extern void XvFreeEncodingInfo(
  XvEncodingInfo*         /* encodings */
);


extern XvImageFormatValues * XvListImageFormats (
   Display 	*display,
   XvPortID 	port_id,
   int 		*count_return
);

extern XvImage * XvCreateImage (
   Display *display,
   XvPortID port,
   int id,
   char *data,
   int width, 
   int height 
);

extern int XvPutImage (
  Display *display,
   XvPortID id,
   Drawable d,
   GC gc,
   XvImage *image,
   int src_x,
   int src_y,
   unsigned int src_w,
   unsigned int src_h,
   int dest_x, 
   int dest_y,
   unsigned int dest_w,
   unsigned int dest_h
);

extern int XvShmPutImage (
   Display *display,
   XvPortID id,
   Drawable d,
   GC gc,
   XvImage *image,
   int src_x,
   int src_y,
   unsigned int src_w,
   unsigned int src_h,
   int dest_x, 
   int dest_y,
   unsigned int dest_w,
   unsigned int dest_h,
   Bool send_event
);

#ifdef _XSHM_H_

extern XvImage * XvShmCreateImage (
   Display *display,
   XvPortID port,
   int id,
   char* data,
   int width, 
   int height,
   XShmSegmentInfo *shminfo
);

#endif


_XFUNCPROTOEND

#endif /* XVLIB_H */
