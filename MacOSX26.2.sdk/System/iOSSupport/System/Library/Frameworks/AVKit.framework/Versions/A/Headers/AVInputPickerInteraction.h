/*
	File:  AVInputPickerInteraction.h
	
	Framework:  AVKit
	
	Copyright © 2013-2025 Apple Inc. All rights reserved.
	
 */

#import <AVFoundation/AVFoundation.h>
#import <UIKit/UIKit.h>

@class AVInputPickerInteraction;

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(26.0)) API_UNAVAILABLE(visionos, macCatalyst) API_UNAVAILABLE(macos, tvos, watchos)
/*! The `AVInputPickerInteractionDelegate` protocol defines methods you use to receive notifications about transitions in an `AVInputPickerInteraction` object. */
NS_SWIFT_NAME(AVInputPickerInteraction.Delegate)
@protocol AVInputPickerInteractionDelegate <NSObject>
@optional

/*!
 Tells the delegate that the input picker view is about to present devices.

 - Parameter inputPickerInteraction: The current AVInputPickerInteraction.
 */
- (void)inputPickerInteractionWillBeginPresenting:(AVInputPickerInteraction *_Nonnull)inputPickerInteraction;

/*!
 Tells the delegate that the input picker view has finished presenting devices

 The `isPresented` property is set to `YES` at this point, indicating that the presentation is complete.

 - Parameter inputPickerInteraction: The current AVInputPickerInteraction.
 */
- (void)inputPickerInteractionDidEndPresenting:(AVInputPickerInteraction *_Nonnull)inputPickerInteraction;

/*!
 Tells the delegate that the input picker view is about to dismiss devices.

 - Parameter inputPickerInteraction: The current AVInputPickerInteraction.
 */
- (void)inputPickerInteractionWillBeginDismissing:(AVInputPickerInteraction *_Nonnull)inputPickerInteraction;

/*!
 Tells the delegate that the input picker view has finished dismissing devices.

 The `isPresented` property is set to `NO` at this point, indicating that the dismissal is complete.

 - Parameter inputPickerInteraction: The current AVInputPickerInteraction.
 */
- (void)inputPickerInteractionDidEndDismissing:(AVInputPickerInteraction *_Nonnull)inputPickerInteraction;

@end

API_AVAILABLE(ios(26.0)) API_UNAVAILABLE(visionos, macCatalyst) API_UNAVAILABLE(macos, tvos, watchos)
/*! Use `AVInputPickerInteraction` to present an input picker. */
@interface AVInputPickerInteraction : NSObject <UIInteraction>

/*! The input picker view's delegate. */
@property (nonatomic, nullable, weak) id<AVInputPickerInteractionDelegate> delegate;

/*! A Boolean value that indicates whether the picker is currently visible. */
@property (nonatomic, readonly, getter=isPresented) BOOL presented;

/*! The audio session for the picker. */
@property (nonatomic, nonnull, strong) AVAudioSession *audioSession;

/*! Presents the input picker. */
- (void)present;

/*! Dismisses the input picker. */
- (void)dismiss;

/*! Creates a new instance of AVInputPickerController using a default sharedInstance from `AVAudioSession`. */
- (instancetype)init;

/*!
 Creates a new instance of AVInputPickerInteraction using a specific `AVAudioSession`.
  
 Use this initializer when the provided `AVAudioSession` is in .record
 mode or you plan to switch it to record mode.
  
 If nil session is passed in object will use a sharedInstance from `AVAudioSession`.
  
	- Parameter audioSession: An optional recording configured audio session. If you provide a non-recording session, the input list will be empty.
 */
- (instancetype)initWithAudioSession:(AVAudioSession *_Nullable)audioSession;

@end

NS_ASSUME_NONNULL_END
