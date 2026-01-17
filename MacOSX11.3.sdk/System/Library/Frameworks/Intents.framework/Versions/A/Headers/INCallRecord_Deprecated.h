//
//  INCallRecord_Deprecated.h
//  Intents
//
//  Created by KRISHNA SHARMA on 12/14/20.
//  Copyright © 2020 Apple Inc. All rights reserved.
//

#import <Intents/INCallRecord.h>

NS_ASSUME_NONNULL_BEGIN

@interface INCallRecord (Deprecated)

- (instancetype)initWithIdentifier:(NSString *)identifier
                       dateCreated:(nullable NSDate *)dateCreated
                            caller:(nullable INPerson *)caller
                    callRecordType:(INCallRecordType)callRecordType
                    callCapability:(INCallCapability)callCapability
                      callDuration:(nullable NSNumber *)callDuration
                            unseen:(nullable NSNumber *)unseen NS_REFINED_FOR_SWIFT API_DEPRECATED("Replaced by -initWithIdentifier:dateCreated:callRecordType:callCapability:callDuration:unseen:participants:numberOfCalls:isCallerIdBlocked", ios(11.0, 14.5), watchos(4.0, 7.3), macosx(10.13, 11.3));

- (instancetype)initWithIdentifier:(NSString *)identifier
                       dateCreated:(nullable NSDate *)dateCreated
                            caller:(nullable INPerson *)caller
                    callRecordType:(INCallRecordType)callRecordType
                    callCapability:(INCallCapability)callCapability
                      callDuration:(nullable NSNumber *)callDuration
                            unseen:(nullable NSNumber *)unseen
                     numberOfCalls:(nullable NSNumber *)numberOfCalls NS_REFINED_FOR_SWIFT API_DEPRECATED("Replaced by -initWithIdentifier:dateCreated:callRecordType:callCapability:callDuration:unseen:participants:numberOfCalls:isCallerIdBlocked", ios(13.0, 14.5), watchos(6.0, 7.3), macosx(10.15, 11.3));

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) INPerson *caller API_DEPRECATED("", ios(11.0, 14.5), watchos(4.0, 7.3)) API_UNAVAILABLE(macos);

@end

NS_ASSUME_NONNULL_END
