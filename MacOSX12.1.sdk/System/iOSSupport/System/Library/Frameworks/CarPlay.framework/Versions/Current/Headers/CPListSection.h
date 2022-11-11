//
//  CPListSection.h
//  CarPlay
//
//  Copyright © 2018 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CarPlay/CPListItemTypes.h>
#import <CarPlay/CPButton.h>

NS_ASSUME_NONNULL_BEGIN

/**
 The expected maximum size of an image size for your @c CPListSection.
 
 To properly size your images, your app should size them to the display scale of the car screen.
 See -[CPInterfaceController carTraitCollection].
 
 */
extern CGSize const CPMaximumListSectionImageSize;

/**
 @c CPListSection models a single section of items appearing in a @c CPListTemplate.
 */
API_AVAILABLE(ios(12.0)) API_UNAVAILABLE(macos, watchos, tvos)
@interface CPListSection : NSObject <NSSecureCoding>

/**
 Create a section with a list of items and an optional header and identifier.
 */

#if __swift__
- (instancetype)initWithItems:(NSArray *)items
                       header:(nullable NSString *)header
            sectionIndexTitle:(nullable NSString *)sectionIndexTitle NS_REFINED_FOR_SWIFT;
#else
- (instancetype)initWithItems:(NSArray <id <CPListTemplateItem>> *)items
                       header:(nullable NSString *)header
            sectionIndexTitle:(nullable NSString *)sectionIndexTitle;
#endif

/**
 Create a section with a list of items and an optional header containing labels, an image, and a button.
 
 @note The maximum size of the section header image is given by CPMaximumListSectionImageSize.
 
 When providing an image, your app may provide a @c UIImage that is display-ready. If necessary for the image, provide
 light and dark styles by using an asset from your asset catalog, prepared with light and dark styles
 or by using @c UIImageAsset to combine two @c UIImage instances into a single image with
 both styles.

 UIImageAsset is used to combine multiple UIImages with different trait collections into a single UIImage.
  
 @discussion To properly size your header image, your app should consider the display scale of the car screen.
 See -[CPInterfaceController carTraitCollection].
 
 */

- (instancetype)initWithItems:(NSArray <id <CPListTemplateItem>> *)items
                       header:(NSString *)header
               headerSubtitle:(nullable NSString *)headerSubtitle
                  headerImage:(nullable UIImage *)headerImage
                 headerButton:(nullable CPButton *)headerButton
            sectionIndexTitle:(nullable NSString *)sectionIndexTitle API_AVAILABLE(ios(15.0));
/**
 Create a section by specifying a list of items.
 */

#if __swift__
- (instancetype)initWithItems:(NSArray *)items NS_REFINED_FOR_SWIFT;
#else
- (instancetype)initWithItems:(NSArray <id <CPListTemplateItem>> *)items;
#endif

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

/**
 * Optional string to use for a simple header in this section.
 */
@property (nullable, nonatomic, readonly, copy) NSString *header;

/**
 * Optional section header elements used by the enhanced header in this section.
 */

@property (nullable, nonatomic, readonly, copy) NSString *headerSubtitle API_AVAILABLE(ios(15.0));
@property (nullable, nonatomic, copy) UIImage *headerImage API_AVAILABLE(ios(15.0));
@property (nullable, nonatomic, readonly, copy) CPButton *headerButton API_AVAILABLE(ios(15.0));

/**
 An optional section index title to use in a table displaying this section.
 The system will enforce a maximum length of 1 for each section index title - in other words,
 you must choose single-character section index titles.
 */
@property (nullable, nonatomic, readonly, copy) NSString *sectionIndexTitle;

/**
 Items appearing in this section.
 */
@property (nonatomic, readonly, copy) NSArray <id <CPListTemplateItem>> *items;

/**
 Search for an item in this section, returning its index
 or @c NSNotFound if not found.
 */
- (NSUInteger)indexOfItem:(id <CPListTemplateItem>)item;

/**
 Convenience access to the item in this section at the specified index.
 */
- (id <CPListTemplateItem>)itemAtIndex:(NSUInteger)index;

@end

NS_ASSUME_NONNULL_END
