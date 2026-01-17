/* $Xorg: Sunkeysym.h,v 1.4 2001/02/09 02:03:22 xorgcvs Exp $ */

/************************************************************

Copyright 1991, 1998  The Open Group

Permission to use, copy, modify, distribute, and sell this software and its
documentation for any purpose is hereby granted without fee, provided that
the above copyright notice appear in all copies and that both that
copyright notice and this permission notice appear in supporting
documentation.

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL THE
OPEN GROUP BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN
AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

Except as contained in this notice, the name of The Open Group shall not be
used in advertising or otherwise to promote the sale, use or other dealings
in this Software without prior written authorization from The Open Group.


Copyright 1991 by Sun Microsystems, Inc. Mountain View, CA.

                    All Rights Reserved

Permission  to  use,  copy,  modify,  and  distribute   this
software  and  its documentation for any purpose and without
fee is hereby granted, provided that the above copyright no-
tice  appear  in all copies and that both that copyright no-
tice and this permission notice appear in  supporting  docu-
mentation,  and  that the name of Sun not be used in
advertising or publicity pertaining to distribution  of  the
software  without specific prior written permission. Sun 
makes  no  representations about the suitability  of this
software for any purpose. It is provided "as is" without any
express or implied warranty.

SUN DISCLAIMS ALL WARRANTIES WITH REGARD TO  THIS  SOFTWARE,
INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FIT-
NESS FOR A PARTICULAR PURPOSE. IN NO EVENT SHALL SUN BE  LI-
ABLE  FOR  ANY SPECIAL, INDIRECT OR CONSEQUENTIAL DAMAGES OR
ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE,  DATA  OR
PROFITS,  WHETHER  IN  AN  ACTION OF CONTRACT, NEGLIGENCE OR
OTHER TORTUOUS ACTION, ARISING OUT OF OR IN CONNECTION  WITH
THE USE OR PERFORMANCE OF THIS SOFTWARE.

***********************************************************/

/*
 * Floating Accent
 */

#define	SunXK_FA_Grave		0x1005FF00
#define	SunXK_FA_Circum		0x1005FF01
#define	SunXK_FA_Tilde		0x1005FF02
#define	SunXK_FA_Acute		0x1005FF03
#define	SunXK_FA_Diaeresis	0x1005FF04
#define	SunXK_FA_Cedilla	0x1005FF05

/*
 * Miscellaneous Functions
 */

#define	SunXK_F36		0x1005FF10	/* Labeled F11 */
#define	SunXK_F37		0x1005FF11	/* Labeled F12 */

#define SunXK_Sys_Req   	0x1005FF60
#define SunXK_Print_Screen	0x0000FF61	/* Same as XK_Print */

/*
 * International & Multi-Key Character Composition
 */

#define SunXK_Compose		0x0000FF20	/* Same as XK_Multi_key */
#define SunXK_AltGraph		0x0000FF7E	/* Same as XK_Mode_switch */

/*
 * Cursor Control
 */

#define SunXK_PageUp		0x0000FF55 	/* Same as XK_Prior */
#define SunXK_PageDown		0x0000FF56	/* Same as XK_Next */

/*
 * Open Look Functions
 */

#define SunXK_Undo		0x0000FF65	/* Same as XK_Undo */
#define SunXK_Again		0x0000FF66	/* Same as XK_Redo */
#define SunXK_Find		0x0000FF68	/* Same as XK_Find */
#define SunXK_Stop		0x0000FF69	/* Same as XK_Cancel */
#define SunXK_Props		0x1005FF70
#define SunXK_Front		0x1005FF71
#define SunXK_Copy		0x1005FF72
#define SunXK_Open		0x1005FF73
#define SunXK_Paste		0x1005FF74
#define SunXK_Cut		0x1005FF75

#define SunXK_PowerSwitch		0x1005FF76
#define SunXK_AudioLowerVolume		0x1005FF77
#define SunXK_AudioMute			0x1005FF78
#define SunXK_AudioRaiseVolume		0x1005FF79
#define SunXK_VideoDegauss		0x1005FF7A
#define SunXK_VideoLowerBrightness	0x1005FF7B
#define SunXK_VideoRaiseBrightness	0x1005FF7C
#define SunXK_PowerSwitchShift		0x1005FF7D
