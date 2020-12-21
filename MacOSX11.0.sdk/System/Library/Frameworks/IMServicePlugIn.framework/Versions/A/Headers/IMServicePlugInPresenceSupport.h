/*
    Protocols for Group List Support
    IMServicePlugIn Framework
    Copyright (c) 2009-2010, Apple, Inc.
    All rights reserved.
*/

#import <Foundation/Foundation.h>


#pragma mark -
#pragma mark IMServicePlugIn (Messages -> Service Plug-in)
#pragma mark -

/*!
    @protocol   IMServicePlugInPresenceSupport

    @discussion Implementing this protocol on your service plug-in's principal class indicates that your
                service supports presence information.
                
                If implementing this protocol, you must also include "IMServiceCapabilityPresenceSupport"
                in the "IMServiceCapabilities" key in the Info.plist of your service plug-in.

                If implementing this protocol, you may optionally include "IMServiceCapabilityPresenceInvisibilitySupport"
                in the "IMServiceCapabilities" key in the Info.plist of your service plug-in.  Doing so indicates that
                your service supports a value of YES for the IMSessionPropertyIsInvisible key of
                updateSessionProperties:.
*/
@protocol IMServicePlugInPresenceSupport

/*!
    @method     updateSessionProperties:

    @discussion Messages calls this method on the IMServicePlugIn instance when the 
                the user's availability, status message, idle state, or picture
                changes.

    @param      properties  A dictionary, corresponding to the modified session properties
    
                Available keys include:
                IMSessionPropertyAvailability   - the user's availablility
                IMSessionPropertyStatusMessage  - the user's status message
                IMSessionPropertyPictureData    - the user's icon
                IMSessionPropertyIdleDate       - the time of the last user activity
                IMSessionPropertyIsInvisible    - If YES, the user wishes to appear offline to other users
*/
- (oneway void) updateSessionProperties:(NSDictionary *)properties NS_DEPRECATED_MAC(10_7, 10_13);

@end
