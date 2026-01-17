/*
 * Copyright (c) 2015, 2018, 2020 Apple Inc.
 * All rights reserved.
 */

/*!
 * @file NEHotspotHelper.h
 *
 * @discussion
 *   The NEHotspotHelper interface allows an application to
 *   participate in the process of joining Wi-Fi/hotspot networks. Such an
 *   application is referred to as a HotspotHelper. A HotspotHelper receives
 *   commands to be processed in the background that allow it to participate
 *   in the Hotspot Network state machine.
 *
 *   When a network is joined initially, the state machine enters
 *   the Evaluating state. In that state, each HotspotHelper receives a
 *   command of type Evaluate. If one or more helpers indicates that it
 *   is able to handle the network, the one with the highest confidence
 *   level is chosen before entering the Authenticating state. As an
 *   optimization, the first helper to assert a high confidence wins and
 *   the state machine ignores the other helpers.
 *
 *   If no helpers claim the network, the state machine enters the
 *   Authenticated state.
 *
 *   In the Authenticating state, the chosen helper is given a command of type
 *   Authenticate. The helper is expected to perform whatever network
 *   processing is required to make the network available for general
 *   network traffic. If the authentication is successful, the helper
 *   indicates that with a Success result. The state machine enters the
 *   Authenticated state.
 *
 *   On a network that has been authenticated by a helper, the state machine
 *   enters the Maintaining state when the network is joined again, and also
 *   periodically while the system remains associated with the network. In the
 *   Maintaining state, the helper is expected to perform whatever network
 *   operations are required to determine if the network is still able to
 *   carry general network traffic. If that is the case, the helper returns
 *   Success. If not, and authentication is again required, it returns
 *   AuthenticationRequired to cause the state machine to re-enter the
 *   Authenticating state.
 *
 *   In the Authenticating state, if the helper determines that it requires
 *   user interaction to proceed, the helper first arranges to alert
 *   the user via a UserLocalNotification, then returns a result of
 *   UIRequired. The state machine enters the PresentingUI state.
 *
 *   In the PresentingUI state, the helper is given a command of type
 *   PresentUI. The application is not kept running in the background
 *   in this state: PresentingUI relies on the user bringing the application
 *   to the foreground manually or via the UILocalNotification. Once the
 *   application has the required information, it returns Success to
 *   enter the Authenticated state.
 *
 *   The HotspotHelper may also receive a FilterScanList command at any time,
 *   in addition to a state machine command as described above. In its response,
 *   the helper indicates which of the networks in the scan list it can
 *   confidently handle.
 *
 * @ignorefuncmacro NS_OPTIONS
 * @ignorefuncmacro NS_ENUM
 */

#import <Foundation/Foundation.h>
#import <os/availability.h>
#import <NetworkExtension/NEHotspotNetwork.h>

NS_ASSUME_NONNULL_BEGIN

#if defined(__cplusplus)
#define NEHS_EXPORT extern "C"
#else
#define NEHS_EXPORT extern
#endif

/*!
 * @typedef NEHotspotHelperCommandType
 * @abstract The type of the NEHotspotHelperCommand object.
 * @const kNEHotspotHelperCommandTypeNone Placeholder for the null command.
 * @const kNEHotspotHelperCommandTypeFilterScanList Filter the Wi-Fi scan list.
 * @const kNEHotspotHelperCommandTypeEvaluate Evaluate the network.
 * @const kNEHotspotHelperCommandTypeAuthenticate Authenticate to the network.
 * @const kNEHotspotHelperCommandTypePresentUI Present user interface.
 * @const kNEHotspotHelperCommandTypeMaintain Maintain the network.
 * @const kNEHotspotHelperCommandTypeLogoff Logoff the network.
 */
typedef NS_ENUM(NSInteger, NEHotspotHelperCommandType) {
	kNEHotspotHelperCommandTypeNone				= 0,
	kNEHotspotHelperCommandTypeFilterScanList	= 1,
	kNEHotspotHelperCommandTypeEvaluate			= 2,
	kNEHotspotHelperCommandTypeAuthenticate		= 3,
	kNEHotspotHelperCommandTypePresentUI		= 4,
	kNEHotspotHelperCommandTypeMaintain			= 5,
	kNEHotspotHelperCommandTypeLogoff			= 6,
} API_AVAILABLE(ios(9.0)) API_UNAVAILABLE(macos, tvos) __WATCHOS_PROHIBITED;

/*!
 * @typedef NEHotspotHelperResult
 * @abstract The result of processing the NEHotspotHelperCommand.
 * @discussion The HotspotHelper provides the result of
 *   processing the NEHotspotHelperCommand when it instantiates
 *   its NEHotspotHelperResponse.
 * @const kNEHotspotHelperResultSuccess The operation was successful.
 * @const kNEHotspotHelperResultFailure The operation failed.
 * @const kNEHotspotHelperResultUIRequired The operation requires user
 *   interaction. This result is only valid in response to a command with type
 *   kNEHotspotHelperCommandTypeAuthenticate.
 * @const kNEHotspotHelperResultCommandNotRecognized The helper did not
 *   recognize the command type.
 * @const kNEHotspotHelperResultAuthenticationRequired The network requires
 *   authentication again. This result is only valid in response to a
 *   command with type kNEHotspotHelperCommandTypeMaintain.
 * @const kNEHotspotHelperResultUnsupportedNetwork After attempting to
 *   authenticate, the helper determined that it can't perform the
 *   authentication. This result is only valid in response to commands of type
 *   kNEHotspotHelperCommandTypeAuthenticate and
 *   kNEHotspotHelperCommandTypePresentUI.
 * @const kNEHotspotHelperResultTemporaryFailure The helper determined that
 *   it is temporarily unable to perform the authentication.
 *   This result is only valid in response to commands of type
 *   kNEHotspotHelperCommandTypeAuthenticate and
 *   kNEHotspotHelperCommandTypePresentUI.
 */
typedef NS_ENUM(NSInteger, NEHotspotHelperResult) {
	kNEHotspotHelperResultSuccess				= 0,
	kNEHotspotHelperResultFailure				= 1,
	kNEHotspotHelperResultUIRequired			= 2,
	kNEHotspotHelperResultCommandNotRecognized	= 3,
	kNEHotspotHelperResultAuthenticationRequired= 4,
	kNEHotspotHelperResultUnsupportedNetwork	= 5,
	kNEHotspotHelperResultTemporaryFailure		= 6,
} API_AVAILABLE(ios(9.0)) API_UNAVAILABLE(macos, tvos) __WATCHOS_PROHIBITED;

/*!
 * @typedef NEHotspotHelperConfidence
 * @abstract
 *   The HotspotHelper's confidence in its ability to handle the network.
 * @discussion
 *   The HotspotHelper indicates its confidence in being able to handle the
 *   given hotspot network.
 * @const kNEHotspotHelperConfidenceNone The helper is unable to handle
 *   the network.
 * @const kNEHotspotHelperConfidenceLow The helper has some confidence
 *   in being able to handle the network.
 * @const kNEHotspotHelperConfidenceHigh The helper has high confidence
 *   in being able to handle the network.
 */
typedef NS_ENUM(NSInteger, NEHotspotHelperConfidence) {
	kNEHotspotHelperConfidenceNone		= 0,
	kNEHotspotHelperConfidenceLow		= 1,
	kNEHotspotHelperConfidenceHigh		= 2,
} API_AVAILABLE(ios(9.0)) API_UNAVAILABLE(macos, tvos) __WATCHOS_PROHIBITED;

/*!
 * @category NEHotspotNetwork(HotspotHelper)
 * @discussion
 *   Extends NEHotspotNetwork class to support conveying information about the
 *   network to the HotspotHelper. When the HotspotHelper is asked to evaluate
 *   the current network or filter the Wi-Fi scan list, it annotates the NEHotspotNetwork
 *   via the setConfidence method.
 */
API_AVAILABLE(ios(9.0)) API_UNAVAILABLE(macos, tvos) __WATCHOS_PROHIBITED
@interface NEHotspotNetwork (HotspotHelper)

/*!
 * @property signalStrength
 * @discussion
 *   The signal strength for the Wi-Fi network. The value lies within
 *   the range 0.0 (weak/no signal) to 1.0 (strong signal).
 */
@property (readonly) double signalStrength
API_AVAILABLE(ios(9.0)) API_UNAVAILABLE(macos, tvos) __WATCHOS_PROHIBITED;

/*!
 * @property secure
 * @discussion Indicates whether the network is secure
 */
@property (readonly, getter=isSecure) BOOL secure
API_AVAILABLE(ios(9.0)) API_UNAVAILABLE(macos, tvos) __WATCHOS_PROHIBITED;

/*!
 * @property autoJoined
 * @discussion
 *   Indicates whether the network was joined automatically
 *   (YES) or joined by the user (NO).
 */
@property (readonly, getter=didAutoJoin) BOOL autoJoined
API_AVAILABLE(ios(9.0)) API_UNAVAILABLE(macos, tvos) __WATCHOS_PROHIBITED;

/*!
 * @property justJoined
 * @discussion
 *   Indicates whether the network was just joined. Useful in the
 *   Maintaining state to differentiate whether the Maintain command
 *   is for the initial join, or the subsequent periodic callback.
 */
@property (readonly, getter=didJustJoin) BOOL justJoined
API_AVAILABLE(ios(9.0)) API_UNAVAILABLE(macos, tvos) __WATCHOS_PROHIBITED;

/*!
 * @property chosenHelper
 * @discussion
 *   Indicates whether the HotspotHelper is the chosen helper for
 *   the network. The NEHotspotNetwork must have been instantiated via a
 *   call to the +[NEHotspotHelper supportedNetworkInterfaces] method. This
 *   is useful to restore state after the HotspotHelper application is quit
 *   and restarted.
 */
@property (readonly, getter=isChosenHelper) BOOL chosenHelper
API_AVAILABLE(ios(9.0)) API_UNAVAILABLE(macos, tvos) __WATCHOS_PROHIBITED;

/*!
 * @method setConfidence
 * @abstract
 *   Indicate the confidence in being able to handle the network.
 * @discussion
 *   Use this method to indicate the confidence in being able to
 *   successfully authenticate to the given network. Used in the response
 *   to the kNEHotspotHelperCommandTypeEvaluate and
 *   kNEHotspotHelperCommandTypeFilterScanList commands.
 */
- (void)setConfidence:(NEHotspotHelperConfidence)confidence
	API_AVAILABLE(ios(9.0)) API_UNAVAILABLE(macos, tvos) __WATCHOS_PROHIBITED;

/*!
 * @method setPassword
 * @abstract
 *   Provide the password for a secure network
 * @discussion
 *   The HotspotHelper may set a password for a secure network. The format
 *   password string must adhere to IEEE 802.11 guidelines appropriate for
 *   the particular security scheme.
 *
 *   Used only in the response to the kNEHotspotHelperCommandTypeFilterScanList
 *   command.
 */
- (void)setPassword:(NSString *)password
	API_AVAILABLE(ios(9.0)) API_UNAVAILABLE(macos, tvos) __WATCHOS_PROHIBITED;

@end

@class NEHotspotHelperResponse;
@class NWTCPConnection;
@class NWUDPSession;
@class NWEndpoint;

/*!
 * @interface NEHotspotHelperCommand
 * @discussion
 *   An NEHotspotHelperCommand object is provided to the helper's
 *   command handler block. The HotspotHelper processes the command
 *   instantiates an NEHotspotHelperResponse object, sets the annotated
 *   network or networkList (Evaluate/FilterScanList only),
 *   then delivers it.
 */
API_AVAILABLE(ios(9.0)) API_UNAVAILABLE(macos, tvos) __WATCHOS_PROHIBITED
@interface NEHotspotHelperCommand : NSObject

/*!
 * @property commandType
 * @discussion
 *   The type of the command.
 */
@property (readonly) NEHotspotHelperCommandType commandType
API_AVAILABLE(ios(9.0)) API_UNAVAILABLE(macos, tvos) __WATCHOS_PROHIBITED;

/*!
 * @property network
 * @discussion
 *   The network associated with the command. May be nil.
 */
@property (readonly, nullable) NEHotspotNetwork * network
API_AVAILABLE(ios(9.0)) API_UNAVAILABLE(macos, tvos) __WATCHOS_PROHIBITED;

/*!
 * @property networkList
 * @discussion
 *   The list of networks associated with a command. Will be nil unless
 *   the command type is kNEHotspotHelperCommandTypeFilterScanList.
 *   This property returns an NSArray of NEHotspotNetwork.
 */
@property (readonly, nullable) NSArray<NEHotspotNetwork *> * networkList
API_AVAILABLE(ios(9.0)) API_UNAVAILABLE(macos, tvos) __WATCHOS_PROHIBITED;

/*!
 * @method createResponse:
 * @abstract
 *   Create a response to the command.
 * @discussion
 *   Instantiate an NEHotspotHelperResponse for the command.
 * @return
 *   NEHotspotHelperResponse with the specified result.
 */
- (NEHotspotHelperResponse *)createResponse:(NEHotspotHelperResult)result
	API_AVAILABLE(ios(9.0)) API_UNAVAILABLE(macos, tvos) __WATCHOS_PROHIBITED;

/*!
 * @method createTCPConnection
 * @abstract
 *   Create a new TCP connection over the interface associated with the command.
 * @discussion
 *   Instantiate an NWTCPConnection to the specified endpoint
 *   bound to the network interface associated with the command.
 * @return
 *   non-nil NWTCPConnection object if successful, nil otherwise
 */
- (NWTCPConnection *)createTCPConnection:(NWEndpoint *)endpoint
	API_AVAILABLE(ios(9.0)) API_UNAVAILABLE(macos, tvos) __WATCHOS_PROHIBITED;

/*!
 * @method createUDPSession
 * @abstract
 *   Create a new UDP session over the interface associated with the command.
 * @discussion
 *   Instantiate an NWUDPSession to the specified endpoint
 *   bound to the network interface associated with the command.
 * @return
 *   non-nil NWUDPSession object if successful, nil otherwise
 */
- (NWUDPSession *)createUDPSession:(NWEndpoint *)endpoint
	API_AVAILABLE(ios(9.0)) API_UNAVAILABLE(macos, tvos) __WATCHOS_PROHIBITED;

@end

/*!
 * @interface NEHotspotHelperResponse
 * @discussion
 *   The HotspotHelper creates an NEHotspotHelperResponse object to provide
 *   the results of running the corresponding NEHotspotHelperCommand.
 */
API_AVAILABLE(ios(9.0)) API_UNAVAILABLE(macos, tvos) __WATCHOS_PROHIBITED
@interface NEHotspotHelperResponse : NSObject

/*!
 * @method setNetwork
 * @abstract
 *   Set the network that conveys the confidence level.
 * @discussion
 *   Provide the annotated NEHotspotNetwork object in the response to the
 *   kNEHotspotHelperCommandTypeEvaluate command. The helper sets the
 *   confidence in the network object to indicate its ability to handle
 *   the current network.
 */
- (void)setNetwork:(NEHotspotNetwork *)network
	API_AVAILABLE(ios(9.0)) API_UNAVAILABLE(macos, tvos) __WATCHOS_PROHIBITED;

/*!
 * @method setNetworkList
 * @abstract
 *   Set the list of handled networks.
 * @discussion
 *   Provide an NSArray of annotated NEHotspotNetwork objects in response
 *   to the kNEHotspotHelperCommandTypeFilterScanList command.
 *   The helper provides the list of network objects that it is capable of
 *   handling with at least low confidence. Networks that it has no
 *   confidence in handling should not be specified.
 */
- (void)setNetworkList:(NSArray<NEHotspotNetwork *> *)networkList
	API_AVAILABLE(ios(9.0)) API_UNAVAILABLE(macos, tvos) __WATCHOS_PROHIBITED;

/*!
 * @method deliver
 * @abstract
 *   Delivers the response to the command.
 * @discussion
 *   Deliver the NEHotspotHelperResponse to the HotspotHelper infrastructure.
 */
- (void)deliver
	API_AVAILABLE(ios(9.0)) API_UNAVAILABLE(macos, tvos) __WATCHOS_PROHIBITED;
@end

/*!
 * @typedef NEHotspotHelperHandler
 * @abstract
 *   The type definition for the HotspotHelper's command handler block.
 * @discussion
 *   The application provides a block of this type when it
 *   invokes the +[NEHotspotHelper registerWithOptions:queue:handler] method.
 *   The block is invoked every time there is a command to be processed.
 */
typedef void (^NEHotspotHelperHandler)(NEHotspotHelperCommand * cmd)
API_AVAILABLE(ios(9.0)) API_UNAVAILABLE(macos, tvos) __WATCHOS_PROHIBITED;

NEHS_EXPORT
/*!
 * @const kNEHotspotHelperOptionDisplayName
 * @abstract
 *   The string displayed in Wi-Fi Settings for a network handled by
 *   the application.
 * @discussion
 *   This key specifies the display name for the application, if an alternate
 *   name is desired.  If this property is not specified, the application's
 *   name is used.
 *
 *   This name appears in Settings -> Wi-Fi underneath the Wi-Fi network
 *   name if the helper indicated that it was able to handle the network.
 */
const NSString * kNEHotspotHelperOptionDisplayName
API_AVAILABLE(ios(9.0)) API_UNAVAILABLE(macos, tvos) __WATCHOS_PROHIBITED;

/*!
 * @interface NEHotspotHelper
 * @discussion
 *   The NEHotspotHelper class allows an application to register itself as a
 *   HotspotHelper.
 */
API_AVAILABLE(ios(9.0)) API_UNAVAILABLE(macos, tvos) __WATCHOS_PROHIBITED
@interface NEHotspotHelper : NSObject

/*!
 * @method registerWithOptions:queue:handler
 * @abstract
 *   Register the application as a HotspotHelper.
 * @discussion
 *   Once this API is invoked successfully, the application becomes
 *   eligible to be launched in the background and participate in
 *   various hotspot related functions.
 *
 *   This function should be called once when the application starts up.
 *   Invoking it again will have no effect and result in FALSE being returned.
 *
 *   The 'options' dictionary may be nil, or contain the single property
 *   kNEHotspotHelperOptionDisplayName.
 *
 * @param options If not nil, 'options' is an NSDictionary containing
 *   kNEHotspotHelperOption* keys (currently just
 *   kNEHotspotHelperOptionDisplayName).
 * @param queue The dispatch_queue_t to invoke the handle block on.
 * @param handler The NEHotspotHelperHandler block to execute to process
 *   helper commands.
 * @return
 *   YES if the registration was successful, NO otherwise.
 * @note Notes
 * @note 1
 *   The application's Info.plist MUST include a UIBackgroundModes array
 *   containing 'network-authentication'.
 * @note 2
 *   The application MUST set 'com.apple.developer.networking.HotspotHelper'
 *   as one of its entitlements. The value of the entitlement is a boolean
 *   value true.
 */
+ (BOOL)registerWithOptions:(nullable NSDictionary<NSString *,NSObject *> *)options
					  queue:(dispatch_queue_t)queue
					handler:(NEHotspotHelperHandler)handler
	API_AVAILABLE(ios(9.0)) API_UNAVAILABLE(macos, tvos) __WATCHOS_PROHIBITED;

/*!
 * @method logoff:
 * @abstract
 *   Terminate the authentication session.
 * @discussion
 *   The application invokes this method when it wants to logoff from the
 *   current network. Invoking this method causes an NEHotspotHelperCommand
 *   of type kNEHotspotHelperCommandTypeLogoff to be issued to the application's
 *   'handler' block (see +[NEHotspotHelper registerWithOptions:queue:handler]).
 *
 *   'network' must correspond to the currently associated Wi-Fi network
 *   i.e. it must have come from the NEHotspotHelperCommand's 'network' property
 *   or from the +[NEHotspotHelper supportedInterfaces] method.
 * @return
 *   YES if the logoff command was successfully queued, NO otherwise.
 * @note Notes
 * @note 1
 *   The application MUST NOT actually logoff from the network until it
 *   receives the command to logoff.
 * @note 2
 *   After the application invokes -[NEHotspotHelperResponse deliver] indicating
 *   kNEHotspotHelperResultSuccess, the Wi-Fi network is disassociated.
 */
+ (BOOL)logoff:(NEHotspotNetwork *)network
	API_AVAILABLE(ios(9.0)) API_UNAVAILABLE(macos, tvos) __WATCHOS_PROHIBITED;

/*!
 * @method supportedNetworkInterfaces
 * @abstract
 *   Return the list of network interfaces managed by the
 *   HotspotHelper infrastructure.
 * @discussion
 *   Each network interface is represented by an NEHotspotNetwork object.
 *   Currently, the returned array contains exactly one NEHotspotNetwork
 *   object representing the Wi-Fi interface.
 *
 *   The main purpose of this method is to allow a HotspotHelper to provide
 *   accurate status in its UI at times when it has not been given a command
 *   to process. This method coupled with -[NEHotspotNetwork isChosenHelper]
 *   allows the application to know whether it is the one that is handling
 *   the current network.
 * @return
 *   nil if no network interfaces are being managed,
 *   non-nil NSArray of NEHotspotNetwork objects otherwise.
 */
+ (NSArray *_Nullable)supportedNetworkInterfaces /* of NEHotspotNetwork */
	API_AVAILABLE(ios(9.0)) API_UNAVAILABLE(macos, tvos) __WATCHOS_PROHIBITED;

@end

/*!
 * @category NSMutableURLRequest(NEHotspotHelper)
 * @discussion
 *   Extend NSMutableURLRequest to include a method to bind the
 *   request to the network interface associated with the specified
 *   NEHotspotHelperCommand object.
 */
@interface NSMutableURLRequest (NEHotspotHelper)
/*!
 * @method bindToHotspotHelperCommand:
 * @discussion
 *   Binds the NSMutableURLRequest to the network interface associated with
 *   the NEHotspotHelperCommand object.
 */
- (void)bindToHotspotHelperCommand:(NEHotspotHelperCommand *)command
	API_AVAILABLE(ios(9.0)) API_UNAVAILABLE(macos, tvos) __WATCHOS_PROHIBITED;
@end

NS_ASSUME_NONNULL_END
