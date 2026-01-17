//
//  INIntent.h
//  Intents
//
//  Copyright (c) 2016-2017 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(macosx(10.12), ios(10.0), watchos(3.2))
@interface INIntent : NSObject <NSCopying, NSSecureCoding>

// Returns the identifier of the receiver.
// Could be used to keep track of the entire transaction for resolve, confirm and handleIntent
@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) NSString *identifier;

// A human-understandable string representation of the intent's user-facing behavior
@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) NSString *intentDescription API_AVAILABLE(ios(11.0), watchos(4.0), macosx(10.13));

@end

NS_ASSUME_NONNULL_END
