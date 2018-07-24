//
//  INPerson.h
//  Intents
//
//  Copyright (c) 2016-2017 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

#import <Intents/INPersonRelationship.h>

@class INImage;
@class INPersonHandle;

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(macosx(10.12), ios(10.0), watchos(3.2))
@interface INPerson : NSObject <NSCopying, NSSecureCoding>

- (instancetype)init NS_UNAVAILABLE;

- (instancetype)initWithPersonHandle:(INPersonHandle *)personHandle
                      nameComponents:(nullable NSPersonNameComponents *)nameComponents
                         displayName:(nullable NSString *)displayName
                               image:(nullable INImage *)image
                   contactIdentifier:(nullable NSString *)contactIdentifier
                    customIdentifier:(nullable NSString *)customIdentifier;

- (instancetype)initWithPersonHandle:(INPersonHandle *)personHandle
                      nameComponents:(nullable NSPersonNameComponents *)nameComponents
                         displayName:(nullable NSString *)displayName
                               image:(nullable INImage *)image
                   contactIdentifier:(nullable NSString *)contactIdentifier
                    customIdentifier:(nullable NSString *)customIdentifier
                                isMe:(BOOL)isMe NS_DESIGNATED_INITIALIZER API_AVAILABLE(ios(12.0), watchos(5.0), macosx(10.14));

// The identity of the person in the application
@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) INPersonHandle *personHandle;

// Returns the person's name components if this was initialized with them
@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) NSPersonNameComponents *nameComponents;

// This will return either the displayName if non-nil, else the formatted nameComponents, else the handle, else an empty string
@property (readonly, copy, NS_NONATOMIC_IOSONLY) NSString *displayName;

// Returns an image for the person.
@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) INImage *image;

// Reference to this person, if present in the system's Contacts store
@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) NSString *contactIdentifier;

// This property can be set to the app's identifier for this person
// It is also used as the vocabulary identifier for this person
@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) NSString *customIdentifier;

// This person's relationship to the user
@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) INPersonRelationship relationship API_AVAILABLE(ios(10.2), macosx(10.12.2));

@end

typedef NS_ENUM(NSInteger, INPersonSuggestionType) {
    INPersonSuggestionTypeNone API_AVAILABLE(macosx(10.14), ios(12.0), watchos(5.0)) = 0,
    INPersonSuggestionTypeSocialProfile,
    INPersonSuggestionTypeInstantMessageAddress
};

@interface INPerson (INInteraction)

// If your application has other representations for the person's handle, you can supply it for INInteraction donation
@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) NSArray<INPersonHandle *> *aliases;

// What Contact property this INInteraction donation should be suggested as when this person is matched to a contact in the system's Contacts store.
@property (readonly, NS_NONATOMIC_IOSONLY) INPersonSuggestionType suggestionType;

- (instancetype)initWithPersonHandle:(INPersonHandle *)personHandle
                      nameComponents:(nullable NSPersonNameComponents *)nameComponents
                         displayName:(nullable NSString *)displayName
                               image:(nullable INImage *)image
                   contactIdentifier:(nullable NSString *)contactIdentifier
                    customIdentifier:(nullable NSString *)customIdentifier
                             aliases:(nullable NSArray<INPersonHandle *> *)aliases
                      suggestionType:(INPersonSuggestionType)suggestionType;

@end

NS_ASSUME_NONNULL_END
