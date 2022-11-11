//
//  INRelevantShortcut.h
//  Intents
//
//  Copyright (c) 2016-2020 Apple Inc. All rights reserved.
//

#import <Intents/INRelevanceProvider.h>
#import <Intents/INDefaultCardTemplate.h>
#import <Intents/INShortcut.h>

@class INShortcut;

NS_ASSUME_NONNULL_BEGIN

/*!
 @abstract The role of the relevant shortcut.
 @discussion Provides a hint to Siri about the expected user experience.
 */
typedef NS_ENUM(NSInteger, INRelevantShortcutRole) {
    
    /*!
     @abstract The relevant shortcut represents an action that the user may want to perform using your app.
     */
    INRelevantShortcutRoleAction,
    
    /*!
     @abstract The relevant shortcut represents information that the user may want to glance at.
     */
    INRelevantShortcutRoleInformation,
} API_AVAILABLE(ios(12.0), watchos(5.0)) API_UNAVAILABLE(macos, tvos);

/*!
 @abstract Lets you provide relevant shortcut to Siri, for display on the Siri Watch Face.
 @discussion Including relevance information allows Siri to make suggestions for shortcuts that the user might be interested in but has not previously performed.
 */
API_AVAILABLE(ios(12.0), watchos(5.0)) API_UNAVAILABLE(macos, tvos)
@interface INRelevantShortcut : NSObject <NSSecureCoding, NSCopying>

/*!
 @abstract A collection of relevance information that is attached to the relevant shortcuts.
 @discussion Providing additional relevance information allows Siri to suggest a shortcut that the user is interested in but has not previously performed.
 @seealso INRelevanceProvider
 */
@property (copy, NS_NONATOMIC_IOSONLY) NSArray<INRelevanceProvider *> *relevanceProviders;

/*!
 @abstract Customizes the display of the relevant shortcut on the Siri watch face.
 @discussion By default, the UI for the relevant shortcut can be derivied from the information provided in the @c INShortcut. In certain situations, it may be desirable to override this behavior and provide a custom template.
 @seealso INDefaultCardTemplate
 */
@property (copy, nullable, NS_NONATOMIC_IOSONLY) INDefaultCardTemplate *watchTemplate;

/*!
 @abstract Links the relevant shortcut to a specific WidgetKit widget kind.
 @discussion When a relevant shortcut is linked to a WidgetKit widget, it hints to the system when to show the widget in a stack.
 */
@property (copy, nullable, NS_NONATOMIC_IOSONLY) NSString *widgetKind API_AVAILABLE(ios(15.0), watchos(8.0));

/*!
 @abstract The role of the relevant shortcut.
 @discussion Provides a hint to Siri about the expected user experience. The default is @c INRelevantShortcutRoleAction.
 @seealso INRelevantShortcutRole
 */
@property (NS_NONATOMIC_IOSONLY) INRelevantShortcutRole shortcutRole;

/*!
 @abstract The shortcut that will be performed when this relevant shortcut is invoked.
 @seealso INShortcut
 */
@property (readonly, copy, NS_NONATOMIC_IOSONLY) INShortcut *shortcut;

/*!
 @abstract Creates a relevant shortcut for the given shortcut.
 */
- (instancetype)initWithShortcut:(INShortcut *)shortcut NS_DESIGNATED_INITIALIZER;

@end

NS_ASSUME_NONNULL_END
