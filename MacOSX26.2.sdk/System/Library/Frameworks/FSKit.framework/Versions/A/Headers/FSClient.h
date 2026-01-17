//
//  Copyright (c) 2022 Apple Inc. All rights reserved.
//
//  FSClient.h
//  FSKit
//

#import <Foundation/Foundation.h>
#import <FSKit/FSModuleIdentity.h>

NS_ASSUME_NONNULL_BEGIN

/// An interface for apps and daemons to interact with FSKit.
///
/// FSClient is the primary management interface for FSKit.
/// Use this class to discover FSKit extensions installed on the system, including your own.
///
/// > Important: Don't subclass `FSClient`.
FSKIT_API_AVAILABILITY_V1
@interface FSClient : NSObject

-(instancetype)init NS_UNAVAILABLE;

/// The shared instance of the FSKit client class.
@property (class, readonly) FSClient *sharedInstance NS_SWIFT_NAME(shared);

/// Asynchronously retrieves an list of installed file system modules.
///
/// In Swift, you can either call this method and pass a completion handler closure, or get the value of the `installedExtensions` property with the `async` keyword.
///
/// - Parameter completionHandler: A block or closure that executes when FSKit finishes its fetch process. If the fetch succeeds, the first parameter contains an array of ``FSModuleIdentity`` instances that identify installed modules. If the fetch fails, the second parameter contains an error detailing the failure.
-(void)fetchInstalledExtensionsWithCompletionHandler:(void(^)(NSArray<FSModuleIdentity *> *_Nullable,
                                                              NSError *_Nullable))completionHandler FSKIT_API_AVAILABILITY_V1 NS_SWIFT_ASYNC_NAME(getter:installedExtensions());

@end

NS_ASSUME_NONNULL_END
