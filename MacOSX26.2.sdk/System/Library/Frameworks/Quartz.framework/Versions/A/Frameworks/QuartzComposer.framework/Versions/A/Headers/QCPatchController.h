/*
	Copyright:	(c) 2003-2010 by Apple Inc.  All rights reserved.
*/

#import <QuartzComposer/QuartzComposerDefines.h>
#import <AppKit/AppKit.h>

/* NOTES:
 - QCPatchController is a simple controller to use with Cocoa bindings that wraps a QCComposition
 - The controller can be bound to a QCView in which case the composition bound to "patch" will be rendered into it.
 - UI elements may be bound to the controller using the keys of published input/output ports to control the parameters of the composition.
*/

QC_CLASS_DEPRECATED_MAC(10_15)
@interface QCPatchController : NSController
{
@private
	void*			_QCPatchControllerPrivate;
}

@end
