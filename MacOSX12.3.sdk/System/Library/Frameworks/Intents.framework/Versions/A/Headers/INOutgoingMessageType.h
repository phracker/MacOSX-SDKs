//
//  INOutgoingMessageType.h
//  Intents
//
//  Copyright (c) 2016-2022 Apple Inc. All rights reserved.
//

#ifndef INOutgoingMessageType_h
#define INOutgoingMessageType_h

#import <Foundation/Foundation.h>
#import <Intents/IntentsDefines.h>

typedef NS_ENUM(NSInteger, INOutgoingMessageType) {
    INOutgoingMessageTypeUnknown = 0,
    INOutgoingMessageTypeOutgoingMessageText,
    INOutgoingMessageTypeOutgoingMessageAudio,
} API_AVAILABLE(ios(14.0), macos(12.0), watchos(7.0)) API_UNAVAILABLE(tvos);

#endif // INOutgoingMessageType_h
