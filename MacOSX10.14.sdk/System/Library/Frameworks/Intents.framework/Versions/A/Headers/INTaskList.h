//
//  INTaskList.h
//  Intents
//
//  Copyright (c) 2016-2017 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

@class INSpeakableString;
@class INTask;

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(11.0), watchos(4.0))
API_UNAVAILABLE(macosx)
@interface INTaskList : NSObject <NSCopying, NSSecureCoding>

- (instancetype)initWithTitle:(INSpeakableString *)title
                        tasks:(NSArray<INTask *> *)tasks
                    groupName:(nullable INSpeakableString *)groupName
        createdDateComponents:(nullable NSDateComponents *)createdDateComponents
       modifiedDateComponents:(nullable NSDateComponents *)modifiedDateComponents
                   identifier:(nullable NSString *)identifier NS_DESIGNATED_INITIALIZER;

@property (readonly, copy, NS_NONATOMIC_IOSONLY) INSpeakableString *title;

@property (readonly, copy, NS_NONATOMIC_IOSONLY) NSArray<INTask *> *tasks;

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) INSpeakableString *groupName;

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) NSDateComponents *createdDateComponents;

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) NSDateComponents *modifiedDateComponents;

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) NSString *identifier;

@end

NS_ASSUME_NONNULL_END
