//  
//  GCGameControllerActivationContext.h
//  GameController
//
//  Copyright © 2024 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

API_AVAILABLE(ios(18.0))
API_UNAVAILABLE(macCatalyst, tvos, visionos)
API_UNAVAILABLE(macos)
@interface GCGameControllerActivationContext : NSObject

- (instancetype)init NS_UNAVAILABLE;

/** The bundle identifier of the previously active application, if any. */
@property (nonatomic, nullable, readonly) NSString *previousApplicationBundleID;

@end

NS_HEADER_AUDIT_END(nullability, sendability)
