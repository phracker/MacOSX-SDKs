//
//  MTLCaptureManager.h
//  Metal
//
//  Copyright © 2017 Apple, Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <Metal/MTLDefines.h>


NS_ASSUME_NONNULL_BEGIN

@protocol MTLCaptureScope;
@protocol MTLCommandQueue;
@protocol MTLDevice;

MTL_EXPORT API_AVAILABLE(macos(10.13), ios(11.0))
@interface MTLCaptureManager : NSObject
{
    BOOL _isCapturing;
    id<MTLCaptureScope> _defaultCaptureScope;
}

/** Retrieves the shared capture manager for this process. There is only one capture manager per process.
    The capture manager allows the user to create capture scopes and trigger captures from code.
    When a capture has been completed, it will be displayed in Xcode and the application will be paused.
    @remarks: only MTLCommandBuffers created after starting a capture and committed before stopping it are captured. 
 */
+ (MTLCaptureManager*)sharedCaptureManager;

// Use +[sharedCaptureManager]
- (instancetype)init API_UNAVAILABLE(macos, ios);

// Creates a new capture scope for the given capture device
- (id<MTLCaptureScope>)newCaptureScopeWithDevice:(id<MTLDevice>)device;
// Creates a new capture scope for the given command queue
- (id<MTLCaptureScope>)newCaptureScopeWithCommandQueue:(id<MTLCommandQueue>)commandQueue;

// Starts capturing, for all queues of the given device, new MTLCommandBuffer's until -[stopCapture] or Xcode’s stop capture button is pressed
- (void)startCaptureWithDevice:(id<MTLDevice>)device;
// Starts capturing, for the given command queue, command buffers that are created after invoking this method and committed before invoking -[stopCapture] or clicking Xcode’s stop capture button.
- (void)startCaptureWithCommandQueue:(id<MTLCommandQueue>)commandQueue;
// Start a capture with the given scope: from the scope's begin until its end, restricting the capture to the scope's device(s) and, if selected, the scope's command queue
- (void)startCaptureWithScope:(id<MTLCaptureScope>)captureScope;

// Stops a capture started from startCaptureWithDevice:/startCaptureWithCommandQueue:/startCaptureWithScope: or from Xcode’s capture button
- (void)stopCapture;

// Default scope to be captured when a capture is initiated from Xcode’s capture button. When nil, it’ll fall back to presentDrawable:, presentDrawable:atTime:, presentDrawable:afterMinimumDuration: in MTLCommandBuffer or present:, present:atTime:, present:afterMinimumDuration: in MTLDrawable.
@property (nullable, readwrite, strong, atomic) id<MTLCaptureScope> defaultCaptureScope;

// Query if a capture is currently in progress
@property (readonly) BOOL isCapturing;

@end

NS_ASSUME_NONNULL_END

