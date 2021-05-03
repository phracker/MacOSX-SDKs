//
//  CPListItem.h
//  CarPlay
//
//  Copyright © 2018 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import <CarPlay/CPListItemTypes.h>

NS_ASSUME_NONNULL_BEGIN

@class CPListSection;

/**
 @c CPListItem describes a single object appearing in a list template.
 Each @c CPListItem is displayed as a single cell in the list.
 */
API_AVAILABLE(ios(12.0)) API_UNAVAILABLE(macos, watchos, tvos)
@interface CPListItem : NSObject <CPSelectableListItem>

API_AVAILABLE(ios(14.0)) API_UNAVAILABLE(macos, watchos, tvos)
typedef NS_ENUM(NSInteger, CPListItemAccessoryType) {
    CPListItemAccessoryTypeNone = 0,             // The list item will render without a trailing accessory, or using your custom image.
    CPListItemAccessoryTypeDisclosureIndicator,  // The list item will display a disclosure indicator on its trailing side.
    CPListItemAccessoryTypeCloud                 // The list item will display a cloud image on its trailing side, perhaps indicating remotely-available content.
};

API_AVAILABLE(ios(14.0)) API_UNAVAILABLE(macos, watchos, tvos)
typedef NS_ENUM(NSInteger, CPListItemPlayingIndicatorLocation) {
    CPListItemPlayingIndicatorLocationLeading = 0, // The list item will display its now playing indicator on the leading side.
    CPListItemPlayingIndicatorLocationTrailing,    // The list item will display its now playing indicator on the trailing side.
};

/**
 Initialize a list item with text, detailtext, an image, an accessory type, and an accessory image.

 @note The maximum size of the image is given by +[CPListItem maximumImageSize].
 
 When providing an image, your app should provide a @c UIImage that is display-ready. If necessary for the image, provide
 light and dark styles by using an asset from your asset catalog, prepared with light and dark styles
 or by using @c UIImageAsset to combine two @c UIImage instances into a single image with
 both styles.

 UIImageAsset is used to combine multiple UIImages with different trait collections into a single UIImage.
 
 If you specify an @c accessoryImage, your @c accessoryType will be set to @c CPListItemAccessoryTypeNone.
 
 @discussion To properly size your list images, your app should consider the display scale of the car screen.
 See -[CPInterfaceController carTraitCollection].
 */
- (instancetype)initWithText:(nullable NSString *)text
                  detailText:(nullable NSString *)detailText
                       image:(nullable UIImage *)image
              accessoryImage:(nullable UIImage *)accessoryImage
               accessoryType:(CPListItemAccessoryType)accessoryType API_AVAILABLE(ios(14.0));

/**
 Initialize a list item with text, detail text, and an image.
 
 Your app should provide a @c UIImage that is display-ready, containing
 two @c UIImageAssets, corresponding to night and day mode.

 @note The maximum size of the image is given by +[CPListItem maximumImageSize].

 When providing an image, your app should provide a @c UIImage that is display-ready. If necessary for the image, provide
 light and dark styles by using an asset from your asset catalog, prepared with light and dark styles
 or by using @c UIImageAsset to combine two @c UIImage instances into a single image with
 both styles.

 UIImageAsset is used to combine multiple UIImages with different trait collections into a single UIImage.
 
 @discussion To properly size your list images, your app should size them to the display scale of the car screen.
 See -[CPInterfaceController carTraitCollection].
 */
- (instancetype)initWithText:(nullable NSString *)text
                  detailText:(nullable NSString *)detailText
                       image:(nullable UIImage *)image;

/**
 Initialize a list item with text and detail text.
 */
- (instancetype)initWithText:(nullable NSString *)text
                  detailText:(nullable NSString *)detailText;

/**
 An accessory image type to display in the trailing portion of this list item.
 
 @note If you specify a custom accessoryImage, it will take priority over one of the
 built-in accessory types specified here.
 */
@property (nonatomic, assign) CPListItemAccessoryType accessoryType API_AVAILABLE(ios(14.0));

/**
 If YES, a cell displaying this list item will render with an explicit indicator to the trailing edge of the text
 
 Defaults to NO.
 */
@property (nonatomic, assign, getter=isExplicitContent) BOOL explicitContent API_AVAILABLE(ios(14.0));

/**
 Set a fractional value between 0 and 1 to display a progress bar on this list item.
 */
@property (nonatomic, assign) CGFloat playbackProgress API_AVAILABLE(ios(14.0));

/**
 Indicate that this list item represents content that is currently playing. This list item
 will render with an icon indicating that this item is playing.
 */
@property (nonatomic, assign, getter=isPlaying) BOOL playing API_AVAILABLE(ios(14.0));

/**
 Specify the location in the list item for the now playing indicator.
 
 Defaults to CPListItemPlayingIndicatorLocationLeading.
 */
@property (nonatomic, assign) CPListItemPlayingIndicatorLocation playingIndicatorLocation API_AVAILABLE(ios(14.0));

/**
 The expected image size for your @c CPListItem.
 
 To properly size your list images, your app should size them to the display scale of the car screen.
 See -[CPInterfaceController carTraitCollection].
 */
@property (nonatomic, class, readonly) CGSize maximumImageSize API_AVAILABLE(ios(14.0));

#pragma mark - Dynamic List Item Updates

/**
 Update the detail text in this list item, reloading this item in the table if needed.
 */
- (void)setDetailText:(nullable NSString *)detailText API_AVAILABLE(ios(14.0));

/**
 Update the image in this list item, reloading this item in the table if needed.
 
 When providing an image, your app should provide a @c UIImage that is display-ready. If necessary for the image, provide
 light and dark styles by using an asset from your asset catalog, prepared with light and dark styles
 or by using @c UIImageAsset to combine two @c UIImage instances into a single image with
 both styles.

 UIImageAsset is used to combine multiple UIImages with different trait collections into a single UIImage.
 */
- (void)setImage:(nullable UIImage *)image API_AVAILABLE(ios(14.0));

/**
 Update the accessory image in this list item, reloading this item in the table if needed.
 
 When providing an image, your app should provide a @c UIImage that is display-ready. If necessary for the image, provide
 light and dark styles by using an asset from your asset catalog, prepared with light and dark styles
 or by using @c UIImageAsset to combine two @c UIImage instances into a single image with
 both styles.

 UIImageAsset is used to combine multiple UIImages with different trait collections into a single UIImage.
 */
- (void)setAccessoryImage:(nullable UIImage *)accessoryImage API_AVAILABLE(ios(14.0));

/**
 Assign a new text label to this list item, automatically reloading this item in its list template.
 */
- (void)setText:(NSString *)text API_AVAILABLE(ios(14.0));

/**
 An optional action block, fired when the user selects this item in a list template.
 */
@property (nullable, nonatomic, copy) void (^handler) (id <CPSelectableListItem> item,
                                                       dispatch_block_t completionBlock) API_AVAILABLE(ios(14.0));

/**
 The primary text shown in a cell displaying this list item.
 */
@property (nullable, nonatomic, copy, readonly) NSString *text;

/**
 Any custom user info related to this item.
 */
@property (nullable, nonatomic, strong) id userInfo;

/**
 Any extra text displayed below the primary text in a cell displaying this list item.
 */
@property (nullable, nonatomic, copy, readonly) NSString *detailText;

/**
 An image displayed on the leading side of a cell displaying this list item.
 
 When providing an image, your app should provide a @c UIImage that is display-ready. If necessary for the image, provide
 light and dark styles by using an asset from your asset catalog, prepared with light and dark styles
 or by using @c UIImageAsset to combine two @c UIImage instances into a single image with
 both styles.

 UIImageAsset is used to combine multiple UIImages with different trait collections into a single UIImage.

 @discussion Animated images are not supported. If an animated image is assigned, only the first image will be used.
 To properly size your list images, your app should size them to the display scale of the car screen.
 See -[CPInterfaceController carTraitCollection].
 */
@property (nullable, nonatomic, strong, readonly) UIImage *image;

/**
 An image displayed on the trailing side of a cell displaying this list item.
 
 When providing an image, your app should provide a @c UIImage that is display-ready. If necessary for the image, provide
 light and dark styles by using an asset from your asset catalog, prepared with light and dark styles
 or by using @c UIImageAsset to combine two @c UIImage instances into a single image with
 both styles.

 UIImageAsset is used to combine multiple UIImages with different trait collections into a single UIImage.
 
 @discussion Animated images are not supported. If an animated image is assigned, only the first image will be used.
 
 @note If set, this property takes precedence over the @c accessoryType.
 */
@property (nullable, nonatomic, strong, readonly) UIImage *accessoryImage;

#pragma mark - Deprecated

/**
 If YES, a cell displaying this list item will render with a disclosure indicator
 in the trailing side of the cell.
 
 @note If set, this property takes precedence over showsCloudLabel.

 Defaults to NO.
 */
@property (nonatomic, readonly, assign) BOOL showsDisclosureIndicator API_DEPRECATED_WITH_REPLACEMENT("CPListItemAccessoryType", ios(12.0, 14.0));


/**
 If YES, a cell displaying this list item will render with an explicit label to the trailing edge of the text
 
 Defaults to NO.
 */
@property (nonatomic, assign) BOOL showsExplicitLabel API_DEPRECATED_WITH_REPLACEMENT("-explicitContent", ios(14.0, 14.0));

@end

@interface CPListItem (Deprecated)

/**
 Initialize a list item with text, detailtext, an image, and a disclosure indicator.

 @note The maximum size of the image is given by +[CPListItem maximumImageSize].
 
 @discussion To properly size your list images, your app should size them to the display scale of the car screen.
 See -[CPInterfaceController carTraitCollection].
 */
- (instancetype)initWithText:(nullable NSString *)text
                  detailText:(nullable NSString *)detailText
                       image:(nullable UIImage *)image
    showsDisclosureIndicator:(BOOL)showsDisclosureIndicator API_DEPRECATED_WITH_REPLACEMENT("initWithText:detailText:image:accessoryImage:accessoryType:", ios(12.0, 14.0));

@end

NS_ASSUME_NONNULL_END
