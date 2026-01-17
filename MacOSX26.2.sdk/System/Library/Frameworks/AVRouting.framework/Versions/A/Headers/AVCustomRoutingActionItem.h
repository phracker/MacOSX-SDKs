/*
    File:  AVCustomRoutingActionItem.h
    
    Framework:  AVRouting
    
    Copyright © 2022 Apple Inc. All rights reserved.
    
 */

#import <Foundation/Foundation.h>

@class UTType;

NS_ASSUME_NONNULL_BEGIN

/*!
    @class      AVCustomRoutingActionItem
    @abstract   AVCustomRoutingActionItem objects can be created by 3rd parties to inject custom action items into the route picker.
    @discussion An item can be any action the app wants to provide as menu items besides the discovered routes.
    Tapping on the custom items dismisses the picker and invokes a callback to the app telling it which item was tapped. (See -[AVCustomRoutingController customRoutingController:didSelectItem:])
 */

/// An object that represents a custom action item to display in a device route
/// picker.
///
/// Use this class to specify supplemental action items to display in the list
/// of discovered routes. Tapping a custom item dismisses the picker and calls
/// the
/// ``AVCustomRoutingControllerDelegate/customRoutingController:didSelectItem:``
/// method of ``AVCustomRoutingControllerDelegate``.
API_AVAILABLE(ios(16.0)) API_UNAVAILABLE(macos) API_UNAVAILABLE(tvos, watchos)
NS_SWIFT_NONSENDABLE @interface AVCustomRoutingActionItem : NSObject

/*!
    @property   type
    @abstract   A UTType with an identifier which matches a UTType in the info.plist.
    @discussion Provide a UTTypeSymbolName and description in the info.plist.
 */

/// A type with an identifier that matches a value in the app’s configuration.
///
/// Provide a `UTType` symbol name and description in your app’s `Info.plist`
/// file.
@property (nonatomic, copy) UTType *type API_AVAILABLE(ios(16.0)) API_UNAVAILABLE(macos) API_UNAVAILABLE(tvos, watchos);

/*!
    @property   overrideTitle
    @abstract   A title which overrides the title of the UTType.
    @discussion Use this to dynamically override the title of the custom item.
 */

/// A string to use to override the title of the item’s type.
///
/// Use this value to dynamically override the title of the custom item.
@property (nonatomic, copy, nullable) NSString *overrideTitle API_AVAILABLE(ios(16.0)) API_UNAVAILABLE(macos) API_UNAVAILABLE(tvos, watchos);

@end

NS_ASSUME_NONNULL_END
