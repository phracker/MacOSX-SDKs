//
//  INStartAudioCallIntent_Deprecated.h
//  Intents
//
//  Copyright (c) 2016-2017 Apple Inc. All rights reserved.
//

#import <Intents/INStartAudioCallIntent.h>

NS_ASSUME_NONNULL_BEGIN

@interface INStartAudioCallIntent (Deprecated)

- (instancetype)initWithContacts:(nullable NSArray<INPerson *> *)contacts API_DEPRECATED("Use the designated initializer instead", ios(10.0, 11.0), watchos(3.2, 4.0), macosx(10.12, 10.13));

@end

NS_ASSUME_NONNULL_END
