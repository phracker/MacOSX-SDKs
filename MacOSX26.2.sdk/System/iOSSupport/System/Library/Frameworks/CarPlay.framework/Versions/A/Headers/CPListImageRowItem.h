//
//  CPListImageRowItem.h
//  CarPlay
//
//  Copyright © 2019 Apple Inc. All rights reserved.
//

#import <CarPlay/CPImageSet.h>
#import <CarPlay/CPListImageRowItemElement.h>
#import <CarPlay/CPListImageRowItemCardElement.h>
#import <CarPlay/CPListImageRowItemCondensedElement.h>
#import <CarPlay/CPListImageRowItemGridElement.h>
#import <CarPlay/CPListImageRowItemImageGridElement.h>
#import <CarPlay/CPListImageRowItemRowElement.h>
#import <CarPlay/CPListItemTypes.h>
#import <CarPlay/CPListSection.h>
#import <CarPlay/CPTemplate.h>

/**
 * The maximum number of images allowed in a @c CPListImageRowItem.
 * The system may display fewer than this number of images, depending on the available width of the car screen.
 */
extern NSUInteger const CPMaximumNumberOfGridImages;

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(14.0)) API_UNAVAILABLE(tvos) API_UNAVAILABLE(macos, watchos)
CARPLAY_TEMPLATE_UI_ACTOR
@interface CPListImageRowItem : NSObject <CPSelectableListItem>

/**
 Initialize a list image row item with a text string and an array of @c UIImage
 for the grid of images.
  
 When providing an image, your app should provide a @c UIImage that is display-ready. If necessary for the image, provide
 light and dark styles by using an asset from your asset catalog, prepared with light and dark styles
 or by using @c UIImageAsset to combine two @c UIImage instances into a single image with
 both styles.

 UIImageAsset is used to combine multiple UIImages with different trait collections into a single UIImage.
 
 @note The expected image size is given by +[CPListImageRowItem maximumImageSize]. Images provided will be resized to this size if necessary.

 @discussion To properly size your images, your app should size them to the display scale of the car screen.
 See -[CPInterfaceController carTraitCollection].
 */
- (instancetype)initWithText:(NSString *)text 
                      images:(NSArray<UIImage *> *)images API_DEPRECATED("Use initWithText:elements:allowsMultipleLines:", ios(14.0, 26.0));

/**
 Initialize a list image row item with a text string, an array of @c UIImage
 for the grid of images, and an array of @c NSString titles, one displayed below each image.

 The number of titles in the @c imageTitles list should be equal to the number of images in the
 @c images list.

 When providing an image, your app should provide a @c UIImage that is display-ready. If necessary for the image, provide
 light and dark styles by using an asset from your asset catalog, prepared with light and dark styles
 or by using @c UIImageAsset to combine two @c UIImage instances into a single image with
 both styles.

 UIImageAsset is used to combine multiple UIImages with different trait collections into a single UIImage.

 @note The expected image size is given by +[CPListImageRowItem maximumImageSize]. Images provided will be resized to this size if necessary.

 @discussion To properly size your images, your app should size them to the display scale of the car screen.
 See -[CPInterfaceController carTraitCollection].
 */
- (instancetype)initWithText:(NSString *)text
                      images:(NSArray<UIImage *> *)images
                 imageTitles:(NSArray<NSString *> *)imageTitles API_DEPRECATED("Use initWithText:elements:allowsMultipleLines:", ios(17.4, 26.0));

/**
 Initialize a list image row item with a text string, an array of @c CPListImageRowItemRowElement and a boolean to allow multiple lines in this row.

 If a nil @c text property is provided the cell will resize accordingly to hide the title.

 @param text The text visible at the top of the cell.
 @param elements The list of @c CPListImageRowItemRowElement  elements visible below the text.
 @param allowsMultipleLines Determines if the elements could be visible on more than a single line.
 */
- (instancetype)initWithText:(NSString * _Nullable)text
                    elements:(NSArray<CPListImageRowItemRowElement *> *)elements
         allowsMultipleLines:(BOOL)allowsMultipleLines API_AVAILABLE(ios(26.0)) API_UNAVAILABLE(tvos);

/**
 Initialize a list image row item with a text string, an array of @c CPListImageRowItemCardElement and a boolean to allow multiple lines in this row.

 If a nil @c text property is provided the cell will resize accordingly to hide the title.

 @param text The text visible at the top of the cell.
 @param elements The list of @c CPListImageRowItemCardElement  elements visible below the text.
 @param allowsMultipleLines Determines if the elements could be visible on more than a single line.
 */
- (instancetype)initWithText:(NSString * _Nullable)text
                cardElements:(NSArray<CPListImageRowItemCardElement *> *)elements
         allowsMultipleLines:(BOOL)allowsMultipleLines API_AVAILABLE(ios(26.0)) API_UNAVAILABLE(tvos);

/**
 Initialize a list image row item with a text string, an array of @c CPListImageRowItemCondensedElement and a boolean to allow multiple lines in this row.

 If a nil @c text property is provided the cell will resize accordingly to hide the title.

 @param text The text visible at the top of the cell.
 @param elements The list of @c CPListImageRowItemCondensedElement  elements visible below the text.
 @param allowsMultipleLines Determines if the elements could be visible on more than a single line.
 */
- (instancetype)initWithText:(NSString * _Nullable)text
           condensedElements:(NSArray<CPListImageRowItemCondensedElement *> *)elements
         allowsMultipleLines:(BOOL)allowsMultipleLines API_AVAILABLE(ios(26.0)) API_UNAVAILABLE(tvos);

/**
 Initialize a list image row item with a text string, an array of @c CPListImageRowItemGridElement and a boolean to allow multiple lines in this row.

 If a nil @c text property is provided the cell will resize accordingly to hide the title.

 @param text The text visible at the top of the cell.
 @param elements The list of @c CPListImageRowItemGridElement  elements visible below the text.
 @param allowsMultipleLines Determines if the elements could be visible on more than a single line.
 */
- (instancetype)initWithText:(NSString * _Nullable)text
                gridElements:(NSArray<CPListImageRowItemGridElement *> *)elements
         allowsMultipleLines:(BOOL)allowsMultipleLines API_AVAILABLE(ios(26.0)) API_UNAVAILABLE(tvos);

/**
 Initialize a list image row item with a text string, an array of @c CPListImageRowItemImageGridElement and a boolean to allow multiple lines in this row.

 If a nil @c text property is provided the cell will resize accordingly to hide the title.

 @param text The text visible at the top of the cell.
 @param elements The list of @c CPListImageRowItemImageGridElement  elements visible below the text.
 @param allowsMultipleLines Determines if the elements could be visible on more than a single line.
 */
- (instancetype)initWithText:(NSString * _Nullable)text
           imageGridElements:(NSArray<CPListImageRowItemImageGridElement *> *)elements
         allowsMultipleLines:(BOOL)allowsMultipleLines API_AVAILABLE(ios(26.0)) API_UNAVAILABLE(tvos);

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
                                                       dispatch_block_t completionBlock) API_AVAILABLE(ios(14.0)) API_UNAVAILABLE(tvos);

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
@property (nonatomic, strong, readonly) NSArray<UIImage *> *gridImages API_DEPRECATED("No longer supported", ios(14.0, 26.0));

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
 @see To update/reload the title labels displayed below each image, assign to
 the @c imageTitles property of the image row item.
 */
- (void)updateImages:(NSArray <UIImage *> *)gridImages API_DEPRECATED("No longer supported", ios(14.0, 26.0));

/**
 The titles displayed for each image in this image row item.

 @see To update/reload the title of the image row item, assign to
 the @c text property of the image row item.
 */
@property (nonatomic, copy, readonly) NSArray <NSString *> *imageTitles API_DEPRECATED("No longer supported", ios(17.4, 26.0));

/**
 The array of elements used to draw visible elements.
 */
@property (nonatomic, copy) NSArray<CPListImageRowItemElement *> *elements API_AVAILABLE(ios(26.0)) API_UNAVAILABLE(tvos);

/**
 A Boolean value indicating whether the elements should be visible in more than a single line.

 @discussion Set the value of this property to @c YES to allow elements to be visible on multiple lines. Set the value of this property to @c NO to only show a single line of elements.
 */
@property (nonatomic, readonly) BOOL allowsMultipleLines API_AVAILABLE(ios(26.0)) API_UNAVAILABLE(tvos);

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
@property (nonatomic, class, readonly) CGSize maximumImageSize API_DEPRECATED("Use +[CPListImageRowItemElement maximumImageSize] on an appropriate element", ios(14.0, 26.0));

@end

NS_ASSUME_NONNULL_END
