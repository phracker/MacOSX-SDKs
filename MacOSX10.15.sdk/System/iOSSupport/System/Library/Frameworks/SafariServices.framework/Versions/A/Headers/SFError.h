//
//  SFError.h
//  SafariServices
//
//  Copyright © 2016 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <SafariServices/SFFoundation.h>

SF_EXTERN NSString * const SFErrorDomain API_AVAILABLE(ios(10.0));

typedef NS_ENUM(NSInteger, SFErrorCode) {
    SFErrorNoExtensionFound = 1,
    SFErrorNoAttachmentFound = 2,
    SFErrorLoadingInterrupted = 3,
} API_AVAILABLE(ios(10.0)) API_UNAVAILABLE(macCatalyst);
