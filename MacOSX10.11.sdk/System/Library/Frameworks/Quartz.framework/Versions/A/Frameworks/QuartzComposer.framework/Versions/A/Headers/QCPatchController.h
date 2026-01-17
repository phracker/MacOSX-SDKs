/*
	Copyright:	(c) 2003-2010 by Apple Inc.  All rights reserved.
*/

#import <AppKit/AppKit.h>

/* NOTES:
 - QCPatchController is a simple controller to use with Cocoa bindings that wraps a QCComposition
 - The controller can be bound to a QCView in which case the composition bound to "patch" will be rendered into it.
 - UI elements may be bound to the controller using the keys of published input/output ports to control the parameters of the composition.
*/

@interface QCPatchController : NSController
{
@private
	__strong void*			_QCPatchControllerPrivate;
}

@end
