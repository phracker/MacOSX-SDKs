//
//  CPListImageRowItem.h
//  CarPlay
//
//  Copyright © 2019 Apple Inc. All rights reserved.
//

#import <CarPlay/CPImageSet.h>
#import <CarPlay/CPListSection.h>
#import <CarPlay/CPListItemTypes.h>

/**
 * The maximum number of images allowed in a @c CPListImageRowItem.
 * The system may display fewer than this number of images, depending on the available width of the car screen.
 */
extern NSUInteger const CPMaximumNumberOfGridImages;

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(14.0)) API_UNAVAILABLE(macos, watchos, tvos)
@interface CPListImageRowItem : NSObject <CPSelectableListItem>

/**
 Initialize a list image row item with a text string and an array of @c UIImage
 for the grid of images.
  
 When providing an image, your app should provide a @c UIImage that is display-ready. If necessary for the image, provide
 light and dark styles by using an asset from your asset catalog, prepared with light and dark styles
 or by using @c UIImageAsset to combine two @c UIImage instances into a single image with
 both styles.

 UIImageAsset is used to combine multiple UIImages with different trait collections into a single UIImage.
 
 @note The expected image size is given by +[CPListImageRowItem maximumImageSize]. Images provided
 will be resized to this size if necessary.
 
 @discussion To properly size your images, your app should size them to the display scale of the car screen.
 See -[CPInterfaceController carTraitCollection].
 */
- (instancetype)initWithText:(NSString *)text images:(NSArray<UIImage *> *)images;

/**
 The primary text shown in a cell displaying this list item.
 */
@property (nonatomic, copy, nullable) NSString *text;

/**
 Any custom user info related to this item.
 */
@property (nullable, nonatomic, strong) id userInfo;

/**
 An optional action block, fired when the user selects this item in a list template.
 */
@property (nullable, nonatomic, copy) void (^handler) (id <CPSelectableListItem> item,
                                                       dispatch_block_t completionBlock) API_AVAILABLE(ios(14.0));

/**
 A Boolean value indicating whether the list item is enabled.

 @discussion Set the value of this property to @c YES to enable the list item or @c NO to disable it. The default value of this property is @c YES.
 */
@property (nonatomic, assign, getter=isEnabled) BOOL enabled API_AVAILABLE(ios(15.0));

/**
 Read-only access to the grid images shown in a row in the cell.
 
 @note The maximum number of images shown is @c CPMaximumNumberOfGridImages.
 If you supply more images, only the first @c CPMaximumNumberOfGridImages will be used.
 */
@property (nonatomic, strong, readonly) NSArray<UIImage *> *gridImages;

/**
 Update the images displayed in this image row item. If this image row
 item is already displayed in a list template, this image row item will be
 automatically reloaded.
 
 When providing an image, your app should provide a @c UIImage that is display-ready. If necessary for the image, provide
 light and dark styles by using an asset from your asset catalog, prepared with light and dark styles
 or by using @c UIImageAsset to combine two @c UIImage instances into a single image with
 both styles.

 UIImageAsset is used to combine multiple UIImages with different trait collections into a single UIImage.
 
 @see To update/reload the title of the image row item, assign to
 the @c text property of the image row item.
 */
- (void)updateImages:(NSArray <UIImage *> *)gridImages;

/**
 A block that is called when the user selects one of the images in this image row item.
 
 The user may also select the cell itself - for that event, specify a @c handler.
 */
@property (nullable, nonatomic, copy) void (^listImageRowHandler) (CPListImageRowItem *item,          // The image row item that the user selected.
                                                                   NSInteger index,                   // The index of the image in the image row item that the user selected.
                                                                   dispatch_block_t completionBlock); // A completion block you must call after processing the user's selection.


/**
 The expected image size for the grid images in your @c CPListImageRowItem. Images provided
 will be resized to this size.
 
 @discussion To properly size your images, your app should size them to the display scale of the car screen.
 See -[CPInterfaceController carTraitCollection].
 */
@property (nonatomic, class, readonly) CGSize maximumImageSize;

@end

NS_ASSUME_NONNULL_END
