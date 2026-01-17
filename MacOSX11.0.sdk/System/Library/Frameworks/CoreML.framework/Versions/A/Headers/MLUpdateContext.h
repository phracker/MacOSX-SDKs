//
//  MLUpdateContext.h
//  CoreML
//
//  Copyright © 2019 Apple Inc. All rights reserved.
//

#import <CoreML/CoreML.h>

NS_ASSUME_NONNULL_BEGIN

@class MLUpdateTask;
@class MLMetricKey;
@protocol MLWritable;

/*!
 * Provides context for the update process when the progress or completion handlers are invoked.
 */
ML_EXPORT
API_AVAILABLE(macos(10.15), ios(13.0), tvos(14.0))
@interface MLUpdateContext : NSObject

// Reference to the update task that invokved the progress or completion handlers.
@property (readonly, nonatomic) MLUpdateTask *task;

// Reference to the updated model that can be used for additional validation or evaluation.
@property (readonly, nonatomic) MLModel<MLWritable> *model;

// Indicates the event the progress handler invocation corresponds to. This will be one of the events app registered via MLUpdateProgressHandlers.interestedEvents.
@property (readonly, nonatomic) MLUpdateProgressEvent event;

// Metrics computed on the training input during the update process.
@property (readonly, nonatomic) NSDictionary <MLMetricKey *, id> *metrics;

// A snapshot of parameters (including their values) used during the update process.
@property (readonly, nonatomic) NSDictionary <MLParameterKey *, id> *parameters;

@end

NS_ASSUME_NONNULL_END

