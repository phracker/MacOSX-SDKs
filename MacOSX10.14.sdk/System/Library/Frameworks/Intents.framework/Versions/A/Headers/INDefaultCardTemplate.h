//
//  INDefaultCardTemplate.h
//  Intents
//
//  Copyright © 2018 Apple. All rights reserved.
//

#import <Intents/INImage.h>

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(12.0), watchos(5.0)) API_UNAVAILABLE(macosx)
@interface INDefaultCardTemplate : NSObject <NSCopying, NSSecureCoding>

@property (copy, NS_NONATOMIC_IOSONLY) NSString *title;
@property (copy, nullable, NS_NONATOMIC_IOSONLY) NSString *subtitle;
@property (copy, nullable, NS_NONATOMIC_IOSONLY) INImage *image;

+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;
- (instancetype)initWithTitle:(NSString *)title NS_DESIGNATED_INITIALIZER;

@end

NS_ASSUME_NONNULL_END
