//
//  INCallRecord.h
//  Intents
//
//  Copyright (c) 2016-2022 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

#import <Intents/INCallCapability.h>
#import <Intents/INCallRecordType.h>

@class INPerson;

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(11.0), macos(12.0), watchos(4.0))
API_UNAVAILABLE(tvos)
@interface INCallRecord : NSObject <NSCopying, NSSecureCoding>

- (instancetype)init NS_UNAVAILABLE;

- (instancetype)initWithIdentifier:(NSString *)identifier
                       dateCreated:(nullable NSDate *)dateCreated
                    callRecordType:(INCallRecordType)callRecordType
                    callCapability:(INCallCapability)callCapability
                      callDuration:(nullable NSNumber *)callDuration
                            unseen:(nullable NSNumber *)unseen
                      participants:(nullable NSArray<INPerson *> *)participants
                     numberOfCalls:(nullable NSNumber *)numberOfCalls
                 isCallerIdBlocked:(nullable NSNumber *)isCallerIdBlocked NS_DESIGNATED_INITIALIZER NS_REFINED_FOR_SWIFT API_AVAILABLE(ios(14.5), watchos(7.3));

- (instancetype)initWithIdentifier:(NSString *)identifier
                       dateCreated:(nullable NSDate *)dateCreated
                    callRecordType:(INCallRecordType)callRecordType
                    callCapability:(INCallCapability)callCapability
                      callDuration:(nullable NSNumber *)callDuration
                            unseen:(nullable NSNumber *)unseen NS_REFINED_FOR_SWIFT;

- (instancetype)initWithIdentifier:(NSString *)identifier
                       dateCreated:(nullable NSDate *)dateCreated
                    callRecordType:(INCallRecordType)callRecordType
                    callCapability:(INCallCapability)callCapability
                      callDuration:(nullable NSNumber *)callDuration
                            unseen:(nullable NSNumber *)unseen
                     numberOfCalls:(nullable NSNumber *)numberOfCalls NS_REFINED_FOR_SWIFT API_AVAILABLE(ios(13.0), watchos(6.0));

@property (readonly, copy, NS_NONATOMIC_IOSONLY) NSString *identifier;

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) NSDate *dateCreated;

@property (readonly, assign, NS_NONATOMIC_IOSONLY) INCallRecordType callRecordType;

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) NSNumber *callDuration NS_REFINED_FOR_SWIFT;

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) NSNumber *unseen NS_REFINED_FOR_SWIFT;

@property (readonly, assign, NS_NONATOMIC_IOSONLY) INCallCapability callCapability;

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) NSNumber *numberOfCalls NS_REFINED_FOR_SWIFT API_AVAILABLE(ios(13.0), watchos(6.0));

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) NSNumber *isCallerIdBlocked NS_REFINED_FOR_SWIFT API_AVAILABLE(ios(14.5), watchos(7.3));

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) NSArray<INPerson *> *participants API_AVAILABLE(ios(14.5), watchos(7.3));

@end

NS_ASSUME_NONNULL_END
