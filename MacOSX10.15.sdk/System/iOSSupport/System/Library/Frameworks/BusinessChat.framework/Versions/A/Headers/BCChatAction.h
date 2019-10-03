//
//  BCChatAction.h
//  BusinessChat
//
//  Copyright © 2018 Apple, Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

// clang-format off
NS_ASSUME_NONNULL_BEGIN

/**
 BCParameterName is used to define custom parameters when opening the transcript.
 */
typedef NSString *BCParameterName _NS_TYPED_EXTENSIBLE_ENUM NS_SWIFT_NAME(BCChatAction.Parameter);

/** Intent is used to help the support agent or business system identify the product, service, account, or other context when the customer tapped the button to send the message. */
extern BCParameterName const BCParameterNameIntent API_AVAILABLE(macos(10.13.4), ios(11.3));
/** Group is used to help the business or customer service platform route the message to the appropriate support agent group. */
extern BCParameterName const BCParameterNameGroup API_AVAILABLE(macos(10.13.4), ios(11.3));
/** Body is used to help the customer by providing a pre-configured contextual message that the customer can tap to send to smooth the transition into Business Chat. */
extern BCParameterName const BCParameterNameBody API_AVAILABLE(macos(10.13.4), ios(11.3));

API_AVAILABLE(macos(10.13.4), ios(11.3))
@interface BCChatAction : NSObject

/**
 Open the chat transcript configured for a given business.

 @param businessIdentifier The business identifier for the given business.
 @param intentParameters Parameters to be sent with the initial message.
 */
+ (void)openTranscript:(NSString *)businessIdentifier
      intentParameters:(NSDictionary<BCParameterName, NSString *> *)intentParameters NS_SWIFT_NAME(openTranscript(businessIdentifier:intentParameters:))API_AVAILABLE(macos(10.13.4), ios(11.3));

@end

NS_ASSUME_NONNULL_END
