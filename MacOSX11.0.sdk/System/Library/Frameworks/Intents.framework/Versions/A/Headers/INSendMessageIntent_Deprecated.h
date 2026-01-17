//
//  INRequestRideIntent_Deprecated.h
//  Intents
//
//  Copyright (c) 2016-2020 Apple Inc. All rights reserved.
//

#import <Intents/INSendMessageIntent.h>

NS_ASSUME_NONNULL_BEGIN

@interface INSendMessageIntent (Deprecated)

- (instancetype)initWithRecipients:(nullable NSArray<INPerson *> *)recipients
                           content:(nullable NSString *)content
                         groupName:(nullable NSString *)groupName
                       serviceName:(nullable NSString *)serviceName
                            sender:(nullable INPerson *)sender API_DEPRECATED("Use the designated initializer instead", ios(10.0, 11.0), watchos(3.2, 4.0));

- (instancetype)initWithRecipients:(nullable NSArray<INPerson *> *)recipients
                           content:(nullable NSString *)content
                speakableGroupName:(nullable INSpeakableString *)speakableGroupName
            conversationIdentifier:(nullable NSString *)conversationIdentifier
                       serviceName:(nullable NSString *)serviceName
                            sender:(nullable INPerson *)sender API_DEPRECATED("Use the designated initializer with outgoingMessageType instead", ios(11.0, 14.0), watchos(4.0, 7.0), macosx(10.13, 11.0));

- (instancetype)initWithRecipients:(nullable NSArray<INPerson *> *)recipients
               outgoingMessageType:(INOutgoingMessageType)outgoingMessageType
                           content:(nullable NSString *)content
                speakableGroupName:(nullable INSpeakableString *)speakableGroupName
            conversationIdentifier:(nullable NSString *)conversationIdentifier
                       serviceName:(nullable NSString *)serviceName
                            sender:(nullable INPerson *)sender API_DEPRECATED("Use the designated initializer with attachments instead instead", ios(14.0, 14.0), watchos(7.0, 7.0), macosx(10.16, 11.0));

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) NSString *groupName API_DEPRECATED("Use speakableGroupNames instead", ios(10.0, 11.0), watchos(3.2, 4.0));

@end

NS_ASSUME_NONNULL_END
