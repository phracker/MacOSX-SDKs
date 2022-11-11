//
//  ILMessageFilterExtensionContext.h
//  IdentityLookup
//
//  Copyright © 2017 Apple. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <IdentityLookup/ILBase.h>

NS_ASSUME_NONNULL_BEGIN

@class ILNetworkResponse;

/// Represents a MessageFilter extension request's context.
IL_EXTERN API_AVAILABLE(ios(11.0), macCatalyst(13.0)) API_UNAVAILABLE( tvos) API_UNAVAILABLE(macos, watchos)
@interface ILMessageFilterExtensionContext : NSExtensionContext

/**
 Defer the current query request to the app extension's associated network service and receive a network response asynchronously.

 This causes the system to perform an HTTPS network request to a URL specified in the app extension's Info.plist, and the response
 to that HTTPS request (or an error) is returned asynchronously. See documentation for details regarding how this HTTPS request
 is formatted, restrictions on the URL, etc.

 @param completion Completion block containing either the network response to the HTTPS request or an error.
 */
- (void)deferQueryRequestToNetworkWithCompletion:(void (^)(ILNetworkResponse *_Nullable response, NSError *_Nullable error))completion;

@end

NS_ASSUME_NONNULL_END
