/*
	File:  VTFrameProcessor.h
 
	Framework:  VideoToolbox
 
	Copyright © 2023-2024 Apple Inc. All rights reserved.
 
*/

#ifndef VTFRAMEPROCESSOR_H
#define VTFRAMEPROCESSOR_H

#ifdef __OBJC__

#import <CoreMedia/CMBase.h>
#import <VideoToolbox/VTFrameProcessorConfiguration.h>
#import <VideoToolbox/VTFrameProcessorParameters.h>
#import <VideoToolbox/VTFrameProcessorFrame.h>
#import <VideoToolbox/VTFrameProcessorErrors.h>
#if ! TARGET_OS_SIMULATOR
#import <VideoToolbox/VTFrameProcessor_MotionBlur.h>
#import <VideoToolbox/VTFrameProcessor_FrameRateConversion.h>
#import <VideoToolbox/VTFrameProcessor_OpticalFlow.h>
#import <VideoToolbox/VTFrameProcessor_TemporalNoiseFilter.h>
#endif // ! TARGET_OS_SIMULATOR
#import <Metal/Metal.h>


NS_HEADER_AUDIT_BEGIN(nullability, sendability)

/// Provides a unified interface you can use to apply video effects to frames.
///
/// The VTFrameProcessor gives access to a set of powerful video processing implementation suitable for different use cases.
/// A configuration object (conforming to the ``VTFrameProcessorConfiguration`` protocol) passes initialization and
/// configuration parameters for the processor. A Parameter object (conforming to the ``VTFrameProcessorParameters``
/// protocol) provides the parameters for each individual processing operation. A Configuration object and a Parameter
/// object define each processor implementation. These Configuration and Parameters objects for each implementation are
/// defined in a processor-specific header file.
///
/// Use an instance of this class to apply configured video effects either directly to pixel buffers or as a
/// part of Metal pipeline. The video effect must be specified as a ``VTFrameProcessorConfiguration`` instance at session
/// startup. Once a session is started, you need to call one of the process methods for each input frame. After all input
/// frames have been provided, session must be ended for the system to finish all pending processing.
///
/// After you call the process function, you must not modify input and output buffers (including attachments) before the
/// function returns or the system receives the callback, in the case of asynchronous processing.
API_AVAILABLE(macos(15.4), ios(26.0), tvos(26.0), visionos(26.0)) API_UNAVAILABLE(watchos)
@interface VTFrameProcessor : NSObject

/// Create a new instance of the frame processor.
- (instancetype) init;

/// Starts a new session and configures the processor pipeline for an effect.
///
/// - Parameters:
///   - configuration: The system uses this parameter to create an effect pipeline for processing frames. This object
///       must conform to the ``VTFrameProcessorConfiguration`` interface.
///   - error: Contains error information if any. You may specify NULL for this parameter if you do not want the error information.
- (BOOL) startSessionWithConfiguration:(id<VTFrameProcessorConfiguration>)configuration
                                 error:(NSError * _Nullable * _Nullable)error NS_SWIFT_NAME(startSession(configuration:));

/// Synchronously performs the processor effects.
///
/// Use the respective ``VTFrameProcessorParameters`` to pass frame level settings and frame level input/output parameters
/// for the effect that you configured this session for by calling ``startSessionWithConfiguration:error``.
///
/// - Parameters:
///   - parameters: A `VTFrameProcessorParameters` based object to specify additional frame based parameters to use
///     during processing. It needs to match the configuration type used during start session.
///   - error: Contains error information if any. You may specify NULL for this parameter if you do not want the error information.
- (BOOL) processWithParameters:(id<VTFrameProcessorParameters>)parameters
                         error:(NSError * _Nullable * _Nullable)error NS_SWIFT_UNAVAILABLE("use the async version processWithParameters:completionHandler instead");

/// Asynchronously performs the processor effects.
///
/// - Parameters:
///   - parameters: A `VTFrameProcessorParameters` based object to specify additional frame based parameters to use
///     during processing. It needs to match the configuration type used during start session.
///   - completionHandler: This completion handler is called when frame processing is completed. The completion handler
///     receives the same parameters object that you provided to the original call, as well as an `NSError` which contains
///     an error code if processing was not successful.
- (void) processWithParameters:(id<VTFrameProcessorParameters>)parameters
             completionHandler:(void (^)(id<VTFrameProcessorParameters> , NSError * _Nullable) )completionHandler NS_SWIFT_NAME(process(parameters:completionHandler:));

/// Asynchronously performs the processor effects and outputs each frame separately.
///
/// Use with frame processor configurations which allow multiple output frames from a single processing call, such
/// as frame rate conversion processor cases when you need access to output frames as they become available, rather than
/// waiting for all output frames to be complete.
///
/// This interface is suitable for low-latency scenarios when a call would generate multiple output frames, but waiting
/// for all frames to be generated before beginning to use the frames is not ideal. Because the processor may use the
/// output frames as references for frames still being generated, the output frames are strictly read-only. If you want
/// to modify the frames, you must create a copy first.
///
/// - Parameters:
///   - parameters: A `VTFrameProcessorParameters` based object to specify additional frame based parameters to use
///       during processing. It needs to match the configuration type used during start session.
///   - frameOutputHandler: This frame output handler is called once for each destination frame in the provided parameters
///       if no errors are encountered. The output handler receives the same parameters object that you provided to the
///       original call, a flag indicating if this is the final output to be called for this processing request, and the
///       presentation timestamp associated with the `VTFrameProcessorFrame` that it is being called for. The `NSError`
///       parameter contains an error code if processing was not successful.
- (void) processWithParameters:(id<VTFrameProcessorParameters>)parameters
			frameOutputHandler:(void (^)(id<VTFrameProcessorParameters> , CMTime, BOOL, NSError * _Nullable) )frameOutputHandler NS_REFINED_FOR_SWIFT;

/// Performs effects in a Metal command buffer.
///
/// This function allows you to add the effect to an existing Metal command buffer. The clients that have an existing
/// Metal pipeline and want to add this effect to it can use this function.
///
/// > Note: this function waits until all previously inserted tasks in the command buffer finish before running. Tasks
/// inserted after the `processWithCommandBuffer` returns are run by the system after the effect is applied. Processing
/// does not happen until the commandBuffer is executed.
///
/// - Parameters:
///   - commandBuffer: An existing Metal command buffer where the frame processing is inserted.
///   - parameters: A `VTFrameProcessorParameters` based object to specify additional frame based parameters to use
///       during processing. It needs to match the configuration type used during start session.
- (void) processWithCommandBuffer:(id <MTLCommandBuffer>) commandBuffer
                       parameters:(id<VTFrameProcessorParameters>)parameters;

/// Performs all necessary tasks to end the session.
///
/// After this call completes, you can process no new frames unless you call ``startSessionWithConfiguration`` again.
- (void) endSession;

@end

NS_HEADER_AUDIT_END(nullability, sendability)

#endif // __OBJC__

#endif // VTFRAMEPROCESSOR_H
