//
//  INCallRecordTypeOptions.h
//  Intents
//
//  Copyright (c) 2016-2017 Apple Inc. All rights reserved.
//

#ifndef INCallRecordTypeOptions_h
#define INCallRecordTypeOptions_h

#import <Foundation/Foundation.h>
#import <Intents/IntentsDefines.h>

typedef NS_OPTIONS(NSUInteger, INCallRecordTypeOptions) {
    INCallRecordTypeOptionOutgoing = (1UL << 0),
    INCallRecordTypeOptionMissed = (1UL << 1),
    INCallRecordTypeOptionReceived = (1UL << 2),
    INCallRecordTypeOptionLatest = (1UL << 3),
    INCallRecordTypeOptionVoicemail = (1UL << 4),
} API_AVAILABLE(ios(10.0), watchos(3.2), macosx(10.12));

#endif // INCallRecordTypeOptions_h
