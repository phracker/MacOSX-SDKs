//
//  INPerson_Deprecated.h
//  Intents
//
//  Copyright (c) 2016-2017 Apple Inc. All rights reserved.
//

#import <Intents/INPerson.h>

NS_ASSUME_NONNULL_BEGIN

@interface INPerson (Deprecated)

// The identity of the person in the application (e.g. email address, phone number, user handle, etc.)
@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) NSString *handle  API_DEPRECATED("Use personHandle instead", ios(10.0, 10.0), macosx(10.12, 10.12));

//  This is the preferred convenience initializer if the app knows the name components of the person (e.g. given name, family name, etc).
- (instancetype)initWithHandle:(NSString *)handle
                nameComponents:(NSPersonNameComponents *)nameComponents
             contactIdentifier:(nullable NSString *)contactIdentifier API_DEPRECATED("Use the designated initializer instead", ios(10.0, 10.0), macosx(10.12, 10.12));

// Use this convenience initializer if the person's name is unknown
- (instancetype)initWithHandle:(NSString *)handle
                   displayName:(nullable NSString *)displayName
             contactIdentifier:(nullable NSString *)contactIdentifier API_DEPRECATED("Use the designated initializer instead", ios(10.0, 10.0), macosx(10.12, 10.12));

- (instancetype)initWithHandle:(NSString *)handle
                nameComponents:(nullable NSPersonNameComponents *)nameComponents
                   displayName:(nullable NSString *)displayName
                         image:(nullable INImage *)image
             contactIdentifier:(nullable NSString *)contactIdentifier API_DEPRECATED("Use the designated initializer instead", ios(10.0, 10.0), macosx(10.12, 10.12));




@end

NS_ASSUME_NONNULL_END
