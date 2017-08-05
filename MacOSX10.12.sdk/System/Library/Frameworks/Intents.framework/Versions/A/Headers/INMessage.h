//
//  INMessage.h
//  Intents
//
//  Copyright © 2016 Apple. All rights reserved.
//

#import <Foundation/Foundation.h>

@class INPerson;

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(macosx(10.12), ios(10.0))
@interface INMessage : NSObject <NSCopying, NSSecureCoding>

- (id)init NS_UNAVAILABLE;

- (instancetype)initWithIdentifier:(NSString *)identifier
                           content:(nullable NSString *)content
                          dateSent:(nullable NSDate *)dateSent
                            sender:(nullable INPerson *)sender
                        recipients:(nullable NSArray<INPerson *> *)recipients NS_DESIGNATED_INITIALIZER;

@property (readonly, copy, NS_NONATOMIC_IOSONLY) NSString *identifier;

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) NSString *content;

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) NSDate *dateSent;

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) INPerson *sender;

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) NSArray<INPerson *> *recipients;

@end

NS_ASSUME_NONNULL_END
