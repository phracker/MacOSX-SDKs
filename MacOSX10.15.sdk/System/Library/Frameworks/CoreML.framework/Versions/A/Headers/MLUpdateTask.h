//
//  MLUpdateTask.h
//  CoreML
//
//  Copyright © 2019 Apple Inc. All rights reserved.
//

#import <CoreML/CoreML.h>

NS_ASSUME_NONNULL_BEGIN

@class MLUpdateContext;
@class MLUpdateProgressHandlers;

/*!
 * Main class for setting up and controlling a model update. It provides some utility class methods for performing an update synchronously as well as class constructors for configuring an update and give developers control for the execution of that update.
 */
ML_EXPORT
API_AVAILABLE(macos(10.15), ios(13.0))
@interface MLUpdateTask : MLTask

// Update via task control with completion handler
+ (nullable instancetype)updateTaskForModelAtURL:(NSURL *)modelURL
                                    trainingData:(id<MLBatchProvider>)trainingData
                                   configuration:(nullable MLModelConfiguration *)configuration
                               completionHandler:(void (^)(MLUpdateContext * context))completionHandler
                                           error:(NSError * _Nullable * _Nullable)error;

// Update via task control and custom progress callbacks
+ (nullable instancetype)updateTaskForModelAtURL:(NSURL *)modelURL
                                    trainingData:(id<MLBatchProvider>)trainingData
                                   configuration:(nullable MLModelConfiguration *)configuration
                                progressHandlers:(MLUpdateProgressHandlers *)progressHandlers
                                           error:(NSError * _Nullable * _Nullable)error;

// Request a resume with new parameters. Should be used within a progressHandler
- (void)resumeWithParameters:(NSDictionary<MLParameterKey *, id> *)updateParameters;

// cannot construct MLUpdateTask without parameters.
- (instancetype)init NS_UNAVAILABLE;

// cannot construct MLUpdateTask without parameters.
+ (id)new NS_UNAVAILABLE;

@end


NS_ASSUME_NONNULL_END

