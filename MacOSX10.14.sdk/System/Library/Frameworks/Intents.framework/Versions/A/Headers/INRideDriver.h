//
//  INRideDriver.h
//  Intents
//
//  Copyright (c) 2016-2017 Apple Inc. All rights reserved.
//

#import <Intents/INPerson.h>

@class INImage;
@class INPersonHandle;

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(10.0), watchos(3.2))
API_UNAVAILABLE(macosx)
@interface INRideDriver : INPerson <NSCopying, NSSecureCoding>

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) NSString *rating;
@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) NSString *phoneNumber;

- (instancetype)initWithPhoneNumber:(NSString *)phoneNumber
                     nameComponents:(nullable NSPersonNameComponents *)nameComponents
                        displayName:(nullable NSString *)displayName
                              image:(nullable INImage *)image
                             rating:(nullable NSString *)rating NS_DESIGNATED_INITIALIZER API_AVAILABLE(ios(10.2), watchos(3.2)) API_UNAVAILABLE(macosx);

@end
 
NS_ASSUME_NONNULL_END
