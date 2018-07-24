//
//  INRideDriver_Deprecated.h
//  Intents
//
//  Copyright (c) 2016-2017 Apple Inc. All rights reserved.
//

#import <Intents/INRideDriver.h>

NS_ASSUME_NONNULL_BEGIN

@interface INRideDriver (Deprecated)

- (instancetype)initWithPersonHandle:(INPersonHandle *)personHandle
                      nameComponents:(nullable NSPersonNameComponents *)nameComponents
                         displayName:(nullable NSString *)displayName
                               image:(nullable INImage *)image
                              rating:(nullable NSString *)rating
                         phoneNumber:(nullable NSString *)phoneNumber API_DEPRECATED("Use the designated initializer instead", ios(10.0, 10.2));

- (instancetype)initWithHandle:(NSString *)handle
                   displayName:(nullable NSString *)displayName
                         image:(nullable INImage *)image
                        rating:(nullable NSString *)rating
                   phoneNumber:(nullable NSString *)phoneNumber API_DEPRECATED("Use the designated initializer instead", ios(10.0, 10.0));

- (instancetype)initWithHandle:(NSString *)handle
                nameComponents:(NSPersonNameComponents *)nameComponents
                         image:(nullable INImage *)image
                        rating:(nullable NSString *)rating
                   phoneNumber:(nullable NSString *)phoneNumber API_DEPRECATED("Use the designated initializer instead", ios(10.0, 10.0));

@end

NS_ASSUME_NONNULL_END
