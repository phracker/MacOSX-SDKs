/*
    File:  AVRouting.h
    
    Framework:  AVRouting
    
    Copyright © 2022 Apple Inc. All rights reserved.
    
 */
#import <TargetConditionals.h>

#if TARGET_OS_IOS || TARGET_OS_VISION || TARGET_OS_SIMULATOR || TARGET_OS_OSX
#import <AVRouting/AVCustomRoutingController.h>
#import <AVRouting/AVCustomRoutingEvent.h>
#import <AVRouting/AVCustomRoutingActionItem.h>
#import <AVRouting/AVCustomDeviceRoute.h>
#endif // TARGET_OS_IOS || TARGET_OS_VISION || TARGET_OS_SIMULATOR || TARGET_OS_OSX

#import <AVRouting/AVRoutingPlaybackArbiter.h>
