//
//  INCallRecordType.h
//  Intents
//
//  Copyright (c) 2016-2017 Apple Inc. All rights reserved.
//

#ifndef INCallRecordType_h
#define INCallRecordType_h

#import <Foundation/Foundation.h>
#import <Intents/IntentsDefines.h>

typedef NS_ENUM(NSInteger, INCallRecordType) {
    INCallRecordTypeUnknown = 0,
    INCallRecordTypeOutgoing,
    INCallRecordTypeMissed,
    INCallRecordTypeReceived,
    INCallRecordTypeLatest API_AVAILABLE(ios(11.0), watchos(4.0), macosx(10.13)),
    INCallRecordTypeVoicemail API_AVAILABLE(ios(11.0), watchos(4.0), macosx(10.13)),
} API_AVAILABLE(ios(10.0), watchos(3.2), macosx(10.12));

#endif // INCallRecordType_h
