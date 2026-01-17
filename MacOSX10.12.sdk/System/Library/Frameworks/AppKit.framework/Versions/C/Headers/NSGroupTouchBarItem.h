/*
 NSGroupTouchBarItem.h
 Application Kit
 Copyright (c) 2015-2016, Apple Inc.
 All rights reserved.
*/

#import <AppKit/NSTouchBarItem.h>

NS_ASSUME_NONNULL_BEGIN

NS_CLASS_AVAILABLE_MAC(10_12_2)
@interface NSGroupTouchBarItem : NSTouchBarItem {
@private
    NSTouchBar *_groupTouchBar;
    NSString *_customizationLabel;
#if !__OBJC2__
    void *_groupTouchBarItemReserved[4] __unused;
#endif /* !__OBJC2__ */
}

/*
    Returns an autoreleased NSGroupTouchBarItem with a groupTouchBar built from the given items array. Customization is not enabled by default when creating a NSGroupTouchBarItem this way.
*/
+ (NSGroupTouchBarItem *)groupItemWithIdentifier:(NSTouchBarItemIdentifier)identifier items:(NSArray<NSTouchBarItem *> *)items;

/*
    A touch bar, presented seamlessly as part of the touch bar this item is hosted in.
    This touch bar may have its own principal item, and can be customized (or not) per the normal touch bar customization rules.
    By default this is an empty touch bar that cannot be customized. This property is archived.
*/
@property (strong) NSTouchBar *groupTouchBar;

/*
    The localized string labelling this item during user customization. The default value is the empty string. This property is archived.
*/
@property (readwrite, copy, null_resettable) NSString *customizationLabel;

@end

NS_ASSUME_NONNULL_END
