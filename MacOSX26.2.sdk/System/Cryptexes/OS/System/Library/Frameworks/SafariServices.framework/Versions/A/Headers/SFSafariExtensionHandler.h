//
//  SFSafariExtensionHandler.h
//  SafariServices
//
//  Copyright © 2016 Apple Inc. All rights reserved.
//

#if __OBJC2__

#import <Foundation/Foundation.h>
#import <SafariServices/SFFoundation.h>
#import <SafariServices/SFSafariExtensionHandling.h>

NS_ASSUME_NONNULL_BEGIN

SF_CLASS_AVAILABLE_MAC_SAFARI(10_0)
@interface SFSafariExtensionHandler : NSObject <NSExtensionRequestHandling, SFSafariExtensionHandling>
@end

NS_ASSUME_NONNULL_END

#endif // __OBJC2__
