//
//  BENetworkingProcess.h
//
//  Copyright © 2023 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <BrowserEngineKit/BEMacros.h>

#import <BrowserEngineKit/BEExtensionProcess.h>

#if TARGET_OS_OSX || TARGET_OS_IOS && !TARGET_OS_VISION
#include <xpc/xpc.h>
#endif


NS_ASSUME_NONNULL_BEGIN

/// An object that represents a running network extension process.
///
/// The system guarantees that the extension process has launched by the time the initializer methods return.
/// If the extension process exits, the system calls ``interruptionHandler``. There can only be one extension process per
/// host browser. The first time this type is initialized, a  process will be launched. If a extension process is all ready
/// running, the returned object will represent the already running process.
NS_REFINED_FOR_SWIFT
API_AVAILABLE(macos(14.3), ios(17.4))
API_UNAVAILABLE(watchos, tvos, visionos)
BROWSERENGINE_EXPORT
@interface BENetworkingProcess: NSObject

-(instancetype)init NS_UNAVAILABLE;
+(instancetype)new NS_UNAVAILABLE;

/// Asynchronously finds an existing network extension process or launches a one.
///
/// This initializer finds an existing networking extension process. If it’s unable to find an
/// existing process, it launches a new extension process.
///
/// - Parameters:
///   - `interruptionHandler` : A block that is called if the extension process terminates.
///   - `completion` : A block called with a new ``BENetworkingProcess`` when the extension process has
///     launched or with an error.
+(void)networkProcessWithInterruptionHandler:(void(^)(void))interruptionHandler
                               completion:(void(^)(BENetworkingProcess* _Nullable process, NSError* _Nullable error))completion;

/// Asynchronously launches a network extension process.
///
/// This initializer launches a new network extension process with the provided bundle identifier.
///
/// - Parameters:
///   - `bundleID` : The bundle identifier of the network extension process to launch.
///   - `interruptionHandler` : A block that is called if the extension process terminates.
///   - `completion` : A block called with a new ``BENetworkingProcess`` when the extension process has
///     launched or with an error.
+(void)networkProcessWithBundleID:(NSString *)bundleID interruptionHandler:(void(^)(void))interruptionHandler completion:(void(^)(BENetworkingProcess *_Nullable process, NSError *_Nullable error))completion API_AVAILABLE(ios(18.2));

/// Stops the extension process.
///
/// When you call this method, you tell the system your app no longer needs this extension process.
/// The system will terminate the extension process.
-(void)invalidate;


#if TARGET_OS_OSX || TARGET_OS_IOS && !TARGET_OS_VISION
/// Creates a new libXPC connection to the extension process.
///
/// This method creates a connection to the extension process and returns it. If it is not possible to make an XPC connection, this method will return nil and populate the `error` out param.
///
/// - Returns: The connection object representing the created libXPC connection or nil.
-(nullable xpc_connection_t)makeLibXPCConnectionError:(NSError* _Nullable*)error;
#endif // TARGET_OS_OSX || TARGET_OS_IOS

@end

NS_REFINED_FOR_SWIFT
API_AVAILABLE(macos(14.3), ios(17.4))
API_UNAVAILABLE(watchos, tvos, visionos)
BROWSERENGINE_EXPORT
@interface BENetworkingProcess (BEExtensionProcessConformance) <BEExtensionProcess>
@end

NS_ASSUME_NONNULL_END
