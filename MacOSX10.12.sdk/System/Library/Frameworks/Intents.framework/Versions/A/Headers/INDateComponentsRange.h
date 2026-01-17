//
//  INDateComponentsRange.h
//  Intents
//
//  Copyright © 2016 Apple. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(macosx(10.12), ios(10.0))
@interface INDateComponentsRange : NSObject <NSCopying, NSSecureCoding>

- (instancetype)init NS_UNAVAILABLE;

- (instancetype)initWithStartDateComponents:(nullable NSDateComponents *)startDateComponents
                          endDateComponents:(nullable NSDateComponents *)endDateComponents NS_DESIGNATED_INITIALIZER;

@property (copy, readonly, nullable, NS_NONATOMIC_IOSONLY) NSDateComponents *startDateComponents;

@property (copy, readonly, nullable, NS_NONATOMIC_IOSONLY) NSDateComponents *endDateComponents;

@end

NS_ASSUME_NONNULL_END
