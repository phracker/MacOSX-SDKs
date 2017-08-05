//
//  INCallRecordType.h
//  Intents
//
//  Copyright © 2016 Apple. All rights reserved.
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
} API_AVAILABLE(macosx(10.12), ios(10.0));

#endif // INCallRecordType_h
