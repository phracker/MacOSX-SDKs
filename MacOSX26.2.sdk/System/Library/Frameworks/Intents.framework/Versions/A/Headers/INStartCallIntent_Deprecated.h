//
//  INStartCallIntent_Deprecated.h
//  Intents
//
//  Copyright (c) 2016-2020 Apple Inc. All rights reserved.
//

#import <Intents/INStartCallIntent.h>

NS_ASSUME_NONNULL_BEGIN

@interface INStartCallIntent (Deprecated)

- (instancetype)initWithAudioRoute:(INCallAudioRoute)audioRoute
                   destinationType:(INCallDestinationType)destinationType
                          contacts:(nullable NSArray<INPerson *> *)contacts
            recordTypeForRedialing:(INCallRecordType)recordTypeForRedialing
                    callCapability:(INCallCapability)callCapability API_DEPRECATED_WITH_REPLACEMENT("-initWithCallRecordFilter:callRecordToCallBack:audioRoute:destinationType:contacts:callCapability:", ios(13.0, 14.0), watchos(6.0, 7.0)) API_UNAVAILABLE(macos);

@property (readonly, assign, NS_NONATOMIC_IOSONLY) INCallRecordType recordTypeForRedialing API_DEPRECATED("", ios(13.0, 14.0), watchos(6.0, 7.0)) API_UNAVAILABLE(macos);

@end

NS_ASSUME_NONNULL_END
