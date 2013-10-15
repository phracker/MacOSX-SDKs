/*
    File:	AGL/aglRenderers.h

    Contains:	Constant values for built-in AGL renderers.

    Version:	Technology:	Mac OS X
                Release:	GM
 
     Copyright:  (c) 2000-2005 by Apple Computer, Inc., all rights reserved.
 
     Bugs?:      For bug reports, consult the following page on
                 the World Wide Web:
 
                     http://developer.apple.com/bugreporter/
 
*/

#ifndef _AGLRENDERERS_H
#define _AGLRENDERERS_H

/*
** Renderer ID numbers
*/
#define AGL_RENDERER_GENERIC_ID            0x00020200
#define AGL_RENDERER_GENERIC_FLOAT_ID	   0x00020400
#define AGL_RENDERER_APPLE_SW_ID           0x00020600
#define AGL_RENDERER_ATI_RAGE_128_ID       0x00021000
#define AGL_RENDERER_ATI_RADEON_ID         0x00021200
#define AGL_RENDERER_ATI_RAGE_PRO_ID       0x00021400
#define AGL_RENDERER_ATI_RADEON_8500_ID    0x00021600
#define AGL_RENDERER_ATI_RADEON_9700_ID    0x00021800
#define AGL_RENDERER_NVIDIA_GEFORCE_2MX_ID 0x00022000 /* also for GeForce 4MX  */
#define AGL_RENDERER_NVIDIA_GEFORCE_3_ID   0x00022200 /* also for GeForce 4 Ti */
#define AGL_RENDERER_NVIDIA_GEFORCE_FX_ID  0x00022400
#define AGL_RENDERER_VT_BLADE_XP2_ID       0x00023000
#define AGL_RENDERER_MESA_3DFX_ID          0x00040000

/* depreciated for Mac OS X, use above instead for specific renderer*/
/* AGL_RENDERER_ATI_ID    */ 
/* AGL_RENDERER_NVIDIA_ID */
/* AGL_RENDERER_FORMAC_ID */
/* AGL_RENDERER_3DFX_ID   */

#endif /* _AGLRENDERERS_H */
