//
//  ILMessageFilterQueryHandling.h
//  IdentityLookup
//
//  Copyright © 2017 Apple. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <IdentityLookup/ILBase.h>

NS_ASSUME_NONNULL_BEGIN

@class ILMessageFilterQueryRequest;
@class ILMessageFilterExtensionContext;
@class ILMessageFilterQueryResponse;

/**
 Functionality related to MessageFilter extension query requests.

 Subclasses of ILMessageFilterExtension which support querying must conform to this protocol.
 */
IL_EXTERN API_AVAILABLE(ios(11.0), macCatalyst(13.0)) API_UNAVAILABLE( tvos) API_UNAVAILABLE(macos, watchos)
@protocol ILMessageFilterQueryHandling <NSObject>

/**
 Evaluate a query request and provide a response describing how the system should handle the message it represents.

 May include either (or both) of the following:

 - Using offline/stored information to form a response about the message described by the query request.

 - Deferring the query request to a network service associated with the app extension, allowing the network service to
   return data back to extension in order to form a response about the message. The `context` parameter provides an API which
   allows deferring a request to the network and receiving the response to that network request.

 Block specified in `completion` parameter must be invoked with a response describing how to handle the message, and may be
 invoked asynchronously.

 @param queryRequest A query request to be handled which describes a received message.
 @param context Extension context which offers API to defer request to network if necessary.
 @param completion Completion block for returning a response.
 */
- (void)handleQueryRequest:(ILMessageFilterQueryRequest *)queryRequest context:(ILMessageFilterExtensionContext *)context completion:(void (^)(ILMessageFilterQueryResponse *))completion;

@end

NS_ASSUME_NONNULL_END
