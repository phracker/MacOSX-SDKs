//
//  INSetTaskAttributeIntent_Deprecated.h
//  Intents
//
//  Copyright (c) 2016-2020 Apple Inc. All rights reserved.
//

#import <Intents/INSetTaskAttributeIntent.h>

NS_ASSUME_NONNULL_BEGIN

@interface INSetTaskAttributeIntent (Deprecated)

- (instancetype)initWithTargetTask:(nullable INTask *)targetTask
                            status:(INTaskStatus)status
               spatialEventTrigger:(nullable INSpatialEventTrigger *)spatialEventTrigger
              temporalEventTrigger:(nullable INTemporalEventTrigger *)temporalEventTrigger API_DEPRECATED("Use the designated initializer instead", ios(11.0, 13.0), watchos(4.0, 6.0));

@end

NS_ASSUME_NONNULL_END
