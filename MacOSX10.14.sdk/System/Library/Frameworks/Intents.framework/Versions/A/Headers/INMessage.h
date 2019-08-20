//
//  INMessage.h
//  Intents
//
//  Copyright (c) 2016-2017 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

@class INPerson;
@class INSpeakableString;

NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(NSInteger, INMessageType) {
    INMessageTypeUnspecified = 0,
    INMessageTypeText,
    INMessageTypeAudio,
    INMessageTypeDigitalTouch,
    INMessageTypeHandwriting,
    INMessageTypeSticker,
    INMessageTypeTapbackLiked,
    INMessageTypeTapbackDisliked,
    INMessageTypeTapbackEmphasized,
    INMessageTypeTapbackLoved,
    INMessageTypeTapbackQuestioned,
    INMessageTypeTapbackLaughed,
    INMessageTypeMediaCalendar,
    INMessageTypeMediaLocation,
    INMessageTypeMediaAddressCard,
    INMessageTypeMediaImage,
    INMessageTypeMediaVideo,
    INMessageTypeMediaPass,
    INMessageTypeMediaAudio,
    INMessageTypePaymentSent API_AVAILABLE(macosx(10.14), ios(12.0), watchos(5.0)),
    INMessageTypePaymentRequest API_AVAILABLE(macosx(10.14), ios(12.0), watchos(5.0)),
    INMessageTypePaymentNote API_AVAILABLE(macosx(10.14), ios(12.0), watchos(5.0)),
    INMessageTypeAnimoji API_AVAILABLE(macosx(10.14), ios(12.0), watchos(5.0)),
    INMessageTypeActivitySnippet API_AVAILABLE(macosx(10.14), ios(12.0), watchos(5.0)),
    INMessageTypeFile API_AVAILABLE(macosx(10.14), ios(12.0), watchos(5.0)),
    INMessageTypeLink API_AVAILABLE(macosx(10.14), ios(12.0), watchos(5.0)),
} API_AVAILABLE(macosx(10.13), ios(11.0), watchos(4.0));

API_AVAILABLE(macosx(10.12), ios(10.0), watchos(3.2))
@interface INMessage : NSObject <NSCopying, NSSecureCoding>

- (id)init NS_UNAVAILABLE;

- (instancetype)initWithIdentifier:(NSString *)identifier
            conversationIdentifier:(nullable NSString *)conversationIdentifier
                           content:(nullable NSString *)content
                          dateSent:(nullable NSDate *)dateSent
                            sender:(nullable INPerson *)sender
                        recipients:(nullable NSArray<INPerson *> *)recipients
                         groupName:(nullable INSpeakableString *)groupName
                       messageType:(INMessageType)messageType NS_DESIGNATED_INITIALIZER API_AVAILABLE(macosx(10.13), ios(11.0), watchos(4.0));

- (instancetype)initWithIdentifier:(NSString *)identifier
            conversationIdentifier:(nullable NSString *)conversationIdentifier
                           content:(nullable NSString *)content
                          dateSent:(nullable NSDate *)dateSent
                            sender:(nullable INPerson *)sender
                        recipients:(nullable NSArray<INPerson *> *)recipients
                       messageType:(INMessageType)messageType API_AVAILABLE(macosx(10.13), ios(11.0), watchos(4.0));

- (instancetype)initWithIdentifier:(NSString *)identifier
                           content:(nullable NSString *)content
                          dateSent:(nullable NSDate *)dateSent
                            sender:(nullable INPerson *)sender
                        recipients:(nullable NSArray<INPerson *> *)recipients;

@property (readonly, copy, NS_NONATOMIC_IOSONLY) NSString *identifier;

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) NSString *conversationIdentifier API_AVAILABLE(macosx(10.13), ios(11.0), watchos(4.0));

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) NSString *content;

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) NSDate *dateSent;

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) INPerson *sender;

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) NSArray<INPerson *> *recipients;

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) INSpeakableString *groupName API_AVAILABLE(macosx(10.13), ios(11.0), watchos(4.0));

@property (readonly, NS_NONATOMIC_IOSONLY) INMessageType messageType API_AVAILABLE(macosx(10.13), ios(11.0), watchos(4.0));

@end

NS_ASSUME_NONNULL_END
