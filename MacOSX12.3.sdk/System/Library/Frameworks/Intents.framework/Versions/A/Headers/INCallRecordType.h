//
//  INCallRecordType.h
//  Intents
//
//  Copyright (c) 2016-2022 Apple Inc. All rights reserved.
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
    INCallRecordTypeLatest API_AVAILABLE(ios(11.0), watchos(4.0)),
    INCallRecordTypeVoicemail API_AVAILABLE(ios(11.0), watchos(4.0)),
    INCallRecordTypeRinging API_AVAILABLE(ios(13.0), watchos(6.0)),
    INCallRecordTypeInProgress API_AVAILABLE(ios(13.0), watchos(6.0)),
    INCallRecordTypeOnHold API_AVAILABLE(ios(13.0), watchos(6.0)),
} API_AVAILABLE(ios(10.0), macos(12.0), watchos(3.2)) API_UNAVAILABLE(tvos);

#endif // INCallRecordType_h
