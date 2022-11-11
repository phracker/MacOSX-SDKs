//
//  SFError.h
//  SafariServices
//
//  Copyright © 2016 Apple Inc. All rights reserved.
//

#import <SafariServices/SFFoundation.h>

#if __OBJC2__

#import <Foundation/Foundation.h>

SF_EXTERN NSString * const SFErrorDomain SF_AVAILABLE_MAC_SAFARI(10_0);

typedef NS_ENUM(NSInteger, SFErrorCode) {
    SFErrorNoExtensionFound = 1,
    SFErrorNoAttachmentFound = 2,
    SFErrorLoadingInterrupted = 3,
} SF_ENUM_AVAILABLE_MAC_SAFARI(10_0);

#endif // __OBJC2__
