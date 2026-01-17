/* $XFree86: xc/include/extensions/xf86dga1.h,v 1.2 1999/04/17 07:05:41 dawes Exp $ */
/*

Copyright (c) 1995  Jon Tombs
Copyright (c) 1995  XFree86 Inc

*/

/************************************************************************

   THIS IS THE OLD DGA API AND IS OBSOLETE.  PLEASE DO NOT USE IT ANYMORE

************************************************************************/

#ifndef _XF86DGA1_H_
#define _XF86DGA1_H_

#include <X11/Xfuncproto.h>

#define X_XF86DGAQueryVersion		0
#define X_XF86DGAGetVideoLL		1
#define X_XF86DGADirectVideo		2
#define X_XF86DGAGetViewPortSize	3
#define X_XF86DGASetViewPort		4
#define X_XF86DGAGetVidPage		5
#define X_XF86DGASetVidPage		6
#define X_XF86DGAInstallColormap	7
#define X_XF86DGAQueryDirectVideo	8
#define X_XF86DGAViewPortChanged	9

#define XF86DGADirectPresent		0x0001
#define XF86DGADirectGraphics		0x0002
#define XF86DGADirectMouse		0x0004
#define XF86DGADirectKeyb		0x0008
#define XF86DGAHasColormap		0x0100
#define XF86DGADirectColormap		0x0200




#ifndef _XF86DGA_SERVER_

_XFUNCPROTOBEGIN

Bool XF86DGAQueryVersion(
    Display*		/* dpy */,
    int*		/* majorVersion */,
    int*		/* minorVersion */
);

Bool XF86DGAQueryExtension(
    Display*		/* dpy */,
    int*		/* event_base */,
    int*		/* error_base */
);

Status XF86DGAGetVideoLL(
    Display*			/* dpy */,
    int				/* screen */,
    unsigned int *		/* base addr */,
    int *			/* width */,
    int *			/* bank_size */,
    int *			/* ram_size */ 
);

Status XF86DGAGetVideo(
    Display*			/* dpy */,
    int				/* screen */,
    char **			/* base addr */,
    int *			/* width */,
    int *			/* bank_size */,
    int *			/* ram_size */
);

Status XF86DGADirectVideo(
    Display*			/* dpy */,
    int				/* screen */,
    int 			/* enable */
);

Status XF86DGADirectVideoLL(
    Display*			/* dpy */,
    int				/* screen */,
    int 			/* enable */
);

Status XF86DGAGetViewPortSize(
    Display*			/* dpy */,
    int				/* screen */,
    int *			/* width */,
    int *			/* height */
);

Status XF86DGASetViewPort(
    Display*			/* dpy */,
    int				/* screen */,
    int x			/* X */,
    int y			/* Y */
);

Status XF86DGAGetVidPage(
    Display*			/* dpy */,
    int				/* screen */,
    int *			/* vid page */
);

Status XF86DGASetVidPage(
    Display*			/* dpy */,
    int				/* screen */,
    int				/* vid page */
);

Status XF86DGAInstallColormap(
    Display*			/* dpy */,
    int				/* screen */,
    Colormap			/*Colormap */
);

int XF86DGAForkApp(
    int screen
);

Status XF86DGAQueryDirectVideo(
    Display *		/* dpy */,
    int			/* screen */,
    int *		/* flags */
);

Bool XF86DGAViewPortChanged(
    Display *		/* dpy */,
    int			/* screen */,
    int			/* n */
);


_XFUNCPROTOEND

#endif /* _XF86DGA_SERVER_ */

#endif /* _XF86DGA1_H_ */
