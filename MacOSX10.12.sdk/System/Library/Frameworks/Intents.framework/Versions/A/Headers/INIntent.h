//
//  INIntent.h
//  Intents
//
//  Copyright © 2016 Apple. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(macosx(10.12), ios(10.0))
@interface INIntent : NSObject <NSCopying, NSSecureCoding>

// Returns the identifier of the receiver.
// Could be used to keep track of the entire transaction for resolve, confirm and handleIntent
@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) NSString *identifier;

@end

NS_ASSUME_NONNULL_END
