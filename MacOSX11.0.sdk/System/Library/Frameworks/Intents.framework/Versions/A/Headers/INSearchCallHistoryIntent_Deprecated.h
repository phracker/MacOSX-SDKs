//
//  INSearchCallHistoryIntent_Deprecated.h
//  Intents
//
//  Copyright (c) 2016-2020 Apple Inc. All rights reserved.
//

#import <Intents/INCallRecordType.h>
#import <Intents/INSearchCallHistoryIntent.h>

NS_ASSUME_NONNULL_BEGIN

@interface INSearchCallHistoryIntent (Deprecated)

- (instancetype)initWithCallType:(INCallRecordType)callType
                     dateCreated:(nullable INDateComponentsRange *)dateCreated
                       recipient:(nullable INPerson *)recipient
                callCapabilities:(INCallCapabilityOptions)callCapabilities API_DEPRECATED("Use the designated initializer instead", ios(10.0, 11.0), watchos(3.2, 4.0));

// What type of call record to search for.
@property (readonly, assign, NS_NONATOMIC_IOSONLY) INCallRecordType callType API_DEPRECATED("Use callTypes instead", ios(10.0, 11.0), watchos(3.2, 4.0));

@end

NS_ASSUME_NONNULL_END
