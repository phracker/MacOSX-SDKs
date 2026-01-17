#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UIDataSourceTranslating.h>)
//
//  UIDataSourceTranslating.h
//  UIKit
//
//  Copyright © 2017-2018 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/* For advanced clients with data model centric layouts (i.e. the layout refers to the data source
 * to gather information in order to create UICollectionViewLayoutAttributes) this protocol allows
 * translation between the data source index path into the presentation index path (i.e. layout) state.
 */
API_AVAILABLE(ios(11.0), tvos(11.0))
@protocol UIDataSourceTranslating <NSObject>

/* Translate (if needed) a Data Source section index to its Presentation section index value.
 * If section was deleted during a transaction, this will return NSNotFound.
 * If no effective change took place, will return passed value.
 */
- (NSInteger)presentationSectionIndexForDataSourceSectionIndex:(NSInteger)dataSourceSectionIndex;

/* Translate (if needed) a Presentation section index to its Data Source section index value.
 * If section was inserted and not known the Data Source, this will return NSNotFound.
 * If no effective change took place, will return passed value.
 */
- (NSInteger)dataSourceSectionIndexForPresentationSectionIndex:(NSInteger)presentationSectionIndex;

/* Translate (if needed) a Data Source index path to the Presentation index path.
 * If the item was deleted at the index path, this will return nil.
 * If no effective change took place, will return passed value.
 */
- (nullable NSIndexPath *)presentationIndexPathForDataSourceIndexPath:(nullable NSIndexPath *)dataSourceIndexPath;

/* Translate (if needed) a Presentation index path to the Data Source index path.
 * If the item was inserted at the index path, this will return nil.
 * If no effective change took place, will return passed value.
 */
- (nullable NSIndexPath *)dataSourceIndexPathForPresentationIndexPath:(nullable NSIndexPath *)presentationIndexPath;

/* Arguments passed to actions performed inside the scope of this block will be interpreted as values in the presentation state,
 * and the values returned from these actions will also be in the presentation state.
 */
- (void)performUsingPresentationValues:(void (NS_NOESCAPE ^)(void))actionsToTranslate NS_SWIFT_NAME(performUsingPresentationValues(_:));

@end

NS_ASSUME_NONNULL_END

#else
#import <UIKitCore/UIDataSourceTranslating.h>
#endif
