/* $Xorg: EditresP.h,v 1.4 2001/02/09 02:03:52 xorgcvs Exp $ */

/*

Copyright 1989, 1998  The Open Group

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

*/
/* $XFree86: xc/lib/Xmu/EditresP.h,v 1.5 2001/01/17 19:42:55 dawes Exp $ */

/*
 * Author:  Chris D. Peterson, MIT X Consortium
 */

/************************************************************

		The Editres Protocol


  The Client message sent to the application is:

  ATOM = "ResEditor" 		--- RES_EDITOR_NAME

  FORMAT = 32                   --- RES_EDIT_SEND_EVENT_FORMAT

  l[0] = timestamp
  l[1] = command atom name
  l[2] = ident of command
  l[3] = protocol version number to use



  The binary protocol has the following format:

	Card8:		8-bit unsingned integer
	Card16:		16-bit unsingned integer
	Card32:		32-bit unsingned integer
	Int16:		16-bit signed integer
	Window:		32-bit value
	Widget:		32-bit value
	String8:        ListOfCard8
	
	[a][b][c] represent an exclusive list of choices.

	All widgets are passed as a list of widgets, containing the 
	full instance heirarch of this widget.  The hierarchy is ordered
	from parent to child.  Thus the first element of each list is
	the root of the widget tree (this makes verifying that the widget
	still exists, MUCH faster).

	ListOfFoo comprises a list of things in the following format:
	
	number:			Card16
	<number> things:	????
	
  This is a synchronous protocol, every request MUST be followed by a
  reply.  

  Request:

	Serial Number:	Card8
	Op Code:	Card8 -	{ SendWidgetTree = 0,
				  SetValues = 1,
				  GetResources = 2,
				  GetGeometry = 3,
				  FindChild = 4,
				  GetValues = 5 }
	Length:		Card32
	Data:		

   Reply:

	Serial Number:	Card8
	Type:		Card8 - { Formatted = 0,
	                          Unformatted = 1,
				  ProtocolMismatch = 2
				}
	Length:		Card32


   Byte Order:

	All Fields are MSB -> LSB

    Data:

    	Formatted:

        	The data contains the reply information for the request as
		specified below if the reply type is "Formatted".  The return
		values for the other reply types are shown below.

        Unformatted:

		Message:	String8

	ProtocolMismatch:

		RequestedVersion:   	Card8

------------------------------------------------------------

   SendWidgetTree:

	--->

	Number of Entries:	Card16
	Entry:
		widget:		ListOfWidgets
		name:		String8
		class:		String8
		window:		Card32
         	toolkit:        String8

	Send Widget Tree returns the toolkit type, and a fuly specified list
        of widgets for each widget in the tree.  This is enough information
        to completely reconstruct the entire widget heirarchy.

	The window return value contains the Xid of the window currently 
	used by this widget.  If the widget is unrealized then 0 is returned,
	and if widget is a non-windowed object a value of 2 is returned.

   SetValues:

	name:	String8
	type:	String8
	value:  String8
	Number of Entries:	Card16
	Entry:
		widget:		ListOfWidgets

	--->

	Number of Entries:	Card16
	Entry:
		widget:		ListOfWidgets
		message:	String8

	SetValues will allow the same resource to be set on a number of 
	widgets.  This function will return an error message if the SetValues
	request caused an Xt error.
	
  GetValues:

        names:                ListOfString8       
        widget:               Widget

        --->
	novalues:             ListOfCard16
	values:               ListOfString8
                   
        GetValues will allow a number of resource values to be read 
        on a particular widget.  The request specifies the names of
	the resources wanted and the widget id these resources are
	from.  The reply returns a list of indices from the requests
	name list of resources for which a value can not be returned.
	It also returns a list of returned values, in the order of the
        requests names list, skipping those indices present in novalues.

   GetResources:

	Number of Entries:	Card16
	Entry
		widget:		ListOfWidgets:

	---->

	Number of Entries:	Card16
	Entry
		Widget:			ListOfWidgets:
		Error:			Bool

		[ Message:		String 8 ]
		[ Number of Resources:	Card16
		Resource:
			Kind:	{normal, constraint}
			Name:	String8
			Class:	String8	
			Type:	String8 ]

	GetResource retrieves the kind, name, class and type for every 
	widget passed to it.  If an error occured with the resource fetch
	Error will be set to True for the given widget and a message
	is returned rather than the resource info.

  GetGeometry:

	Number of Entries:	Card16
	Entry
		Widget:		ListOfWidgets:

	---->

	Number of Entries:	Card16
	Entry
		Widget:			ListOfWidgets:
		Error:			Bool

		[ message:		String 8 ]
		[ mapped:       Boolean
		  X: 		Int16
		  Y:  		Int16
		  Width: 	Card16
	      	  Height:	Card16
		  BorderWidth:	Card16 ]

	GetGeometry retreives the mapping state, x, y, width, height
	and border width for each widget specified.  If an error occured 
	with the geometry fetch "Error" will be set to True for the given 
	widget and a message is returned rather than the geometry info.  
	X an Y corrospond to the root coordinates of the upper left corner
	of the widget (outside the window border).
	
  FindChild:

	Widget:		ListOfWidgets
	X:		Int16
	Y:		Int16
	
	--->

	Widget:		ListOfWidgets

	Find Child returns a descendent of the widget specified that 
	is at the root coordinates specified.

	NOTE:

	The returned widget is undefined if the point is contained in
	two or more mapped widgets, or in two overlapping Rect objs.

  GetValues:

        names:                ListOfString8       
        widget:               Widget

        --->
	
	values:               ListOfString8

        GetValues will allow a number of resource values to be read 
        on a particular widget.  Currently only InterViews 3.0.1 Styles 
	and their attributes are supported.  In addition, the current
	user interface  only supports the return of 1 resource.  The ability
	to specify and return multiple resources is defined for future editres
	interfaces where some or all of a widgets resource values are returned
	and displayed at once. 


************************************************************/

#include <X11/Intrinsic.h>
#include <X11/Xfuncproto.h>

#define XER_NBBY 8		/* number of bits in a byte */
#define BYTE_MASK 255

#define HEADER_SIZE 6

#define EDITRES_IS_OBJECT 2
#define EDITRES_IS_UNREALIZED 0

/*
 * Format for atoms
 */
#define EDITRES_FORMAT             8
#define EDITRES_SEND_EVENT_FORMAT 32

/*
 * Atoms
 */
#define EDITRES_NAME         "Editres"
#define EDITRES_COMMAND_ATOM "EditresCommand"
#define EDITRES_COMM_ATOM    "EditresComm"
#define EDITRES_CLIENT_VALUE "EditresClientVal"
#define EDITRES_PROTOCOL_ATOM "EditresProtocol"

typedef enum {
  SendWidgetTree = 0,
	       SetValues      = 1,
	       GetResources   = 2,
	       GetGeometry    = 3, 
	       FindChild      = 4,
	       GetValues      = 5
} EditresCommand;

typedef enum {
  NormalResource     = 0,
  ConstraintResource = 1
} ResourceType;

/*
 * The type of a resource identifier
 */
typedef unsigned char ResIdent;

typedef enum {
  PartialSuccess   = 0,
  Failure	   = 1,
  ProtocolMismatch = 2
} EditResError;

typedef struct _WidgetInfo {
    unsigned short num_widgets;
  unsigned long *ids;
    Widget real_widget;
} WidgetInfo;

typedef struct _ProtocolStream {
    unsigned long size, alloc;
    unsigned char *real_top, *top, *current;
} ProtocolStream;

/************************************************************
 * Function definitions for reading and writing protocol requests
 ************************************************************/
_XFUNCPROTOBEGIN

void _XEditResPutString8
(
 ProtocolStream		*stream,
 char			*str
 );

void _XEditResPut8
(
 ProtocolStream		*stream,
 unsigned int		value
 );

void _XEditResPut16
(
 ProtocolStream		*stream,
 unsigned int		value
 );

void _XEditResPut32
(
 ProtocolStream		*stream,
 unsigned long		value
 );

void _XEditResPutWidgetInfo
(
 ProtocolStream		*stream,
 WidgetInfo		*info
 );

void _XEditResResetStream
(
 ProtocolStream		*stream
 );

Bool _XEditResGet8
(
 ProtocolStream		*stream,
 unsigned char		*value
 );

Bool _XEditResGet16
(
 ProtocolStream		*stream,
 unsigned short		*value
 );

Bool _XEditResGetSigned16
(
 ProtocolStream		*stream,
 short			*value
 );

Bool _XEditResGet32
(
 ProtocolStream		*stream,
 unsigned long		*value
 );

Bool _XEditResGetString8
(
 ProtocolStream		*stream,
 char			**str
 );

Bool _XEditResGetWidgetInfo
(
 ProtocolStream		*stream,
 WidgetInfo		*info
 );

_XFUNCPROTOEND
