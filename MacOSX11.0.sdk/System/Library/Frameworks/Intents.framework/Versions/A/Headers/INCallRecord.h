//
//  INCallRecord.h
//  Intents
//
//  Copyright (c) 2016-2020 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

#import <Intents/INCallCapability.h>
#import <Intents/INCallRecordType.h>

@class INPerson;

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(11.0), watchos(4.0))
API_UNAVAILABLE(macos, tvos)
@interface INCallRecord : NSObject <NSCopying, NSSecureCoding>

- (instancetype)init NS_UNAVAILABLE;

- (instancetype)initWithIdentifier:(NSString *)identifier
                       dateCreated:(nullable NSDate *)dateCreated
                            caller:(nullable INPerson *)caller
                    callRecordType:(INCallRecordType)callRecordType
                    callCapability:(INCallCapability)callCapability
                      callDuration:(nullable NSNumber *)callDuration
                            unseen:(nullable NSNumber *)unseen
                     numberOfCalls:(nullable NSNumber *)numberOfCalls NS_DESIGNATED_INITIALIZER NS_REFINED_FOR_SWIFT API_AVAILABLE(ios(13.0), watchos(6.0), macosx(10.15));

- (instancetype)initWithIdentifier:(NSString *)identifier
                       dateCreated:(nullable NSDate *)dateCreated
                            caller:(nullable INPerson *)caller
                    callRecordType:(INCallRecordType)callRecordType
                    callCapability:(INCallCapability)callCapability
                      callDuration:(nullable NSNumber *)callDuration
                            unseen:(nullable NSNumber *)unseen NS_REFINED_FOR_SWIFT;

@property (readonly, copy, NS_NONATOMIC_IOSONLY) NSString *identifier;

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) NSDate *dateCreated;

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) INPerson *caller;

@property (readonly, assign, NS_NONATOMIC_IOSONLY) INCallRecordType callRecordType;

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) NSNumber *callDuration NS_REFINED_FOR_SWIFT;

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) NSNumber *unseen NS_REFINED_FOR_SWIFT;

@property (readonly, assign, NS_NONATOMIC_IOSONLY) INCallCapability callCapability;

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) NSNumber *numberOfCalls NS_REFINED_FOR_SWIFT API_AVAILABLE(ios(13.0), watchos(6.0)) API_UNAVAILABLE(macos);

@end

NS_ASSUME_NONNULL_END
