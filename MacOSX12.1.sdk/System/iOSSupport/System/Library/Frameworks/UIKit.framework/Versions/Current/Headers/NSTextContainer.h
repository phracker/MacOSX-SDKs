#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/NSTextContainer.h>)
//
//  NSTextContainer.h
//  UIKit
//
//  Copyright (c) 2011-2018, Apple Inc. All rights reserved.
//

#import <Foundation/NSObject.h>
#import <UIKit/NSParagraphStyle.h>
#import <UIKit/UIKitDefines.h>
#import <UIKit/NSLayoutManager.h>

@class UIBezierPath;
@class NSTextLayoutManager;

NS_ASSUME_NONNULL_BEGIN

#if UIKIT_HAS_UIFOUNDATION_SYMBOLS

UIKIT_EXTERN API_AVAILABLE(macos(10.0), ios(7.0))
@interface NSTextContainer : NSObject <NSSecureCoding, NSTextLayoutOrientationProvider>

/**************************** Initialization ****************************/

- (instancetype)initWithSize:(CGSize)size NS_DESIGNATED_INITIALIZER API_AVAILABLE(macos(10.11), ios(7.0));
- (instancetype)initWithCoder:(NSCoder *)coder NS_DESIGNATED_INITIALIZER;


/**************************** Layout ****************************/

// Accessor for the NSLayoutManager object owning the receiver.
// Avoid assigning a layout manager directly through this property.  Adding a text container to a layout manager through -[NSLayoutManager addTextContainer:] will use the property for assigning the new layout manager.
@property (nullable, assign, NS_NONATOMIC_IOSONLY) NSLayoutManager *layoutManager;

// This method should be used instead of the primitive -setLayoutManager: if you need to replace a container's layoutManager with a new one leaving the rest of the web intact.  All the NSTextContainers on the old NSLayoutManager get transferred to the new one.  This method deals with all the work of making sure the containers don't get deallocated and removing the old layoutManager from the text storage and replacing it with the new one.
- (void)replaceLayoutManager:(NSLayoutManager *)newLayoutManager API_AVAILABLE(macos(10.0), ios(9.0));

// Returns NSTextLayoutManager owning the text container. When non-nil, -layoutManager should be nil.
@property (weak, nullable, readonly, NS_NONATOMIC_IOSONLY) NSTextLayoutManager *textLayoutManager API_AVAILABLE(macos(12.0), ios(15.0), tvos(15.0)) API_UNAVAILABLE(watchos);

/************************* Container shape properties *************************/

// Default value: CGSizeZero  Defines the maximum size for the layout area returned from -lineFragmentRectForProposedRect:writingDirection:remainingRect:.  0.0 and less means no limitation.
@property (NS_NONATOMIC_IOSONLY) CGSize size API_AVAILABLE(macos(10.11), ios(7.0));

// Default value : empty array  An array of UIBezierPath representing the exclusion paths inside the receiver's bounding rect.
@property (copy, NS_NONATOMIC_IOSONLY) NSArray<UIBezierPath *> *exclusionPaths API_AVAILABLE(macos(10.11), ios(7.0));

// Default value: NSLineBreakByWordWrapping  The line break mode defines the behavior of the last line inside the text container.
@property (NS_NONATOMIC_IOSONLY) NSLineBreakMode lineBreakMode API_AVAILABLE(macos(10.11), ios(7.0));

/************************* Layout constraint properties *************************/

// Default value: 5.0  The layout padding at the beginning and end of the line fragment rects insetting the layout width available for the contents.  This value is utilized by NSLayoutManager for determining the layout width.
@property (NS_NONATOMIC_IOSONLY) CGFloat lineFragmentPadding;

// Default value: 0 (no limit)  The maximum number of lines that can be stored in the receiver.  This value is utilized by NSLayoutManager for determining the maximum number of lines associated with the text container.
@property (NS_NONATOMIC_IOSONLY) NSUInteger maximumNumberOfLines API_AVAILABLE(macos(10.11), ios(7.0));

/**************************** Line fragments ****************************/

// Returns the bounds of a line fragment rect inside the receiver for proposedRect.  This is the intersection of proposedRect and the receiver's bounding rect defined by -size property.  The regions defined by -exclusionPaths property are excluded from the return value.  charIndex is the character location inside the text storage for the line fragment being processed.  It is possible that proposedRect can be divided into multiple line fragments due to exclusion paths.  In that case, remainingRect returns the remainder that can be passed in as the proposed rect for the next iteration.  baseWritingDirection determines the direction of advancement for line fragments inside a visual horizontal line.  The values passed into the method are either NSWritingDirectionLeftToRight or NSWritingDirectionRightToLeft.  This method can be overridden by subclasses for further text container region customization.
- (CGRect)lineFragmentRectForProposedRect:(CGRect)proposedRect atIndex:(NSUInteger)characterIndex writingDirection:(NSWritingDirection)baseWritingDirection remainingRect:(nullable CGRect *)remainingRect API_AVAILABLE(macos(10.11), ios(7.0));

// Returns YES if the receiver is a rectangular shape defined simply by -size. TextKit utilizes this information for enabling various layout optimizations. NSLayoutManager disables non-contiguous layout when this property is NO. The default implementation returns NO when -exclusionPaths has 1 or more items, -maximumNumberOfLines is not 0, or -lineFragmentRectForProposedRect:atIndex:writingDirection:remainingRect: is overridden. It's recommended to override this property when -lineFragmentRectForProposedRect:atIndex:writingDirection:remainingRect: is overridden.
@property (getter=isSimpleRectangularTextContainer, readonly, NS_NONATOMIC_IOSONLY) BOOL simpleRectangularTextContainer API_AVAILABLE(macos(10.0), ios(9.0));


/**************************** View synchronization ****************************/

// Default value: NO  Define whether the text container view bounds changes can affect the text container size.
@property (NS_NONATOMIC_IOSONLY) BOOL widthTracksTextView;
@property (NS_NONATOMIC_IOSONLY) BOOL heightTracksTextView;

@end

#endif // UIKIT_HAS_UIFOUNDATION_SYMBOLS

NS_ASSUME_NONNULL_END

#else
#import <UIKitCore/NSTextContainer.h>
#endif
