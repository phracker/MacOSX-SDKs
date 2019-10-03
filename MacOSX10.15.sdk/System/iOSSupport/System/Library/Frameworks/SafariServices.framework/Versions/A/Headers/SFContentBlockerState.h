//
//  SFContentBlockerState.h
//  SafariServices
//
//  Copyright © 2016 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <SafariServices/SFFoundation.h>

SF_EXTERN API_AVAILABLE(ios(10.0)) API_UNAVAILABLE(macCatalyst)
@interface SFContentBlockerState : NSObject

@property (nonatomic, readonly, getter=isEnabled) BOOL enabled;

@end
