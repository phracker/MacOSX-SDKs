//
//  INCallRecordFilter.h
//  Intents
//
//  Copyright (c) 2016-2021 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

#import <Intents/INCallCapability.h>
#import <Intents/INCallRecordTypeOptions.h>

@class INPerson;

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(14.0), watchos(7.0))
API_UNAVAILABLE(macos, tvos)
@interface INCallRecordFilter : NSObject <NSCopying, NSSecureCoding>

- (instancetype)init NS_UNAVAILABLE;

- (instancetype)initWithParticipants:(nullable NSArray<INPerson *> *)participants
                           callTypes:(INCallRecordTypeOptions)callTypes
                      callCapability:(INCallCapability)callCapability NS_DESIGNATED_INITIALIZER;

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) NSArray<INPerson *> *participants;

@property (readonly, assign, NS_NONATOMIC_IOSONLY) INCallRecordTypeOptions callTypes;

@property (readonly, assign, NS_NONATOMIC_IOSONLY) INCallCapability callCapability;

@end

NS_ASSUME_NONNULL_END
