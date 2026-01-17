//
//  Created by Dave Dribin on 2/9/18.
//  Copyright © 2018 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@class PHChange;
@class PHPersistentChange;
@class PHPersistentChangeToken;


API_AVAILABLE(macos(13), ios(16), tvos(16))

@interface PHPersistentChangeFetchResult : NSObject

+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;

- (void)enumerateChangesWithBlock:(void (NS_NOESCAPE ^)(PHPersistentChange *change, BOOL *stop))block NS_REFINED_FOR_SWIFT;

@end

NS_ASSUME_NONNULL_END
