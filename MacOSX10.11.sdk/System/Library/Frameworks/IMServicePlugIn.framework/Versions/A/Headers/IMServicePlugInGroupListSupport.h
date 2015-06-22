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
    @protocol   IMServicePlugInGroupListSupport

    @discussion Implementing this protocol on your service plug-in's principal class indicates that your
                service supports a group list.

                If implementing this protocol, you must also include "IMServiceCapabilityGroupListSupport"
                in the "IMServiceCapabilities" key in the Info.plist of your service plug-in.

                IMServicePlugInGroupListSupport and IMServiceApplicationGroupListSupport are
                paired protocols.  If your service plug-in's principal class implements the
                IMServicePlugInGroupListSupport protocol, the IMServiceApplication object handed to your
                IMServicePlugIn will implement the IMServiceApplicationGroupListSupport protocol.
*/
@protocol IMServicePlugInGroupListSupport

/*!
    @method     requestGroupList

    @discussion Messages calls this method on the IMServicePlugIn when the user
                finishes modifying the group list.
                
                After a -requestGroupList is requested, the service plug-in should
                respond with -plugInDidUpdateGroupList:error: with the current "truth"
                of the group list.
                
                If any operations from IMServicePlugInGroupListEditingSupport
                are still pending, -plugInDidUpdateGroupList:error: should not be
                called until they finish.
*/
- (oneway void) requestGroupList;

@end


#pragma mark  -


/*!
    @protocol   IMServicePlugInGroupListEditingSupport

    @discussion Implementing this protocol on your service plug-in's principal class indicates that your
                service supports editing the group list.  It requires that you also implement the
                IMServicePlugInGroupListSupport protocol.
                
                If implementing this protocol, you must also include "IMServiceCapabilityGroupListEditingSupport"
                in the "IMServiceCapabilities" key in the Info.plist of your service plug-in.
*/
@protocol IMServicePlugInGroupListEditingSupport <IMServicePlugInGroupListSupport>


/*!
    @method     addGroups:

    @discussion Messages calls this method when the user had added one or 
                more groups to the group list.

    @param      groupNames  An array of NSString objects, corresponding to the
                            names of the added groups
*/
- (oneway void) addGroups:(NSArray *)groupNames;


/*!
    @method     removeGroups:

    @discussion Messages calls this method when the user had removed one or
                more groups from the group list.

    @param      groupNames  An array of NSString objects, corresponding to the
                            names of the removed groups
*/
- (oneway void) removeGroups:(NSArray *)groupNames;


/*!
    @method     renameGroup:toGroup:

    @discussion Messages calls this method when the user renames a group.

    @param      oldGroupName  The former name of the group
    @param      newGroupName  The new name of the group
*/
- (oneway void) renameGroup:(NSString *)oldGroupName toGroup:(NSString *)newGroupName;


/*!
    @method     addHandles:toGroup:

    @discussion Messages calls this method when the user adds member handles to a group.

                In the event that the user moves a member from one group to
                another group, Messages will first call this method for the
                destination group, and then call -removeHandles:fromGroup:
                for the source group.

    @param      handles    The added handles
    @param      groupName  The name of the group
*/
- (oneway void) addHandles:(NSArray *)handles toGroup:(NSString *)groupName;


/*!
    @method     removeHandles:fromGroup:

    @discussion Messages calls this method when the adds member handles to a group.

                In the event that the user moves a member from one group to
                another group, Messages will first call -addHandles:toGroup: 
                for the destination group, and then call this method for
                the source group.

    @param      handles    The removed handles
    @param      groupName  The name of the group
*/
- (oneway void) removeHandles:(NSArray *)handles fromGroup:(NSString *)groupName;

@end


#pragma mark -


/*!
    @protocol   IMServicePlugInGroupListOrderingSupport

    @discussion Implementing this protocol on your service plug-in's principal class indicates
                that your service supports ordered group list.  It requires that you also implement the
                IMServicePlugInGroupListSupport protocol.

                If implementing this protocol, you must also include "IMServiceCapabilityGroupListOrderingSupport"
                in the "IMServiceCapabilities" key in the Info.plist of your service plug-in.
*/
@protocol IMServicePlugInGroupListOrderingSupport <IMServicePlugInGroupListSupport>


/*!
    @method     reorderGroups:

    @discussion Messages calls this method when the user modifies the order of groups.

    @param      groupNames  An NSArray of NSStrings, corresponding to group names in the new order
*/
- (oneway void) reorderGroups:(NSArray *)groupNames;


/*!
    @method     reorderGroups:

    @discussion Messages calls this method when the user modifies the order of handles in a specific group.
    
    @param      handles    An NSArray of NSStrings, corresponding to handles in the new order
    @param      groupName  The containing group
*/
- (oneway void) reorderHandles:(NSArray *)handles inGroup:(NSString *)groupName;

@end


#pragma mark -

/*!
    @protocol   IMServicePlugInGroupListAuthorizationSupport

    @discussion Implementing this protocol on your service plug-in's principal class indicates that your
                service requires authorization when adding a handle to the group list.

                If implementing this protocol, you must also include "IMServiceCapabilityGroupListAuthorizationSupport"
                in the "IMServiceCapabilities" key in the Info.plist of your service plug-in.

                IMServicePlugInGroupListAuthorizationSupport and IMServiceApplicationGroupListAuthorizationSupport are
                paired protocols.  If your service plug-in's principal class implements the
                IMServicePlugInGroupListAuthorizationSupport protocol, the IMServiceApplication object handed to your
                IMServicePlugIn will implement the IMServiceApplicationGroupListAuthorizationSupport protocol.
*/
@protocol IMServicePlugInGroupListAuthorizationSupport <IMServicePlugInGroupListSupport>


/*!
    @method     sendAuthorizationRequestToHandle:

    @discussion When Messages adds a handle to the group list on a service which requires authorization,
                it will call -sendAuthorizationRequestToHandle: for each handle after 
                -addHandles:toGroup:

    @param      handle     The handle from which to request authorization
*/
- (oneway void) sendAuthorizationRequestToHandle:(NSString *)handle;


/*!
    @method     acceptAuthorizationRequestFromHandle:

    @discussion When the user clicks the "Accept" button on a pending authorization request.  Messages
                calls this method on the service plug-in

    @param      handle     The handle to authorize
*/
- (oneway void) acceptAuthorizationRequestFromHandle:(NSString *)handle;


/*!
    @method     declineAuthorizationRequestFromHandle:

    @discussion When the user clicks the "Decline" button on a pending authorization request.  Messages
                calls this method on the service plug-in

    @param      handle     The handle to not authorize
*/
- (oneway void) declineAuthorizationRequestFromHandle:(NSString *)handle;

@end


#pragma mark -

/*!
    @protocol   IMServicePlugInGroupListHandlePictureSupport

    @discussion Implementing this protocol on your service plug-in's principal class indicates that your
                service supports handle pictures.

                If implementing this protocol, you must also include "IMServiceCapabilityGroupListHandlePictureSupport"
                in the "IMServiceCapabilities" key in the Info.plist of your service plug-in.

                Messages uses a caching mechanism for dealing with user pictures.  A unique identifier
                should be provided/calculated for each buddy picture and pass up to the application
                via the IMHandlePropertyPictureIdentifier handle property via:
                id<IMServiceApplicationGroupListSupport> plugInDidUpdateProperties:ofHandle:]
                
                If Messages does not have the user picture cached, it will request it via:
                id<IMServicePlugInGroupListHandlePictureSupport> requestHandlePictureWithIdentifier:]
                
                The service plug-in then fetches the image data and responds with:
                id<IMServiceApplicationGroupListSupport> plugInDidUpdateProperties:ofHandle:]
                with both the IMHandlePropertyPictureIdentifier and IMHandlePropertyPictureData
                properties set
*/
@protocol IMServicePlugInGroupListHandlePictureSupport <NSObject>


/*!
    @method     requestPictureForHandle:withIdentifier:

    @discussion Messages calls this method on the IMServicePlugIn instance when it needs the handle picture data
                for the specified identifier.

                Once the service plug-in obtains this data, it should call
                -[id<IMServiceApplication> plugInDidUpdateProperties:ofHandle:] 
				with the IMHandlePropertyPictureData property set
				
				Further calls to -plugInDidUpdateProperties:ofHandle: must NOT include the 
				IMHandlePropertyPictureData key.

    @param      handle      The handle to fetch
    @param      identifier  A unqiue handle picture identifier
*/
- (oneway void) requestPictureForHandle:(NSString *)handle withIdentifier:(NSString *)identifier;

@end


#pragma mark -
#pragma mark IMServiceApplication (Service Plug-in -> Messages)
#pragma mark -


/*!
    @protocol   IMServiceApplicationGroupListSupport

    @discussion This protocol is used to pass the group list information up to Messages
                Messages, and to provide response callbacks to IMServicePlugInInstantMessagingSupport 
                methods.
                
                IMServicePlugInGroupListSupport and IMServiceApplicationGroupListSupport are
                paired protocols.  If your service plug-in's principal class implements the
                IMServicePlugInGroupListSupport protocol, the IMServiceApplication object handed to your
                IMServicePlugIn will implement the IMServiceApplicationGroupListSupport protocol.
*/

@protocol IMServiceApplicationGroupListSupport <IMServiceApplication>

/*!
    @method     plug-inDidUpdateGroupList:error:

    @discussion The IMServicePlugIn instance should call this method on Messages in response to 
                a downwards -requestGroupList request (which will be called after each user
                modification of the group list).

                The current "truth" state of the group list should be passed up.

                To indicate that a requested modification operation failed, pass up an error
                in addition to the truth state.
                
    @param      groups  An array of NSDictionary objects, representing the service's group list.

                        Each dictionary should contain the following keys:

                        IMGroupListNameKey        - The name of the group
                        IMGroupListPermissionsKey - An NSNumber of IMGroupListPermissions
                        IMGroupListHandlesKey     - An NSArray containing NSStrings, corresponding to the handles in the group
                
    @param      error   An error for any requested group list modification operation, if one occurred
*/
- (oneway void) plugInDidUpdateGroupList:(NSArray *)groups error:(NSError *)error;

@end


#pragma mark -

/*!
    @protocol   IMServiceApplicationGroupListAuthorizationSupport

    @discussion This protocol is used to pass authorization requests from the server up to Messages.
                
                IMServicePlugInGroupListAuthorizationSupport and IMServiceApplicationGroupListAuthorizationSupport are
                paired protocols.  If your service plug-in's principal class implements the
                IMServicePlugInGroupListAuthorizationSupport protocol, the IMServiceApplication object handed to your
                IMServicePlugIn will implement the IMServiceApplicationGroupListAuthorizationSupport protocol.
*/
@protocol IMServiceApplicationGroupListAuthorizationSupport <IMServiceApplicationGroupListSupport>

/*!
    @method     plugInDidReceiveAuthorizationRequestFromHandle:

	@discussion When the IMServicePlugIn instance calls this method on the service application, Messages
	            displays an authorization request window from the specified handle.

	            If the user clicks "Accept" on the window, Messages then calls -acceptAuthorizationRequestFromHandle:
	 			on the service plug-in.
				
				If the user clicks "Decline", Messages instead calls -declineAuthorizationRequestFromHandle:
	            on the service plug-in.

	@param      handle   The handle requesting authorization
*/
- (oneway void) plugInDidReceiveAuthorizationRequestFromHandle:(NSString *)handle;

@end

