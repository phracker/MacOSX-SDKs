//
//  ILMessageFilterCapabilitiesQueryHandling.h
//  IdentityLookup
//
//  Copyright © 2021 Apple. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <IdentityLookup/ILBase.h>

NS_ASSUME_NONNULL_BEGIN

@class ILMessageFilterExtensionContext;
@class ILMessageFilterCapabilitiesQueryRequest;
@class ILMessageFilterCapabilitiesQueryResponse;

/**
 Functionality related to MessageFilter extension capabilities query requests.

 Subclasses of ILMessageFilterExtension which support querying must conform to this protocol.
 */

IL_EXTERN API_AVAILABLE(ios(16.0), macCatalyst(16.0)) API_UNAVAILABLE( tvos) API_UNAVAILABLE(macos, watchos)
@protocol ILMessageFilterCapabilitiesQueryHandling <NSObject>

/**
 Evaluate a query request and provide a response describing how the system should handle the message it represents.

 - Using offline/stored information to form a response about the message described by the query request.

 Block specified in `completion` parameter must be invoked with a response describing how to handle the message, and may be
 invoked asynchronously.

 @param capabilitiesQueryRequest A capabilities query request to be handled
 @param context Extension context.
 @param completion Completion block for returning a response.
 */
- (void)handleCapabilitiesQueryRequest:(ILMessageFilterCapabilitiesQueryRequest *)capabilitiesQueryRequest context:(ILMessageFilterExtensionContext *)context completion:(void (^)(ILMessageFilterCapabilitiesQueryResponse *))completion;

@end
NS_ASSUME_NONNULL_END
