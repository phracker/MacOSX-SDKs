#ifndef _XVMCLIB_H_
#define _XVMCLIB_H_

#include <X11/Xfuncproto.h>
#include <X11/extensions/Xvlib.h>
#include <X11/extensions/XvMC.h>

_XFUNCPROTOBEGIN

Bool XvMCQueryExtension (Display *display, int *eventBase, int *errBase);
Status XvMCQueryVersion (Display *display, int *major_versionp,
			 int *minor_versionp);
Status XvMCGetDRInfo(Display *dpy, XvPortID port,
		     char **name, char **busID, 
		     int *major, int *minor, 
		     int *patchLevel,
		     int *isLocal);


XvMCSurfaceInfo * XvMCListSurfaceTypes(Display *dpy, XvPortID port, int *num);

Status XvMCCreateContext (
   Display *display,
   XvPortID port,
   int surface_type_id,
   int width,
   int height,
   int flags,
   XvMCContext * context
);

Status XvMCDestroyContext (Display *display, XvMCContext * context);

Status 
XvMCCreateSurface(
  Display *display,
  XvMCContext * context,
  XvMCSurface * surface
);

Status XvMCDestroySurface(Display *display, XvMCSurface *surface);

XvImageFormatValues * XvMCListSubpictureTypes (
  Display * display,
  XvPortID port,
  int surface_type_id,
  int *count_return
);

Status
XvMCPutSurface(
  Display *display,
  XvMCSurface *surface,
  Drawable draw,
  short srcx, 
  short srcy, 
  unsigned short srcw, 
  unsigned short srch,
  short destx,
  short desty,
  unsigned short destw,
  unsigned short desth,
  int flags
);

Status XvMCHideSurface(Display *display, XvMCSurface *surface);

Status
XvMCCreateSubpicture (
   Display *display, 
   XvMCContext *context,
   XvMCSubpicture *subpicture, 
   unsigned short width,
   unsigned short height,
   int xvimage_id
);


Status
XvMCClearSubpicture (
  Display *display,
  XvMCSubpicture *subpicture,
  short x,
  short y,
  unsigned short width,
  unsigned short height,
  unsigned int color
);

Status
XvMCCompositeSubpicture (
   Display *display,
   XvMCSubpicture *subpicture,
   XvImage *image,
   short srcx,
   short srcy,
   unsigned short width,
   unsigned short height,
   short dstx,
   short dsty
);

Status
XvMCDestroySubpicture (Display *display, XvMCSubpicture *subpicture);

Status
XvMCSetSubpicturePalette (
  Display *display, 
  XvMCSubpicture *subpicture, 
  unsigned char *palette
);

Status
XvMCBlendSubpicture (
   Display *display,
   XvMCSurface *target_surface,
   XvMCSubpicture *subpicture,
   short subx,
   short suby,
   unsigned short subw,
   unsigned short subh,
   short surfx,
   short surfy,
   unsigned short surfw,
   unsigned short surfh
);

Status
XvMCBlendSubpicture2 (
   Display *display,
   XvMCSurface *source_surface,
   XvMCSurface *target_surface,
   XvMCSubpicture *subpicture,
   short subx,
   short suby,
   unsigned short subw,
   unsigned short subh,
   short surfx,
   short surfy,
   unsigned short surfw,
   unsigned short surfh
);

Status XvMCSyncSurface (Display *display, XvMCSurface *surface);
Status XvMCFlushSurface (Display *display, XvMCSurface *surface);
Status XvMCGetSurfaceStatus (Display *display, XvMCSurface *surface, int *stat);

Status XvMCRenderSurface ( 
   Display *display,
   XvMCContext *context,
   unsigned int picture_structure,
   XvMCSurface *target_surface,
   XvMCSurface *past_surface,
   XvMCSurface *future_surface,
   unsigned int flags,
   unsigned int num_macroblocks,
   unsigned int first_macroblock,
   XvMCMacroBlockArray *macroblock_array,
   XvMCBlockArray *blocks
);


Status XvMCSyncSubpicture (Display *display, XvMCSubpicture *subpicture);
Status XvMCFlushSubpicture (Display *display, XvMCSubpicture *subpicture);
Status
XvMCGetSubpictureStatus (Display *display, XvMCSubpicture *subpic, int *stat);

Status XvMCCreateBlocks (
   Display *display, 
   XvMCContext *context,
   unsigned int num_blocks,
   XvMCBlockArray *block
);

Status XvMCDestroyBlocks (Display *display,XvMCBlockArray *block);

Status XvMCCreateMacroBlocks (
   Display *display,
   XvMCContext *context,
   unsigned int num_blocks,
   XvMCMacroBlockArray *blocks
);

Status XvMCDestroyMacroBlocks (
   Display *display,
   XvMCMacroBlockArray *block
);

XvAttribute *
XvMCQueryAttributes (
    Display *display,
    XvMCContext *context,
    int *number
);

Status
XvMCSetAttribute (
    Display *display,
    XvMCContext *context, 
    Atom attribute, 
    int value
);

Status
XvMCGetAttribute (
    Display *display,
    XvMCContext *context, 
    Atom attribute, 
    int *value
);

_XFUNCPROTOEND

#endif
