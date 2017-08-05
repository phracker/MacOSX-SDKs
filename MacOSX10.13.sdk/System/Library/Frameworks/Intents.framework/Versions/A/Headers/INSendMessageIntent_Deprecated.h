//
//  INRequestRideIntent_Deprecated.h
//  Intents
//
//  Copyright (c) 2016-2017 Apple Inc. All rights reserved.
//

#import <Intents/INSendMessageIntent.h>

NS_ASSUME_NONNULL_BEGIN

@interface INSendMessageIntent (Deprecated)

- (instancetype)initWithRecipients:(nullable NSArray<INPerson *> *)recipients
                           content:(nullable NSString *)content
                         groupName:(nullable NSString *)groupName
                       serviceName:(nullable NSString *)serviceName
                            sender:(nullable INPerson *)sender API_DEPRECATED("Use the designated initializer instead", ios(10.0, 11.0), watchos(3.2, 4.0), macosx(10.12, 10.13));

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) NSString *groupName API_DEPRECATED("Use speakableGroupNames instead", ios(10.0, 11.0), watchos(3.2, 4.0), macosx(10.12, 10.13));

@end

NS_ASSUME_NONNULL_END
