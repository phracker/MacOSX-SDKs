/*
 NSGroupTouchBarItem.h
 Application Kit
 Copyright (c) 2015-2018, Apple Inc.
 All rights reserved.
*/

#import <AppKit/NSTouchBarItem.h>
#import <AppKit/NSUserInterfaceLayout.h>
#import <AppKit/NSUserInterfaceCompression.h>

NS_ASSUME_NONNULL_BEGIN

NS_CLASS_AVAILABLE_MAC(10_12_2)
@interface NSGroupTouchBarItem : NSTouchBarItem {
@private
    NSTouchBar *_groupTouchBar APPKIT_IVAR;
    NSString *_customizationLabel APPKIT_IVAR;
    NSUserInterfaceLayoutDirection _groupUserInterfaceLayoutDirection APPKIT_IVAR;
    struct __gtbiFlags {
        unsigned int hasAutomaticLayoutDirection:1;
        unsigned int reserved:31;
    } _gtbiFlags APPKIT_IVAR;
    id _private APPKIT_IVAR;
#if !__OBJC2__
    void *_groupTouchBarItemReserved[1] __unused APPKIT_IVAR;
#endif /* !__OBJC2__ */
}

/*
    Returns an autoreleased NSGroupTouchBarItem whose groupTouchBar is built from the given items array.
    Customization is not enabled by default when creating an NSGroupTouchBarItem this way.
*/
+ (instancetype)groupItemWithIdentifier:(NSTouchBarItemIdentifier)identifier items:(NSArray<NSTouchBarItem *> *)items;

/*
    Creates a NSGroupTouchBarItem with the allowed compression options provided in the order AppKit defines.
    Default order: BreakEqualWidths, ReduceMetrics, HideText, HideImages.
    This should only be used with standard options provided by AppKit. Custom options need to be added using the prioritizedCompressionOptions property.
 */
+ (instancetype)groupItemWithIdentifier:(NSTouchBarItemIdentifier)identifier items:(NSArray<NSTouchBarItem *> *)items allowedCompressionOptions:(NSUserInterfaceCompressionOptions *)allowedCompressionOptions NS_AVAILABLE_MAC(10_13);

/*
    Creates a NSGroupTouchBarItem with the appropriate settings to match system style alerts in NSTouchBar.
    Spacing between items is under control of the client, but in general NSTouchBarItemIdentifierFixedSpaceLarge is recommended anywhere additional spacing is required.
    The groupUserInterfaceLayoutDirection will be set to [NSApp userInterfaceLayoutDirection].
 */
+ (instancetype)alertStyleGroupItemWithIdentifier:(NSTouchBarItemIdentifier)identifier NS_AVAILABLE_MAC(10_13);

/*
    An NSTouchBar, presented seamlessly as part of the NSTouchBar this item is hosted in.
    The NSTouchBar may have its own principal item, and can be customized (or not) per the normal customization rules.
    By default this is an empty bar that cannot be customized. This property is archived.
*/
@property (strong) NSTouchBar *groupTouchBar;

/*
    The localized string labelling this item during user customization. The default value is the empty string. This property is archived.
*/
@property (readwrite, copy, null_resettable) NSString *customizationLabel;

/*
    Get and set the user interface layout direction of the groupTouchBar, which defines the order in which the items should be laid out.
    By default, this value is NSUserInterfaceLayoutDirectionLeftToRight.
    To flip the layout direction of the group to the user’s preferred layout, this should be set to [NSApp userInterfaceLayoutDirection].
 */
@property NSUserInterfaceLayoutDirection groupUserInterfaceLayoutDirection NS_AVAILABLE_MAC(10_13);

/*
    When set, items in the associated groupTouchBar will be sized to have equal widths when possible.
    Defaults to NO.
 */
@property BOOL prefersEqualWidths NS_AVAILABLE_MAC(10_13);

/*
    The preferred width for items in the group when prefersEqualWidths is YES. This is the width that items will be set to if they fit, and the item doesn't clip.
    Optional; ignored if <0. Defaults to -1.
 */
@property CGFloat preferredItemWidth NS_AVAILABLE_MAC(10_13);

/*
    The currently active NSUserInterfaceCompressionOptions on the group.
 */
@property (readonly) NSUserInterfaceCompressionOptions *effectiveCompressionOptions NS_AVAILABLE_MAC(10_13);

/*
    The allowed compression options in the order they will be exercised.
    Client defined options should be added to specify the order in which they will be exercised.
    Options not included will be ignored.
    Defaults to an array containing all standard AppKit options in the order AppKit defines.
 */
@property (copy) NSArray<NSUserInterfaceCompressionOptions *> *prioritizedCompressionOptions NS_AVAILABLE_MAC(10_13);

@end

NS_ASSUME_NONNULL_END
