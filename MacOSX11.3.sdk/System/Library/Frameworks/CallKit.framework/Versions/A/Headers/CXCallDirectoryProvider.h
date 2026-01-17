//
//  CXCallDirectoryProvider.h
//  CallKit
//
//  Copyright © 2016 Apple. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CallKit/CXBase.h>

NS_ASSUME_NONNULL_BEGIN

@class CXCallDirectoryExtensionContext;

CX_EXTERN API_AVAILABLE(ios(10.0), macCatalyst(13.0))  API_UNAVAILABLE(macos, watchos, tvos)
@interface CXCallDirectoryProvider : NSObject <NSExtensionRequestHandling>

- (void)beginRequestWithExtensionContext:(CXCallDirectoryExtensionContext *)context;

@end

NS_ASSUME_NONNULL_END
