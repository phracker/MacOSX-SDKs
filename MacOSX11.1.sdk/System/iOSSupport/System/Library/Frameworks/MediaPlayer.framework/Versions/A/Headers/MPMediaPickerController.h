//
//  MPMediaPickerController.h
//  MediaPlayer
//
//  Copyright 2008 Apple, Inc. All rights reserved.
//

#import <MediaPlayer/MediaPlayerDefines.h>

#if MP_HAS_UIKIT

#import <UIKit/UIKit.h>
#import <MediaPlayer/MPMediaItem.h>
#import <MediaPlayer/MPMediaItemCollection.h>

NS_ASSUME_NONNULL_BEGIN

@protocol MPMediaPickerControllerDelegate;

// MPMediaPickerController is a UIViewController for visually selecting media items.
// To display it, present it modally on an existing view controller.
MP_API(ios(3.0))
API_UNAVAILABLE(watchos)
MP_UNAVAILABLE(tvos, macos)
@interface MPMediaPickerController : UIViewController

- (instancetype)initWithMediaTypes:(MPMediaType)mediaTypes NS_DESIGNATED_INITIALIZER;
@property (nonatomic, readonly) MPMediaType mediaTypes;

@property (nonatomic, weak, nullable) id<MPMediaPickerControllerDelegate> delegate;

@property (nonatomic) BOOL allowsPickingMultipleItems; // default is NO

@property (nonatomic) BOOL showsCloudItems MP_API(ios(6.0)); // default is YES

@property (nonatomic) BOOL showsItemsWithProtectedAssets MP_API(ios(9.2)); // default is YES

@property (nonatomic, copy, nullable) NSString *prompt; // displays a prompt for the user above the navigation bar buttons

@end

MP_UNAVAILABLE(tvos, macos)
API_UNAVAILABLE(watchos)
@protocol MPMediaPickerControllerDelegate<NSObject>
@optional

// It is the delegate's responsibility to dismiss the modal view controller on the parent view controller.

- (void)mediaPicker:(MPMediaPickerController *)mediaPicker didPickMediaItems:(MPMediaItemCollection *)mediaItemCollection;
- (void)mediaPickerDidCancel:(MPMediaPickerController *)mediaPicker;

@end

NS_ASSUME_NONNULL_END

#endif
