//
//  INCallRecordType.h
//  Intents
//
//  Copyright (c) 2016-2019 Apple Inc. All rights reserved.
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
    INCallRecordTypeLatest API_AVAILABLE(ios(11.0), watchos(4.0)) API_UNAVAILABLE(macosx),
    INCallRecordTypeVoicemail API_AVAILABLE(ios(11.0), watchos(4.0)) API_UNAVAILABLE(macosx),
    INCallRecordTypeRinging API_UNAVAILABLE(ios, watchos, macosx),
    INCallRecordTypeInProgress API_UNAVAILABLE(ios, watchos, macosx),
    INCallRecordTypeOnHold API_UNAVAILABLE(ios, watchos, macosx),
} API_AVAILABLE(ios(10.0), watchos(3.2)) API_UNAVAILABLE(macosx);

#endif // INCallRecordType_h
