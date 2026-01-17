/*
    Protocols for File Transfer Support
    IMServicePlugIn Framework
    Copyright (c) 2009-2010, Apple, Inc.
    All rights reserved.
*/

#import <Foundation/Foundation.h>

@class IMServicePlugInFileTransferSession,
       IMServicePlugInOutgoingFileTransferSession,
       IMServicePlugInIncomingFileTransferSession;


#pragma mark -
#pragma mark IMServicePlugIn (Messages -> Service Plug-in)
#pragma mark -

/*!
    @protocol   IMServicePlugInFileTransferSessionSupport

    @discussion Implementing this protocol on your service plug-in's principal class indicates that your
                service supports handle-to-handle file transfers.

                If implementing this protocol, you must also include "IMServiceCapabilityFileTransferSessionSupport"
                in the "IMServiceCapabilities" key in the Info.plist of your service plug-in.

                Incoming File Transfers:
                1) The Service Plug-in creates an IMServicePlugInIncomingFileTransferSession instance
                2) The Service Plug-in creates an IMServicePlugInIncomingFileTransfer instance for each incoming file,
                   and adds them via -[IMServicePlugInIncomingFileTransferSession addIncomingFileTransfer:]
                3) The Service Plug-in calls -plugInDidReceiveIncomingFileTransferSession:fromHandle on the service application
                4) Messages displays the "Incoming file transfer" dialog to the user.
                5) If the user selects "Accept", Messages sends -acceptIncomingFileTransferSession: to the service plug-in
                   If the user selects "Decline", Messages sends -cancelFileTransferSession: to the service plug-in
                   
                If the file transfer is accepted:
                
                1) The service plug-in reads bytes from the network
                5) The service plug-in writes bytes via the fileHandleForWriting property's NSFileHandle object 
                7) Upon completing the file transfer -plugInDidFinishFileTransfer:error: is called with a nil error
                   If at any time the plug-in cannot finish the file transfer, call -plugInDidFinishFileTransfer:error:
                   with an actual NSError
                   
                Outgoing File Transfers:
                1) Messages creates an IMServicePlugInOutgoingFileTransfer instance
                2) Messages calls -startOutgoingFileTransfer:toHandle: on the service plug-in.
                3) The service plug-in delivers the file transfer notification to the selected handle
                4) If the handle accepts the transfer, the service plug-in calls:
                   -plugInDidReceiveAcceptForOutgoingFileTransfer:
                   If the handle declines the transfer, the service plug-in calls:
                   -plugInDidFinishFileTransfer:error:  with a non-nil error.

                If the file transfer is accepted:
                4) The service plug-in reads bytes via the fileHandleForReading property's NSFileHandle object 
                5) The bytes are written over the network
                6) The service plug-in sends occasional progress reports (once every second) via -plugInDidUpdateFileTransfer:transferredBytes:
                7) Upon completing the file transfer -plugInDidFinishFileTransfer:error: is called with a nil error
                   If at any time the plug-in cannot finish the file transfer, call -plugInDidFinishFileTransfer:error:
                   with an actual NSError

                IMServicePlugInFileTransferSessionSupport and IMServiceApplicationFileTransferSessionSupport are
                paired protocols.  If your service plug-in's principal class implements the
                IMServicePlugInFileTransferSessionSupport protocol, the IMServiceApplication object handed to your
                IMServicePlugIn will implement the IMServiceApplicationFileTransferSessionSupport protocol.
*/
@protocol IMServicePlugInFileTransferSessionSupport

- (oneway void) startOutgoingFileTransferSession:(IMServicePlugInOutgoingFileTransferSession *)session toHandle:(NSString *)handle NS_DEPRECATED_MAC(10_7, 10_13);;

- (oneway void) acceptIncomingFileTransferSession:(IMServicePlugInIncomingFileTransferSession *)session NS_DEPRECATED_MAC(10_7, 10_13);;
- (oneway void) cancelFileTransferSession:(IMServicePlugInFileTransferSession *)session NS_DEPRECATED_MAC(10_7, 10_13);;

@end


#pragma mark -
#pragma mark IMServiceApplication (Service Plug-in -> Messages)
#pragma mark -

@protocol IMServiceApplicationFileTransferSessionSupport <IMServiceApplication>
- (oneway void) plugInDidReceiveIncomingFileTransferSession:(IMServicePlugInIncomingFileTransferSession *)session fromHandle:(NSString *)handle NS_DEPRECATED_MAC(10_7, 10_13);;

- (oneway void) plugInDidAcceptOutgoingFileTransferSession:(IMServicePlugInOutgoingFileTransferSession *)session NS_DEPRECATED_MAC(10_7, 10_13);;

- (oneway void) plugInDidFinishFileTransferSession:(IMServicePlugInFileTransferSession *)session error:(NSError *)error NS_DEPRECATED_MAC(10_7, 10_13);;

@end

