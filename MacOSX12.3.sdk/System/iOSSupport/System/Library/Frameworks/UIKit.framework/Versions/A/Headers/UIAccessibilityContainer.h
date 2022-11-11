#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UIAccessibilityContainer.h>)
//
//  UIAccessibilityContainer.h
//  UIKit
//
//  Copyright (c) 2016-2018 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIAccessibilityConstants.h>
#import <UIKit/UIKitDefines.h>

NS_ASSUME_NONNULL_BEGIN

/*
 UIAccessibilityContainer
 
 UIAccessibilityContainer methods can be overridden to vend individual elements
 that are managed by a single UIView.
 
 For example, a single UIView might draw several items that (to an
 end user) have separate meaning and functionality.  It is important to vend
 each item as an individual accessibility element.
 
 Sub-elements of a container that are not represented by concrete UIView
 instances (perhaps painted text or icons) can be represented using instances
 of UIAccessibilityElement class (see UIAccessibilityElement.h).
 
 Accessibility containers MUST return NO to -isAccessibilityElement.
 */
@interface NSObject (UIAccessibilityContainer)

/*
 Returns the number of accessibility elements in the container.
 */
- (NSInteger)accessibilityElementCount NS_SWIFT_UI_ACTOR;

/*
 Returns the accessibility element in order, based on index.
 default == nil
 */
- (nullable id)accessibilityElementAtIndex:(NSInteger)index NS_SWIFT_UI_ACTOR;

/*
 Returns the ordered index for an accessibility element
 default == NSNotFound
 */
- (NSInteger)indexOfAccessibilityElement:(id)element NS_SWIFT_UI_ACTOR;

// A list of container elements managed by the receiver.
// This can be used as an alternative to implementing the dynamic methods.
// default == nil
@property (nullable, nonatomic, strong) NSArray *accessibilityElements API_AVAILABLE(ios(8.0)) NS_SWIFT_UI_ACTOR;

// Some containers provide more context for accessibility elements, such as tables or lists.
// Set this property so that assistive technologies can output more information.
// default == UIAccessibilityContainerTypeNone
@property (nonatomic) UIAccessibilityContainerType accessibilityContainerType API_AVAILABLE(ios(11.0)) NS_SWIFT_UI_ACTOR;

@end

/* 
 The UIAccessibilityContainerDataTable and UIAccessibilityContainerDataTableCell protocols
 convey more information specific to tables that contain structured data.
 */

UIKIT_EXTERN API_AVAILABLE(ios(11.0)) NS_SWIFT_UI_ACTOR
@protocol UIAccessibilityContainerDataTableCell <NSObject>
@required

// The row/column index + the row/column span.
// default == { NSNotFound, 0 }
- (NSRange)accessibilityRowRange;
- (NSRange)accessibilityColumnRange;

@end

UIKIT_EXTERN API_AVAILABLE(ios(11.0)) NS_SWIFT_UI_ACTOR
@protocol UIAccessibilityContainerDataTable <NSObject>
@required

// Return the cell element for a specific row/column, including elements that span rows/columns.
// default == nil
- (nullable id<UIAccessibilityContainerDataTableCell>)accessibilityDataTableCellElementForRow:(NSUInteger)row column:(NSUInteger)column;

- (NSUInteger)accessibilityRowCount;
- (NSUInteger)accessibilityColumnCount;

@optional
// Return header elements for a specific row or column.
// default == nil
- (nullable NSArray<id<UIAccessibilityContainerDataTableCell>> *)accessibilityHeaderElementsForRow:(NSUInteger)row;
- (nullable NSArray<id<UIAccessibilityContainerDataTableCell>> *)accessibilityHeaderElementsForColumn:(NSUInteger)column;

@end

NS_ASSUME_NONNULL_END

#else
#import <UIKitCore/UIAccessibilityContainer.h>
#endif
