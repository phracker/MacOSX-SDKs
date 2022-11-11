//
//  INCallRecordTypeOptions.h
//  Intents
//
//  Copyright (c) 2016-2021 Apple Inc. All rights reserved.
//

#ifndef INCallRecordTypeOptions_h
#define INCallRecordTypeOptions_h

#import <Foundation/Foundation.h>
#import <Intents/IntentsDefines.h>

typedef NS_OPTIONS(NSUInteger, INCallRecordTypeOptions) {
    INCallRecordTypeOptionOutgoing = (1UL << 0),
    INCallRecordTypeOptionMissed = (1UL << 1),
    INCallRecordTypeOptionReceived = (1UL << 2),
    INCallRecordTypeOptionLatest API_AVAILABLE(ios(11.0), watchos(4.0)) = (1UL << 3),
    INCallRecordTypeOptionVoicemail API_AVAILABLE(ios(11.0), watchos(4.0)) = (1UL << 4),
    INCallRecordTypeOptionRinging API_AVAILABLE(ios(13.0), watchos(6.0)) = (1UL << 5),
    INCallRecordTypeOptionInProgress API_AVAILABLE(ios(13.0), watchos(6.0)) = (1UL << 6),
    INCallRecordTypeOptionOnHold API_AVAILABLE(ios(13.0), watchos(6.0)) = (1UL << 7),
} API_AVAILABLE(ios(10.0), macos(12.0), watchos(3.2)) API_UNAVAILABLE(tvos);

#endif // INCallRecordTypeOptions_h
