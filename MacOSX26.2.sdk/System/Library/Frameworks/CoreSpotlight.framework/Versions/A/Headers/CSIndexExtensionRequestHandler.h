//
//  CSIndexExtensionRequestHandler.h
//  CoreSpotlight
//
//  Copyright © 2015–2017 Apple Inc. All rights reserved.
//

#import <CoreSpotlight/CSSearchableIndex.h>
#import <CoreSpotlight/CSBase.h>

CS_CLASS_AVAILABLE(10_13, 9_0)
CS_TVOS_UNAVAILABLE
@interface CSIndexExtensionRequestHandler : NSObject <NSExtensionRequestHandling,CSSearchableIndexDelegate>

@end

