//
//  INCarHeadUnit.h
//  Intents
//
//  Copyright (c) 2016-2022 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(14.0), watchos(7.0))
API_UNAVAILABLE(macos, tvos)
@interface INCarHeadUnit : NSObject <NSCopying, NSSecureCoding>

- (instancetype)init NS_UNAVAILABLE;

// Instantiates an INHeadUnit object with the provided bluetooth identifier and iAP2 identifier.
- (instancetype)initWithBluetoothIdentifier:(nullable NSString *)bluetoothIdentifier
                             iAP2Identifier:(nullable NSString *)iAP2Identifier NS_DESIGNATED_INITIALIZER;

// The bluetooth identifier for the head unit.
@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) NSString *bluetoothIdentifier;

// The iAP2 identifier for the head unit.
@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) NSString *iAP2Identifier;

@end

NS_ASSUME_NONNULL_END
