/*
 GKPeerPickerController.h
 Game Kit
 
 Copyright 2010 Apple Inc. All rights reserved.
 
 This API provides a system-supplied user interface for selecting and connecting to another device for a multiplayer game.  The API introduces GKPeerPickerController for this purpose, and should be used in conjunction with the GKSession API.
 
 This a not a Game Center feature. To support Game Center and online play, see GKMatchMatchmakerViewController.
 */

#import <GameKit/GKSession.h>

/// This a not a Game Center feature. To support Game Center and online play, see GKMatchMatchmakerViewController.
@class GKPeerPickerController;

/* Connection types
 */
typedef NS_ENUM(NSUInteger, GKPeerPickerConnectionType)
{
	GKPeerPickerConnectionTypeOnline = 1 << 0,		// Online (Internet) based multiplayer connection
	GKPeerPickerConnectionTypeNearby = 1 << 1		// Nearby (Bluetooth) based multiplayer connection
} NS_ENUM_DEPRECATED_IOS(3_0, 7_0);

NS_ASSUME_NONNULL_BEGIN

/* callbacks to the GKPeerPickerController delegate
 */
NS_DEPRECATED_IOS(3_0, 7_0, "Use MCBrowserViewController along with MCBrowserViewControllerDelegate from the MultipeerConnectivity framework") 
@protocol GKPeerPickerControllerDelegate <NSObject>

@optional

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdeprecated-declarations"
/* Notifies delegate that a connection type was chosen by the user.
 */
- (void)peerPickerController:(GKPeerPickerController *)picker didSelectConnectionType:(GKPeerPickerConnectionType)type ;

/* Notifies delegate that the connection type is requesting a GKSession object.
 
 You should return a valid GKSession object for use by the picker. If this method is not implemented or returns 'nil', a default GKSession is created on the delegate's behalf.
 */

- (GKSession *)peerPickerController:(GKPeerPickerController *)picker sessionForConnectionType:(GKPeerPickerConnectionType)type ;

/* Notifies delegate that the peer was connected to a GKSession.
 */
- (void)peerPickerController:(GKPeerPickerController *)picker didConnectPeer:(NSString *)peerID toSession:(GKSession *)session ;
#pragma clang diagnostic pop

/* Notifies delegate that the user cancelled the picker.
 */
- (void)peerPickerControllerDidCancel:(GKPeerPickerController *)picker ;

@end


/* The GKPeerPickerController class manages the system-supplied user interface for choosing peers to connect with for multiplayer games. The class manages the actual user interactions with the views and reports the results of those interactions to your delegate object.
 
 Because the GKPeerPickerController class handles all of the user interactions, all you have to do is tell it which GKSession selected peers should be connected to, tell it to start, and then wait to receive a delegate callback when the picker finished connecting peers or cancels.
 
 You must provide a delegate that conforms to the GKPeerPickerControllerDelegate protocol in order to use this class. After the user interface starts, this class notifies your delegate of the user’s actions.
 */
NS_CLASS_DEPRECATED_IOS(3_0, 7_0, "Use MCBrowserViewController from the MultipeerConnectivity framework") 
@interface GKPeerPickerController : NSObject

/* An integer bit mask that determines what connection types are supported by the application, and displays system-supplied UI as appropriate. 
 
 This mask can be specified by combining, using the C bitwise OR operator, any of the options described in GKPickerConnectionType. If not set, the default supported type is GKPickerConnectionTypeNearby.  If multiple connection types are supported, system-supplied UI will be presented to allow the user to select a connection type. The delegate receives a -peerPickerController:didSelectConnectionType: callback when the user selects a connection type.  If desired, this property should be set prior to calling -show, and should not be set while the picker is visible.
 */
@property(nonatomic, assign) GKPeerPickerConnectionType connectionTypesMask;

/* The delegate receives notifications when the user interacts with the picker interface. If this property is nil, the picker is dismissed immediately if you try to show it.
 */
@property(nonatomic, nullable, weak) id<GKPeerPickerControllerDelegate> delegate NS_DEPRECATED_IOS(3_0, 7_0) ;

/* Show the picker.
 */
- (void)show;

/* Dismiss the picker.
 */
- (void)dismiss;

@property(nonatomic,readonly,getter=isVisible) BOOL visible;

@end

NS_ASSUME_NONNULL_END
