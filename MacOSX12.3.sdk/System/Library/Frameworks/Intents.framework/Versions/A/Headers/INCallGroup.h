//
//  INCallGroup.h
//  Intents
//
//  Copyright (c) 2016-2022 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(14.5), macos(11.3), watchos(7.3))
API_UNAVAILABLE(tvos)
@interface INCallGroup : NSObject <NSCopying, NSSecureCoding>

- (instancetype)init NS_UNAVAILABLE;

- (instancetype)initWithGroupName:(nullable NSString *)groupName
                          groupId:(nullable NSString *)groupId NS_DESIGNATED_INITIALIZER;

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) NSString *groupName;

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) NSString *groupId;

@end

NS_ASSUME_NONNULL_END
