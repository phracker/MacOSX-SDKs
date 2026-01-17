//
//  SFContentBlockerState.h
//  SafariServices
//
//  Copyright © 2016 Apple Inc. All rights reserved.
//

#import <SafariServices/SFFoundation.h>

#if __OBJC2__

#import <Foundation/Foundation.h>

SF_CLASS_AVAILABLE_MAC_SAFARI(10_0)
@interface SFContentBlockerState : NSObject

@property (nonatomic, readonly, getter=isEnabled) BOOL enabled;

@end

#endif // __OBJC2__
