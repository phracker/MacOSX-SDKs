//
//  BERenderingProcess.h
//
//  Copyright © 2023 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <BrowserEngineKit/BEMacros.h>

#import <BrowserEngineKit/BEExtensionProcess.h>

#if TARGET_OS_OSX || TARGET_OS_IOS && !TARGET_OS_VISION
#include <xpc/xpc.h>
#endif

#if BROWSERENGINEKIT_HAS_UIINTERACTION
#import <UIKit/UIInteraction.h>
#endif


NS_ASSUME_NONNULL_BEGIN

/// An object that represents a running GPU extension process.
///
/// The system guarantees that the extension process has launched by the time the initializer methods return.
/// If the extension process exits, the system calls ``interruptionHandler``. There can only be one extension process per
/// host browser. The first time this type is initialized, a  process will be launched. If a extension process is all ready
/// running, the returned object will represent the already running process.
NS_REFINED_FOR_SWIFT
API_AVAILABLE(macos(14.3), ios(17.4))
API_UNAVAILABLE(watchos, tvos, visionos)
BROWSERENGINE_EXPORT
@interface BERenderingProcess: NSObject

-(instancetype)init NS_UNAVAILABLE;
+(instancetype)new NS_UNAVAILABLE;

/// Asynchronously finds an existing extension process or launches one.
///
/// This initializer finds an existing extension rendering process. If it’s unable to find an
/// existing process, it launches a new extension process.
///
/// - Parameters:
///   - `interruptionHandler` : A block that is called if the extension process terminates.
///   - `completion` : A block called with a new ``BERenderingProcess`` when the extension process has
///     launched or with an error.
+(void)renderingProcessWithInterruptionHandler:(void(^)(void))interruptionHandler
                           completion:(void(^)(BERenderingProcess* _Nullable process, NSError* _Nullable error))completion;

/// Asynchronously launches a rendering extension process.
///
/// This initializer launches a new rendering extension process with the provided bundle identifier.
///
/// - Parameters:
///   - `bundleID` : The bundle identifier of the rendering extension process to launch.
///   - `interruptionHandler` : A block that is called if the extension process terminates.
///   - `completion` : A block called with a new ``BERenderingProcess`` when the extension process has
///     launched or with an error.
+(void)renderingProcessWithBundleID:(NSString *)bundleID interruptionHandler:(void(^)(void))interruptionHandler completion:(void(^)(BERenderingProcess  *_Nullable process, NSError *_Nullable error))completion API_AVAILABLE(ios(18.2));

/// Stops the extension process.
///
/// When you call this method, you tell the system your app no longer needs this extension process.
/// If this is the last connection from the host process to the extension process, the system terminates
/// the extension process.
-(void)invalidate;


#if TARGET_OS_OSX || TARGET_OS_IOS && !TARGET_OS_VISION
/// Creates a new libXPC connection to the extension process.
///
/// This method creates a connection to the extension process and returns it. If it is not possible to make an XPC connection, this method will return nil and populate the `error` out param.
///
/// - Returns: The connection object representing the created libXPC connection or nil.
-(nullable xpc_connection_t)makeLibXPCConnectionError:(NSError* _Nullable*)error;

#endif // TARGET_OS_OSX || TARGET_OS_IOS


#if BROWSERENGINEKIT_HAS_UIINTERACTION
/// attach the created interaction to a view to express that the content of that view is directly related to the working of this process.
/// therefore, if the view is considered visible by the system then this process must also be considered to be visible.
/// do not attempt to set an interaction on multiple views as interactions track their views - instead create a new interaction for each view that you want to propogate visibility to this process.
- (id<UIInteraction>)createVisibilityPropagationInteraction;
#endif

@end

NS_REFINED_FOR_SWIFT
API_AVAILABLE(macos(14.3), ios(17.4))
API_UNAVAILABLE(watchos, tvos, visionos)
BROWSERENGINE_EXPORT
@interface BERenderingProcess (BEExtensionProcessConformance) <BEExtensionProcess>
@end

NS_ASSUME_NONNULL_END
