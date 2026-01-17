#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UIDragSession.h>)
//
//  UIDragSession.h
//  UIKit
//
//  Copyright © 2017-2018 Apple Inc. All rights reserved.
//

#import <CoreGraphics/CoreGraphics.h>
#import <Foundation/Foundation.h>
#import <UIKit/UIKitDefines.h>

NS_ASSUME_NONNULL_BEGIN

@class UIDragItem, UIView;

API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(watchos, tvos) @protocol UIDragDropSession <NSObject>

/* A common protocol used for both drag and drop sessions. */

/* The items in the session.
 *
 * Before the drop happens, the items' NSItemProviders do not allow
 * the data in the NSItemProvider to be loaded.
 * However, `registeredTypeIdentifiers` and metadata are available at any time.
 * You may request the data only inside the UIDropInteractionDelegate's implementation
 * of `-dropInteraction:performDrop:`.
 *
 * When handling the drop, if you display dropped items in a linear order,
 * place them in this order, first to last.
 */
@property (nonatomic, readonly) NSArray<UIDragItem *> *items;

/* The location of the drag in the specified view.
 */
- (CGPoint)locationInView:(UIView *)view;

/* Whether this session allows moving, or not.
 *
 * This is determined based on the UIDragInteraction's delegate's
 * `-dragInteraction:sessionAllowsMoveOperation:`.
 *
 * If true, then the delegate of UIDropInteraction is allowed to return `UIDropOperationMove`
 * from `-dropInteraction:sessionDidUpdate:`.
 */
@property (nonatomic, readonly) BOOL allowsMoveOperation;

/* Whether this session is restricted to the application that began the drag.
 *
 * This is determined based on the UIDragInteraction's delegate's
 * `-dragInteraction:sessionIsRestrictedToDraggingApplication:`.
 */
@property (nonatomic, readonly, getter=isRestrictedToDraggingApplication) BOOL restrictedToDraggingApplication;

/* Convenience methods to iterate through this session's `items`.
 *
 * Returns true if any of the session's items conforms to any of the specified UTIs.
 */
- (BOOL)hasItemsConformingToTypeIdentifiers:(NSArray<NSString *> *)typeIdentifiers;

/* Returns true if any of the session's items could create any objects of the specified class.
 */
- (BOOL)canLoadObjectsOfClass:(Class<NSItemProviderReading>)aClass;

@end


API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(watchos, tvos) @protocol UIDragSession <UIDragDropSession>

/* Use `localContext` to attach additional information to this drag session,
 * visible only inside the app that started the drag.
 */
@property (nonatomic, strong, nullable) id localContext;

@end


typedef NS_ENUM(NSUInteger, UIDropSessionProgressIndicatorStyle) {
    UIDropSessionProgressIndicatorStyleNone,       // No indicator is displayed
    UIDropSessionProgressIndicatorStyleDefault,    // A default indicator is displayed
} API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(watchos, tvos);

API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(watchos, tvos) @protocol UIDropSession <UIDragDropSession, NSProgressReporting>

/* The `UIDragSession` that corresponds to this `UIDropSession`.
 * If the drag was started in a different app, this is nil.
 */
@property (nonatomic, readonly, nullable) id<UIDragSession> localDragSession;

/* The kind of progress and cancellation UI that UIKit will display
 * if handling this session's drop takes a significant amount of time.
 *
 * The default value is UIDropSessionProgressIndicatorStyleDefault,
 * meaning that some progress UI will be shown. If you show your own
 * progress indicator, hide the system progress UI by setting this
 * property to UIDropSessionProgressIndicatorStyleNone.
 */
@property (nonatomic) UIDropSessionProgressIndicatorStyle progressIndicatorStyle;

/* A convenience method that can be used only during the UIDropInteractionDelegate's
 * implementation of `-dropInteraction:performDrop:`.
 * Asynchronously instantiates objects of the provided class for each
 * drag item that can do so. The completion handler is called on the
 * main queue, with an array of all objects that were created, in the
 * same order as `items`.
 * The progress returned is an aggregate of the progress for all objects
 * that are loaded.
 */
- (NSProgress *)loadObjectsOfClass:(Class<NSItemProviderReading>)aClass completion:(void(^)(NSArray<__kindof id<NSItemProviderReading>> *objects))completion;

@end

NS_ASSUME_NONNULL_END

#else
#import <UIKitCore/UIDragSession.h>
#endif
