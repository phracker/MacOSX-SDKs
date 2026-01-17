/*	SBApplication.h
	Copyright (c) 2006, Apple, Inc. All rights reserved.
*/

#import <Foundation/Foundation.h>
#import <CoreServices/CoreServices.h>
#import <ScriptingBridge/SBObject.h>


NS_ASSUME_NONNULL_BEGIN

@protocol SBApplicationDelegate;


/// The `SBApplication` class provides a mechanism enabling an Objective-C
/// program to send Apple events to a scriptable application and receive Apple
/// events in response. It thereby makes it possible for that program to control
/// the application and exchange data with it. Scripting Bridge works by
/// bridging data types between Apple event descriptors and Cocoa objects.
///
/// Although `SBApplication` includes methods that manually send and process
/// Apple events, you should never have to call these methods directly. Instead,
/// subclasses of `SBApplication` implement application-specific methods that
/// handle the sending of Apple events automatically.
///
/// For example, if you wanted to get the current iTunes track, you can simply
/// use the `currentTrack` method of the dynamically defined subclass for the
/// iTunes application—which handles the details of sending the Apple event for
/// you—rather than figuring out the more complicated, low-level alternative:
///
/// ```objc
/// [iTunes propertyWithCode:'pTrk'];
/// ```
///
/// If you do need to send Apple events manually, consider using the
/// `NSAppleEventDescriptor` class.
///
/// ## Subclassing Notes
///
/// You rarely instantiate `SBApplication` objects directly. Instead, you get
/// the shared instance of a application-specific subclass typically by calling
/// one of the `applicationWith...` class methods, using a bundle identifier,
/// process identifier, or URL to identify the application.
API_AVAILABLE(macos(10.5), macCatalyst(13.0))
@interface SBApplication : SBObject <NSCoding>


/// Returns an instance of an `SBApplication` subclass that represents the
/// target application identified by the given bundle identifier.
///
/// If you must initialize an `SBApplication` object explictly, you should use
/// this initializer if possible; unlike
/// ``SBApplication/initWithProcessIdentifier:`` and
/// ``SBApplication/initWithURL:``, this method is not dependent on changeable
/// factors such as the target application's path or process ID. Even so, you
/// should rarely have to initialize an `SBApplication` object yourself;
/// instead, you should initialize an application-specific subclass such as
/// `iTunesApplication`.
///
/// Note that this method does not check whether an application with the given
/// bundle identifier actually exists.
///
/// - Parameters:
///   - ident: A bundle identifier specifying an application that is
/// OSA-compliant.
///
/// - Returns: An initialized shared instance of an `SBApplication` subclass
/// that represents a target application with the bundle identifier of `ident`.
/// Returns `nil` if no such application can be found or if the application does
/// not have a scripting interface.
- (nullable __kindof SBApplication *) initWithBundleIdentifier:(NSString *)ident;

/// Returns an instance of an `SBApplication` subclass that represents the
/// target application identified by the given URL.
///
/// This approach to initializing `SBApplication` objects should be used only if
/// you know for certain the URL of the target application. In most cases, it is
/// better to use ``SBApplication/applicationWithBundleIdentifier:`` which
/// dynamically locates the target application at runtime. Even so, you should
/// rarely have to initialize an `SBApplication` yourself.
///
/// This method currently supports file URLs (`file:`) and remote application
/// URLs (`eppc:`). It checks whether a file exists at the specified path, but
/// it does not check whether an application identified via `eppc:` exists.
///
/// - Parameters:
///   - url: A Universal Resource Locator (URL) specifying an application that is
/// OSA-compliant.
///
/// - Returns: An initialized `SBApplication` that you can use to communicate
/// with the target application specified by the process ID. Returns `nil` if an
/// application could not be found or if the application does not have a
/// scripting interface.
- (nullable __kindof SBApplication *) initWithURL:(NSURL *)url;

/// Returns an instance of an `SBApplication` subclass that represents the
/// target application identified by the given process identifier.
///
/// You should avoid using this method unless you know nothing about an external
/// application but its PID. In most cases, it is better to use
/// ``SBApplication/initWithBundleIdentifier:``, which will dynamically locate
/// the external application's path at runtime, or
/// ``SBApplication/initWithURL:``, which is not dependent on the external
/// application being open at the time the method is called.
///
/// - Parameters:
///   - pid: A BSD process ID specifying an application that is OSA-compliant.
/// Often you can get the process ID of a process using the
/// <doc://com.apple.documentation/documentation/foundation/nstask/1412022-processidentifier>
/// method of `NSTask`.
///
/// - Returns: An initialized `SBApplication` that you can use to communicate
/// with the target application specified by the process ID. Returns `nil` if no
/// such application can be found or if the application does not have a
/// scripting interface.
- (nullable __kindof SBApplication *) initWithProcessIdentifier:(pid_t)pid;

/// Returns the shared instance representing the target application specified by
/// its bundle identifier.
///
/// For applications that declare themselves to have a dynamic scripting
/// interface, this method will launch the application if it is not already
/// running.
///
/// - Parameters:
///   - ident: A bundle identifier specifying an application that is OSA-compliant.
///
/// - Returns: An instance of a `SBApplication` subclass that represents the
/// target application whose bundle identifier is `ident`. Returns `nil` if no
/// such application can be found or if the application does not have a
/// scripting interface.
+ (nullable __kindof SBApplication *) applicationWithBundleIdentifier:(NSString *) ident;

/// Returns the shared instance representing a target application specified by
/// the given URL.
///
/// For applications that declare themselves to have a dynamic scripting
/// interface, this method will launch the application if it is not already
/// running. This approach to initializing `SBApplication` objects should be
/// used only if you know for certain the URL of the target application. In most
/// cases, it is better to use
/// ``SBApplication/applicationWithBundleIdentifier:`` which dynamically locates
/// the target application at runtime.
///
/// This method currently supports file URLs (`file:`) and remote application
/// URLs (`eppc:`). It checks whether a file exists at the specified path, but
/// it does not check whether an application identified via `eppc:` exists.
///
/// - Parameters:
///   - url: The Universal Resource Locator (URL) locating an OSA-compliant
/// application.
///
/// - Returns: An `SBApplication` subclass from which to generate a shared
/// instance of the target application whose URL is `url`. Returns `nil` if no
/// such application can be found or if the application does not have a
/// scripting interface.
+ (nullable __kindof SBApplication *) applicationWithURL:(NSURL *) url;

/// Returns the shared instance representing a target application specified by
/// its process identifier.
///
/// You should avoid using this method unless you know nothing about a target
/// application but its process ID. In most cases, it is better to use
/// ``SBApplication/applicationWithBundleIdentifier:``, which will dynamically
/// locate the application's path at runtime, or
/// ``SBApplication/applicationWithURL:``, which is not dependent on the target
/// application being open at the time the method is called.
///
/// - Parameters:
///   - pid: The BSD process ID of a OSA-compliant application. Often you can get
/// the process ID of a process using the
/// <doc://com.apple.documentation/documentation/foundation/nstask/1412022-processidentifier>
/// method of `NSTask`.
///
/// - Returns: An instance of an `SBApplication` subclass that represents the
/// target application whose process identifier is `pid`. Returns `nil` if no
/// such application can be found or if the application does not have a
/// scripting interface.
+ (nullable __kindof SBApplication *) applicationWithProcessIdentifier:(pid_t) pid;

/// Returns a class object that represents a particular class in the target
/// application.
///
/// You invoke this method on an instance of a scriptable application. Once you
/// have the class object, you may allocate an instance of the class and
/// appropriately the raw instance. Or you may use it in a call to
/// <doc://com.apple.documentation/documentation/objectivec/1418956-nsobject/1418511-iskindofclass>
/// to determine the class type of an object.
///
/// - Parameters:
///   - className: The name of the scripting class, as it appears in the scripting interface. For example, "document".
///
/// - Returns: A `Class` object representing the scripting class.
- (nullable Class) classForScriptingClass:(NSString *) className;

/// A Boolean that indicates whether the target application represented by the
/// receiver is running.
///
/// <doc://com.apple.documentation/documentation/swift/true> if the application
/// is running, <doc://com.apple.documentation/documentation/swift/false>
/// otherwise.
///
/// This may be <doc://com.apple.documentation/documentation/swift/true> for instances initialized with a bundle identifier or URL because
/// `SBApplication` launches the application only when it's necessary to send
/// it an event.
@property (readonly, getter=isRunning) BOOL running;

/// Moves the target application to the foreground immediately.
///
/// If the target application is not already running, this method launches it.
- (void) activate;

/// The error-handling delegate of the receiver.
///
/// The delegate should implement the
/// ``SBApplicationDelegate/eventDidFail:withError:`` method of the
/// ``SBApplicationDelegate`` informal protocol.
@property (nullable, strong) id <SBApplicationDelegate> delegate;


/// The launch flags for the application represented by the receiver.
///
/// For more information, see
/// <doc://com.apple.documentation/documentation/coreservices/launch_services>.
@property LSLaunchFlags launchFlags;

/// The mode for sending Apple events to the target application.
///
/// For more information, see
/// <doc://com.apple.documentation/documentation/applicationservices/apple_event_manager>.
///
/// The default send mode is
/// <doc://com.apple.documentation/documentation/coreservices/1542914-anonymous/kaewaitreply>.
/// If the send mode is something other than `kAEWaitReply`, the receiver might
/// not correctly handle reply events from the target application.
@property AESendMode sendMode;


/// The period the application will wait to receive reply Apple events.
///
/// For more information, see
/// <doc://com.apple.documentation/documentation/applicationservices/apple_event_manager>.
///
/// The default timeout value is
/// <doc://com.apple.documentation/documentation/coreservices/1542814-timeout_constants/kaedefaulttimeout>,
/// which is about a minute. If you want the receiver to wait indefinitely for
/// reply Apple events, use
/// <doc://com.apple.documentation/documentation/coreservices/1542814-timeout_constants/knotimeout>.
/// For more information, see
/// <doc://com.apple.documentation/documentation/applicationservices/apple_event_manager>.
@property long timeout;

@end



/// This informal protocol defines a delegation method for handling Apple event
/// errors that are sent from a target application to an
/// <doc://com.apple.documentation/documentation/scriptingbridge/sbapplication>
/// object.
///
/// You must set a delegate for the ``SBApplication`` object using the
/// ``SBApplication/delegate`` method. If you do not set a delegate and have the
/// delegate handle the error in some way, ``SBApplication`` raises an
/// exception.
API_AVAILABLE(macos(10.5), macCatalyst(13.0))
@protocol SBApplicationDelegate


/// Sent by an `SBApplication` object when a target application returns an error
/// Apple event.
///
/// - Parameters:
///   - event: A pointer to the Apple event sent to the target application causing
/// the error.
///
///   - error: An object containing information about the error Apple event.
/// Specific information may be included in the `useInfo` dictionary of the
/// error object. The following table shows the possible
/// keys for this dictionary.
///
///     | Key | Description |
///     | ----------- | --------------- |
///     | ErrorBriefMessage | A short human-readable description of the error, as an <doc://com.apple.documentation/documentation/foundation/nsstring> |
///     | ErrorExpectedType | The type of data the target application expected, as an <doc://com.apple.documentation/documentation/foundation/nsappleeventdescriptor> object. |
///     | ErrorOffendingObject | The object that caused the error. |
///     | ErrorString | A full human-readable description of the error, as an <doc://com.apple.documentation/documentation/foundation/nsstring> object. |
///     | ErrorNumber | The Apple event error number, as an <doc://com.apple.documentation/documentation/foundation/nsnumber> object. |
///
/// - Returns: If you return a result, it will become the result of the
/// <doc://com.apple.documentation/documentation/appkit/nsapplication/1428359-sendevent>
/// that failed. Can be `nil`.
- (nullable id) eventDidFail:(const AppleEvent *)event withError:(NSError *)error;

@end

NS_ASSUME_NONNULL_END
