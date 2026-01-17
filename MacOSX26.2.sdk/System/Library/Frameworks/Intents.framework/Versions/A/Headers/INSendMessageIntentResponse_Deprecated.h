//
//  INSendMessageIntentResponse_Deprecated.h
//  Intents
//
//  Created by Abdullah Abo Dan on 2/16/22.
//  Copyright © 2022 Apple Inc. All rights reserved.
//

#import <Intents/INSendMessageIntentResponse.h>

NS_ASSUME_NONNULL_BEGIN

@interface INSendMessageIntentResponse (Deprecated)

@property (readwrite, copy, nullable, NS_NONATOMIC_IOSONLY) INMessage *sentMessage API_DEPRECATED_WITH_REPLACEMENT("sentMessages", ios(10.3, 16.0), watchos(3.2, 9.0)) API_UNAVAILABLE(macos, tvos);

@end

NS_ASSUME_NONNULL_END
