/*
 *  AXActionConstants.h
 *  HIServices
 *
 *  Created by John Louch on Wed Feb 25 2004.
 *  Copyright (c) 2004 Apple Computer, Inc. All rights reserved.
 *
 */


#ifndef __AXACTIONCONSTANTS__
#define __AXACTIONCONSTANTS__



/*
	TBD: Explain general philosophy on whether to expose an action or not.
	Our initial philopsophy is to not to have an action where there is a menu item
	or button that does the same thing.
*/

// standard actions
#define kAXPressAction					CFSTR("AXPress")
#define kAXIncrementAction				CFSTR("AXIncrement")
#define kAXDecrementAction				CFSTR("AXDecrement")
#define kAXConfirmAction				CFSTR("AXConfirm")
#define kAXCancelAction					CFSTR("AXCancel")

// new actions
#define kAXRaiseAction					CFSTR("AXRaise")
#define kAXShowMenuAction				CFSTR("AXShowMenu")

// obsolete actions will be removed soon
#define kAXPickAction					CFSTR("AXPick")


#endif // __AXACTIONCONSTANTS__

