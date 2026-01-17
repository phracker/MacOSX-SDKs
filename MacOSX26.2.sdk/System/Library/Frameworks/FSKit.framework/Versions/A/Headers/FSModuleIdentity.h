//
//  Copyright (c) 2023 Apple Inc.  All rights reserved.
//
//  FSModuleIdentity.h
//  FSKit
//

#import <Foundation/Foundation.h>
#import <FSKit/FSKitDefines.h>

NS_ASSUME_NONNULL_BEGIN

/// An installed file system module.
FSKIT_API_AVAILABILITY_V1
@interface FSModuleIdentity : NSObject

/// The module's bundle identifier.
@property (readonly) NSString   *bundleIdentifier FSKIT_API_AVAILABILITY_V1;

/// The module's URL.
@property (readonly) NSURL      *url FSKIT_API_AVAILABILITY_V1;

/// A Boolean value that indicates if the module is enabled.
@property (nonatomic, getter=isEnabled, readonly)
                     BOOL        enabled FSKIT_API_AVAILABILITY_V1;

@end

NS_ASSUME_NONNULL_END
