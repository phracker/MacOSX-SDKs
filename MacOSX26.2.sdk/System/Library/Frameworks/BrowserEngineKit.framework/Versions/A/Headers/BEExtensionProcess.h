//
//  BEExtensionProcess.h
//
//  Copyright © 2025 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <BrowserEngineKit/BEMacros.h>

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(macos(26.0), ios(26.0))
API_UNAVAILABLE(watchos, tvos, visionos)
@protocol BEExtensionProcess <NSObject>
@required

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

@end

NS_ASSUME_NONNULL_END
