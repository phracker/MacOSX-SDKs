//
//  BEProcesses.h
//  BrowserEngineServices
//

#import <Foundation/Foundation.h>
#import <BrowserEngineKit/BEMacros.h>
#import <BrowserEngineKit/BEWebContentProcess.h>
#import <BrowserEngineKit/BERenderingProcess.h>
#import <BrowserEngineKit/BENetworkingProcess.h>

NS_ASSUME_NONNULL_BEGIN

@class AVCaptureSession;

/// An object that represents a granted capability.
NS_REFINED_FOR_SWIFT
API_AVAILABLE(macos(14.3), ios(17.4))
API_UNAVAILABLE(watchos, tvos, visionos)
BROWSERENGINE_EXPORT
@protocol BEProcessCapabilityGrant <NSObject>

/// Invalidates the grant, removing the capability from the process it was granted to.
-(BOOL)invalidate;

/// `YES` if the process has been granted the capability and the grant is still valid.
@property(readonly, getter=isValid) BOOL valid;

@end


/// An object that represents a media playback environment
NS_REFINED_FOR_SWIFT
API_AVAILABLE(ios(17.4))
API_UNAVAILABLE(macos, watchos, tvos, visionos)
BROWSERENGINE_EXPORT
@interface BEMediaEnvironment : NSObject

-(instancetype)init NS_UNAVAILABLE;
+(instancetype)new NS_UNAVAILABLE;

/// Creates a new media playback environment identified by the web page URL
///
/// - Parameters:
///   - url: The URL identifying the media playback environment
-(instancetype)initWithWebPageURL:(NSURL*)url NS_DESIGNATED_INITIALIZER;

#if BROWSERENGINEKIT_HAS_LIBXPC
/// Create a media session from an XPC representation
///
/// - Parameters:
///   - xpcRepresentation: The XPC representation of a BEMediaEnvironment received via XPC
-(nullable instancetype)initWithXPCRepresentation:(xpc_object_t)xpcRepresentation error:(NSError* _Nullable*)error;

/// Create an `xpc_object_t` that represents the media environment.
-(xpc_object_t)createXPCRepresentation;
#endif

/// Activates the media environment.
-(BOOL)activateWithError:(NSError* _Nullable*)error;

/// Suspends the media environment.
-(BOOL)suspendWithError:(NSError* _Nullable*)error;

/// Creates a new capture session in this media environment.
///
/// The media environment must be activated before the capture session can be started.
-(nullable AVCaptureSession*)makeCaptureSessionWithError:(NSError* _Nullable*)error;

@end


/// An object representing capabilities that can be granted to a helper extension process.
NS_REFINED_FOR_SWIFT
API_AVAILABLE(macos(14.3), ios(17.4))
API_UNAVAILABLE(watchos, tvos, visionos)
BROWSERENGINE_EXPORT
@interface BEProcessCapability : NSObject

/// The helper extension process may access AV hardware required for media capture and playback.
+(instancetype)mediaPlaybackAndCaptureWithEnvironment:(BEMediaEnvironment*)environment API_UNAVAILABLE(macosx);


/// The helper extension process may run in the background to finish work.
+(instancetype)background;

/// The helper extension process may run at foreground priority to work on behalf of the host process while it is foreground.
+(instancetype)foreground;

/// The helper extension process may remain resident in a suspended state (it will not be granted CPU time).
+(instancetype)suspended;

/// Requests the capability to be granted to the current process.
///
/// Returns the granted capability or nil and an error if it can not be granted
-(id<BEProcessCapabilityGrant>)requestWithError:(NSError* _Nullable*)error;

@end


NS_REFINED_FOR_SWIFT
API_AVAILABLE(macos(14.3), ios(17.4))
API_UNAVAILABLE(watchos, tvos, visionos)
BROWSERENGINE_EXPORT
@interface BEWebContentProcess (Capability)

/// Grants the specified capability to the process.
///
/// This method grants the specified capability to the process or returns nil and an error if it can not be granted.
///
/// - Parameters:
///   - capability: The capability to be granted
///   - error: The error out param populated if the capability cannot be granted.
///
///  - Returns: an invalidatable grant object that represents the granted capability.
-(nullable id<BEProcessCapabilityGrant>)grantCapability:(BEProcessCapability*)capability error:(NSError* _Nullable*)error;

@end

NS_REFINED_FOR_SWIFT
API_AVAILABLE(ios(17.6))
API_UNAVAILABLE(macos, watchos, tvos, visionos)
BROWSERENGINE_EXPORT
@interface BEWebContentProcess (CapabilityInvalidationHandler)

/// Grants the specified capability to the process with invalidation handler.
///
/// This method grants the specified capability to the process or returns nil and an error if it can not be granted.
///
/// - Parameters:
///   - capability: The capability to be granted
///   - error: The error out param populated if the capability cannot be granted.
///   - invalidationHandler: The invalidation handler
///
///  - Returns: an invalidatable grant object that represents the granted capability.
-(nullable id<BEProcessCapabilityGrant>)grantCapability:(BEProcessCapability*)capability error:(NSError**)error invalidationHandler:(void (^)(void))invalidationHandler;

@end

NS_REFINED_FOR_SWIFT
API_AVAILABLE(macos(14.3), ios(17.4))
API_UNAVAILABLE(watchos, tvos, visionos)
BROWSERENGINE_EXPORT
@interface BERenderingProcess (Capability)

/// Grants the specified capability to the process.
///
/// This method grants the specified capability to the process or returns nil and an error if it can not be granted.
///
/// - Parameters:
///   - capability: The capability to be granted
///   - error: The error out param populated if the capability cannot be granted.
///
///  - Returns: an invalidatable grant object that represents the granted capability.
-(nullable id<BEProcessCapabilityGrant>)grantCapability:(BEProcessCapability*)capability error:(NSError* _Nullable*)error;

@end

NS_REFINED_FOR_SWIFT
API_AVAILABLE(ios(17.6))
API_UNAVAILABLE(macos, watchos, tvos, visionos)
BROWSERENGINE_EXPORT
@interface BERenderingProcess (CapabilityInvalidationHandler)

/// Grants the specified capability to the process with invalidation handler.
///
/// This method grants the specified capability to the process or returns nil and an error if it can not be granted.
///
/// - Parameters:
///   - capability: The capability to be granted
///   - error: The error out param populated if the capability cannot be granted.
///   - invalidationHandler: The invalidation handler
///
///  - Returns: an invalidatable grant object that represents the granted capability.
-(nullable id<BEProcessCapabilityGrant>)grantCapability:(BEProcessCapability*)capability error:(NSError**)error invalidationHandler:(void (^)(void))invalidationHandler;

@end


NS_REFINED_FOR_SWIFT
API_AVAILABLE(macos(14.3), ios(17.4))
API_UNAVAILABLE(watchos, tvos, visionos)
BROWSERENGINE_EXPORT
@interface BENetworkingProcess (Capability)

/// Grants the specified capability to the process.
///
/// This method grants the specified capability to the process or returns nil and an error if it can not be granted.
///
/// - Parameters:
///   - capability: The capability to be granted
///   - error: The error out param populated if the capability cannot be granted.
///
///  - Returns: an invalidatable grant object that represents the granted capability.
-(nullable id<BEProcessCapabilityGrant>)grantCapability:(BEProcessCapability*)capability error:(NSError* _Nullable*)error;


@end

NS_REFINED_FOR_SWIFT
API_AVAILABLE(ios(17.6))
API_UNAVAILABLE(macos, watchos, tvos, visionos)
BROWSERENGINE_EXPORT
@interface BENetworkingProcess (CapabilityInvalidationHandler)

/// Grants the specified capability to the process with invalidation handler.
///
/// This method grants the specified capability to the process or returns nil and an error if it can not be granted.
///
/// - Parameters:
///   - capability: The capability to be granted
///   - error: The error out param populated if the capability cannot be granted.
///   - invalidationHandler: The invalidation handler
///
///  - Returns: an invalidatable grant object that represents the granted capability.
-(nullable id<BEProcessCapabilityGrant>)grantCapability:(BEProcessCapability*)capability error:(NSError**)error invalidationHandler:(void (^)(void))invalidationHandler;

@end

NS_ASSUME_NONNULL_END
