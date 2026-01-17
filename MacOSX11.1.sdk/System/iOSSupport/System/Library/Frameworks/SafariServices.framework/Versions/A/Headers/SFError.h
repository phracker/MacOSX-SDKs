//
//  SFError.h
//  SafariServices
//
//  Copyright © 2016 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <SafariServices/SFFoundation.h>

SF_EXTERN NSString * const SFErrorDomain API_AVAILABLE(ios(10.0), macCatalyst(13.4));

typedef NS_ENUM(NSInteger, SFErrorCode) {
    SFErrorNoExtensionFound = 1,
    SFErrorNoAttachmentFound = 2,
    SFErrorLoadingInterrupted = 3,
} API_AVAILABLE(ios(10.0), macCatalyst(13.4));
