//
//  SFSafariExtensionState.h
//  Safari
//
//  Copyright © 2016 Apple Inc. All rights reserved.
//

#import <SafariServices/SFFoundation.h>

#if __OBJC2__

#import <Foundation/Foundation.h>

NS_HEADER_AUDIT_BEGIN(nullability, sendability)
SF_CLASS_AVAILABLE_MAC_SAFARI(10_0)
NS_SWIFT_SENDABLE
@interface SFSafariExtensionState : NSObject

@property (nonatomic, readonly, getter=isEnabled) BOOL enabled;

@end
NS_HEADER_AUDIT_END(nullability, sendability)
#endif // __OBJC2__
