//
//  INCallRecord.h
//  Intents
//
//  Copyright (c) 2016-2017 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

#import <Intents/INCallRecordType.h>
#import <Intents/INCallCapability.h>

@class INPerson;

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(macosx(10.13), ios(11.0), watchos(4.0))
@interface INCallRecord : NSObject <NSCopying, NSSecureCoding>

- (id)init NS_UNAVAILABLE;

- (instancetype)initWithIdentifier:(NSString *)identifier
                       dateCreated:(nullable NSDate *)dateCreated
                            caller:(nullable INPerson *)caller
                    callRecordType:(INCallRecordType)callRecordType
                    callCapability:(INCallCapability)callCapability
                      callDuration:(nullable NSNumber *)callDuration
                            unseen:(nullable NSNumber *)unseen NS_DESIGNATED_INITIALIZER NS_REFINED_FOR_SWIFT;

@property (readonly, copy, NS_NONATOMIC_IOSONLY) NSString *identifier;

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) NSDate *dateCreated;

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) INPerson *caller;

@property (readonly, NS_NONATOMIC_IOSONLY) INCallRecordType callRecordType;

@property (readonly, NS_NONATOMIC_IOSONLY) INCallCapability callCapability;

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) NSNumber *callDuration NS_REFINED_FOR_SWIFT;

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) NSNumber *unseen NS_REFINED_FOR_SWIFT;

@end

NS_ASSUME_NONNULL_END
