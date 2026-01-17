//
//  INSetDefrosterSettingsInCarIntent_Deprecated.h
//  Intents
//
//  Copyright (c) 2016-2020 Apple Inc. All rights reserved.
//

#import <Intents/INSetDefrosterSettingsInCarIntent.h>

NS_ASSUME_NONNULL_BEGIN

@interface INSetDefrosterSettingsInCarIntent (Deprecated)

- (instancetype)initWithEnable:(nullable NSNumber *)enable
                     defroster:(INCarDefroster)defroster API_DEPRECATED_WITH_REPLACEMENT("-initWithEnable:defroster:carName:", ios(10.0, 12.0)) NS_REFINED_FOR_SWIFT;

@end

NS_ASSUME_NONNULL_END
