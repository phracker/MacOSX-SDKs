/*
    NSSharingServicePickerTouchBarItem.h
    Application Kit
    Copyright (c) 2016-2018, Apple Inc.
    All rights reserved.
*/

#import <AppKit/NSTouchBarItem.h>
#import <AppKit/NSSharingService.h>

@protocol NSSharingServicePickerTouchBarItemDelegate;

NS_ASSUME_NONNULL_BEGIN

@class NSTouchBarSharingServicePickerViewController, NSPopoverTouchBarItem;

NS_CLASS_AVAILABLE_MAC(10_12_2)
@interface NSSharingServicePickerTouchBarItem : NSTouchBarItem {
@private
    __kindof NSPopoverTouchBarItem *_internalPopoverItem APPKIT_IVAR;
    __weak NSTouchBarSharingServicePickerViewController *_pickerViewController APPKIT_IVAR;
    NSString *_customizationLabel APPKIT_IVAR;
    __weak id<NSSharingServicePickerTouchBarItemDelegate> _delegate APPKIT_IVAR;

#if !__OBJC2__
    void *_sharingServicePickerTouchBarItemReserved[4] __unused APPKIT_IVAR;
#endif
}

@property (weak) id<NSSharingServicePickerTouchBarItemDelegate> delegate;

/* Enables or disabled the sharing button; if the popover is shown, it will first be closed.
 */
@property (getter=isEnabled) BOOL enabled;

/* Get/set the button title and image. By default, the button title is an empty string, and the button image is a share picker image. */
@property (copy) NSString *buttonTitle;
@property (nullable, retain) NSImage *buttonImage;

@end

@protocol NSSharingServicePickerTouchBarItemDelegate <NSSharingServicePickerDelegate>
@required
/* Return the items that represent the objects to be shared. They must conform to the <NSPasteboardWriting> protocol or be an NSItemProvider. (e.g. NSString, NSImage, NSURL, etc.). */
- (NSArray *)itemsForSharingServicePickerTouchBarItem:(NSSharingServicePickerTouchBarItem *)pickerTouchBarItem;

@end

NS_ASSUME_NONNULL_END
