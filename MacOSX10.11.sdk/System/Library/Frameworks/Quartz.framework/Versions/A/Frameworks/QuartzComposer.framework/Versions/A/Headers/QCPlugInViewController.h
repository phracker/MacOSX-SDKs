/*
	Copyright:	(c) 2003-2008 by Apple, Inc., all rights reserved.
*/

#import <AppKit/AppKit.h>

#if defined(MAC_OS_X_VERSION_10_5) && (MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_5)

#import <QuartzComposer/QCPlugIn.h>

/* HIGH-LEVEL NOTES:
- The QCPlugInViewController class provides a controller object used to present a user interface to edit internal settings of QCPlugIns.
- The user interface is represented by a view containing controls which communicate with the plug-in instance through Cocoa bindings to edit its internal settings.
- In its typical usage, the plug-in view controller will handle all the user interface by loading the nib file and being the target of the Cocoa bindings for the controls.
- The internal settings of the plug-in must be accessed through Key Value Coding (KVC), and all the KVC keys representing the internal settings of the plug-in should be listed in its +plugInKeys method.
- The plug-in view controller expects the nib file to have its "File's Owner" of class "QCPlugInViewController", and have its "view" outlet connected to the view containing the editing controls.
- The controls are bound to the "File's Owner" as the target and "plugIn.XXX" as the model key path, where XXX is the KVC key for a given internal setting of the plug-in instance.
- Do not call -setRepresentedObject: or -setView: after initializing the QCPlugInViewController as this is unsupported.
*/

/* The view controller for QCPlugIn user-interface */
@interface QCPlugInViewController : NSViewController
{
@private
	__strong void*				_private;
}

/*
Creates a new plug-in view controller for a plug-in instance and the nib file name which contains the view (this method is the designated initializer).
*/
- (id) initWithPlugIn:(QCPlugIn*)plugIn viewNibName:(NSString*)name;

/*
Returns the plug-in instance for this plug-in view controller.
*/
- (QCPlugIn*) plugIn;

@end

/* Extension to QCPlugIn for user-interface support */
@interface QCPlugIn (QCPlugInViewController)

/*
Override this method to return a new (not autoreleased) QCPlugInViewController instance for the plug-in instance.
*/
- (QCPlugInViewController*) createViewController NS_RETURNS_RETAINED;

@end

#endif
