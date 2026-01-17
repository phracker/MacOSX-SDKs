//
//  INPerson.h
//  Intents
//
//  Copyright (c) 2016-2020 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

#import <Intents/INPersonRelationship.h>

@class INImage;
@class INPersonHandle;

typedef NS_ENUM(NSInteger, INPersonSuggestionType) {
    INPersonSuggestionTypeNone API_AVAILABLE(ios(12.0), watchos(5.0)),
    INPersonSuggestionTypeSocialProfile,
    INPersonSuggestionTypeInstantMessageAddress
} API_AVAILABLE(ios(10.0), macos(11.0), watchos(3.2)) API_UNAVAILABLE(tvos);

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(10.0), macos(11.0), watchos(3.2))
API_UNAVAILABLE(tvos)
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
                        relationship:(nullable INPersonRelationship)relationship API_AVAILABLE(ios(14.0), watchos(7.0));

- (instancetype)initWithPersonHandle:(INPersonHandle *)personHandle
                      nameComponents:(nullable NSPersonNameComponents *)nameComponents
                         displayName:(nullable NSString *)displayName
                               image:(nullable INImage *)image
                   contactIdentifier:(nullable NSString *)contactIdentifier
                    customIdentifier:(nullable NSString *)customIdentifier
                                isMe:(BOOL)isMe NS_DESIGNATED_INITIALIZER API_AVAILABLE(ios(12.0), watchos(5.0));

- (instancetype)initWithPersonHandle:(INPersonHandle *)personHandle
                      nameComponents:(nullable NSPersonNameComponents *)nameComponents
                         displayName:(nullable NSString *)displayName
                               image:(nullable INImage *)image
                   contactIdentifier:(nullable NSString *)contactIdentifier
                    customIdentifier:(nullable NSString *)customIdentifier
                                isMe:(BOOL)isMe
                     suggestionType:(INPersonSuggestionType)suggestionType API_AVAILABLE(ios(15.0), macos(12.0), watchos(8.0));

- (instancetype)initWithPersonHandle:(INPersonHandle *)personHandle
                      nameComponents:(nullable NSPersonNameComponents *)nameComponents
                         displayName:(nullable NSString *)displayName
                               image:(nullable INImage *)image
                   contactIdentifier:(nullable NSString *)contactIdentifier
                    customIdentifier:(nullable NSString *)customIdentifier
                 isContactSuggestion:(BOOL)isContactSuggestion
                      suggestionType:(INPersonSuggestionType)suggestionType API_AVAILABLE(ios(15.0), macos(12.0), watchos(8.0));

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
@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) INPersonRelationship relationship API_AVAILABLE(ios(10.2));

// Indicates that the person is confirmed
@property (readonly, NS_NONATOMIC_IOSONLY, getter=isContactSuggestion) BOOL contactSuggestion API_AVAILABLE(ios(15.0), macos(12.0), watchos(8.0));

@end

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
