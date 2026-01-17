//
//  Created by Dave Dribin on 11/2/17.
//  Copyright © 2017 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN


API_AVAILABLE(macos(13), ios(16), tvos(16))

NS_SWIFT_SENDABLE
@interface PHPersistentChangeToken : NSObject <NSCopying, NSSecureCoding>

+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
