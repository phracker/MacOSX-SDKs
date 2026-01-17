//
//  PHContentEditingController.h
//  PhotosUI
//
//  Copyright (c) 2014 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

#import <UIKit/UIImage.h>

NS_ASSUME_NONNULL_BEGIN
API_AVAILABLE_BEGIN(macos(10.11), ios(8)) API_UNAVAILABLE_BEGIN(macCatalyst)

@class PHAdjustmentData, PHContentEditingInput, PHContentEditingOutput;

// Protocol to which the principal view controller of the extension must conform.
@protocol PHContentEditingController <NSObject>
@required

// Query whether the receiver can handle (i.e. can decode and render) the given adjustment data.
- (BOOL)canHandleAdjustmentData:(PHAdjustmentData *)adjustmentData;

// Provides the input for the editing session. The placeholder image represents the current version of the asset (with adjustments baked in), and can be used as UI placeholder, in case rendering the adjustments from the input cannot be done in a timely fashion.
- (void)startContentEditingWithInput:(PHContentEditingInput *)contentEditingInput placeholderImage:(UIImage *)placeholderImage;

// Called when the user finishes the editing session. The receiver should prevent the user from editing the asset further. Also, it should create the editing output and call the completion handler. The completion handler returns after the output has been consumed, so it is safe to perform clean up after it returns. The completion handler can (and should best) be called on a background queue.
- (void)finishContentEditingWithCompletionHandler:(void (^)(PHContentEditingOutput * _Nullable))completionHandler;

// Called if the user cancels the editing session. (Can be called while the receiver is producing the editing output.)
- (void)cancelContentEditing;

// Returns whether the user should be prompted when canceling the editing session.
@property (readonly, nonatomic) BOOL shouldShowCancelConfirmation;

@end

API_AVAILABLE_END API_UNAVAILABLE_END
NS_ASSUME_NONNULL_END
