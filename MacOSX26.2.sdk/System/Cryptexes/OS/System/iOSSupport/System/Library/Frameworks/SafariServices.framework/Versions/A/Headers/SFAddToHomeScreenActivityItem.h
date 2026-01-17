// Copyright © 2023 Apple Inc. All rights reserved.

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@class BEWebAppManifest;

/*! 
 @protocol SFAddToHomeScreenActivityItem
 An activity item for adding "Add to Home Screen" activity type into activity view (share sheet) list.
 */
API_AVAILABLE(ios(17.4))
@protocol SFAddToHomeScreenActivityItem <NSObject>

/*! @abstract The URL for the home screen bookmark item.
 The URL scheme should be HTTP or HTTPS.
 This URL will be shown to user in the confirmation sheet.
 */
@property (nonatomic, readonly) NSURL *URL;

/*! @abstract The title for the home screen bookmark item.
 This title will be shown to user in the confirmation sheet.
 */
@property (nonatomic, readonly) NSString *title;

/*! @abstract An optional item provider for providing website icons.
 This provider should register and provide an item with the UIImage type.
 A default icon for the website will be shown to user if an icon is not provided.
 */
@optional
@property (nonatomic, nullable, readonly) NSItemProvider *iconItemProvider;

/*! @abstract An optional method to provide the web app manifest.
 This is only available to apps that can use BrowserEngineKit.
*/
- (void)getWebAppManifestWithCompletionHandler:(void (^)(BEWebAppManifest *_Nullable))completionHandler API_DEPRECATED("Create a SFAddToHomeScreenInfo instead", ios(17.5, API_TO_BE_DEPRECATED));


@end

NS_ASSUME_NONNULL_END 
