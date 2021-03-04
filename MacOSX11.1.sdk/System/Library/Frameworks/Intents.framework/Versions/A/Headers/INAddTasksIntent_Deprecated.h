//
//  INAddTasksIntent+Deprecated.h
//  Intents
//
//  Copyright © 2019 Apple. All rights reserved.
//

#import <Intents/INAddTasksIntent.h>

NS_ASSUME_NONNULL_BEGIN

@interface INAddTasksIntent (Deprecated)

- (instancetype)initWithTargetTaskList:(nullable INTaskList *)targetTaskList
                            taskTitles:(nullable NSArray<INSpeakableString *> *)taskTitles
                   spatialEventTrigger:(nullable INSpatialEventTrigger *)spatialEventTrigger
                  temporalEventTrigger:(nullable INTemporalEventTrigger *)temporalEventTrigger API_DEPRECATED_WITH_REPLACEMENT("-initWithTargetTaskList:taskTitles:spatialEventTrigger:temporalEventTrigger:priority:", ios(11.0, 13.0), watchos(4.0, 6.0));

@end

NS_ASSUME_NONNULL_END
