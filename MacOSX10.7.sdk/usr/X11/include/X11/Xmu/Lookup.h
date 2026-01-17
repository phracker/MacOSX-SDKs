/************************************************************

Copyright 1999 by Thomas E. Dickey <dickey@clark.net>

                        All Rights Reserved

Permission is hereby granted, free of charge, to any person obtaining a
copy of this software and associated documentation files (the
"Software"), to deal in the Software without restriction, including
without limitation the rights to use, copy, modify, merge, publish,
distribute, sublicense, and/or sell copies of the Software, and to
permit persons to whom the Software is furnished to do so, subject to
the following conditions:

The above copyright notice and this permission notice shall be included
in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
IN NO EVENT SHALL THE ABOVE LISTED COPYRIGHT HOLDER(S) BE LIABLE FOR ANY
CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

Except as contained in this notice, the name(s) of the above copyright
holders shall not be used in advertising or otherwise to promote the
sale, use or other dealings in this Software without prior written
authorization.

********************************************************/

#ifndef included_xmu_lookup_h
#define included_xmu_lookup_h 1

#include <X11/Xlib.h>
#include <X11/Xutil.h>

extern int XmuLookupString(
		XKeyEvent *event,
		unsigned char *buffer,
		int nbytes,
		KeySym *keysym,
		XComposeStatus *status,
		unsigned long keysymSet);

extern int XmuLookupLatin1(
		XKeyEvent *event,
		unsigned char *buffer,
		int nbytes,
		KeySym *keysym,
		XComposeStatus *status);

extern int XmuLookupLatin2(
		XKeyEvent *event,
		unsigned char *buffer,
		int nbytes,
		KeySym *keysym,
		XComposeStatus *status);

extern int XmuLookupLatin3(
		XKeyEvent *event,
		unsigned char *buffer,
		int nbytes,
		KeySym *keysym,
		XComposeStatus *status);

extern int XmuLookupLatin4(
		XKeyEvent *event,
		unsigned char *buffer,
		int nbytes,
		KeySym *keysym,
		XComposeStatus *status);

extern int XmuLookupKana(
		XKeyEvent *event,
		unsigned char *buffer,
		int nbytes,
		KeySym *keysym,
		XComposeStatus *status);

extern int XmuLookupJISX0201(
		XKeyEvent *event,
		unsigned char *buffer,
		int nbytes,
		KeySym *keysym,
		XComposeStatus *status);

extern int XmuLookupArabic(
		XKeyEvent *event,
		unsigned char *buffer,
		int nbytes,
		KeySym *keysym,
		XComposeStatus *status);

extern int XmuLookupCyrillic(
		XKeyEvent *event,
		unsigned char *buffer,
		int nbytes,
		KeySym *keysym,
		XComposeStatus *status);

extern int XmuLookupGreek(
		XKeyEvent *event,
		unsigned char *buffer,
		int nbytes,
		KeySym *keysym,
		XComposeStatus *status);

extern int XmuLookupAPL(
		XKeyEvent *event,
		unsigned char *buffer,
		int nbytes,
		KeySym *keysym,
		XComposeStatus *status);

extern int XmuLookupHebrew(
		XKeyEvent *event,
		unsigned char *buffer,
		int nbytes,
		KeySym *keysym,
		XComposeStatus *status);

#endif /* included_xmu_lookup_h */
