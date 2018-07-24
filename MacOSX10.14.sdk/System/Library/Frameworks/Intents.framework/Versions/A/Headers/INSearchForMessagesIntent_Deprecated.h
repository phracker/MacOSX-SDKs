//
//  INRequestRideIntent_Deprecated.h
//  Intents
//
//  Copyright (c) 2016-2017 Apple Inc. All rights reserved.
//

#import <Intents/INSearchForMessagesIntent.h>

NS_ASSUME_NONNULL_BEGIN

@interface INSearchForMessagesIntent (DeprecatedSearchForMessages)

- (instancetype)initWithRecipients:(nullable NSArray<INPerson *> *)recipients
                           senders:(nullable NSArray<INPerson *> *)senders
                       searchTerms:(nullable NSArray<NSString *> *)searchTerms
                        attributes:(INMessageAttributeOptions)attributes
                     dateTimeRange:(nullable INDateComponentsRange *)dateTimeRange
                       identifiers:(nullable NSArray<NSString *> *)identifiers
           notificationIdentifiers:(nullable NSArray<NSString *> *)notificationIdentifiers
                        groupNames:(nullable NSArray<NSString *> *)groupNames API_DEPRECATED("Use the designated initializer instead", ios(10.0, 11.0), watchos(3.2, 4.0), macosx(10.12, 10.13));

- (instancetype)initWithRecipients:(nullable NSArray<INPerson *> *)recipients
                           senders:(nullable NSArray<INPerson *> *)senders
                       searchTerms:(nullable NSArray<NSString *> *)searchTerms
                        attributes:(INMessageAttributeOptions)attributes
                     dateTimeRange:(nullable INDateComponentsRange *)dateTimeRange
                       identifiers:(nullable NSArray<NSString *> *)identifiers
           notificationIdentifiers:(nullable NSArray<NSString *> *)notificationIdentifiers
               speakableGroupNames:(nullable NSArray<INSpeakableString *> *)speakableGroupNames API_DEPRECATED("Use the designated initializer instead", ios(11.0, 12.0), watchos(4.0, 5.0), macosx(10.13, 10.14));

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) NSArray<NSString *> *groupNames API_DEPRECATED("Use speakableGroupNames instead", ios(10.0, 11.0), watchos(3.2, 4.0), macosx(10.12, 10.13));

@property (readonly, assign, NS_NONATOMIC_IOSONLY) INConditionalOperator groupNamesOperator API_DEPRECATED("Use speakableGroupNamesOperator instead", ios(10.0, 11.0), watchos(3.2, 4.0), macosx(10.12, 10.13));

@end

NS_ASSUME_NONNULL_END
