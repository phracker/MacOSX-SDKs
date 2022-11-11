#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UIToolTipInteraction.h>)
//
//  UIToolTipInteraction.h
//  UIKit
//
//  Copyright © 2020 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIInteraction.h>

NS_ASSUME_NONNULL_BEGIN

@protocol UIToolTipInteractionDelegate;
                           
UIKIT_EXTERN API_AVAILABLE(ios(15.0)) API_UNAVAILABLE(watchos, tvos)
@interface UIToolTipInteraction : NSObject <UIInteraction>

/// The interaction's delegate.
@property (nonatomic, weak, nullable) id<UIToolTipInteractionDelegate> delegate;

/// Indicates whether the interaction is enabled. Defaults to YES.
@property (nonatomic, getter=isEnabled) BOOL enabled;

/// The interaction's default tool tip string.
@property (nonatomic, copy, nullable) NSString *defaultToolTip;

/*!
 * @abstract Creates a UIToolTipInteraction.
 */
- (instancetype)init;
- (instancetype)initWithDefaultToolTip:(NSString *)defaultToolTip;

@end


UIKIT_EXTERN API_AVAILABLE(ios(15.0)) API_UNAVAILABLE(watchos, tvos)
@interface UIToolTipConfiguration : NSObject

/// The string to annotate the contents at a given point.
@property (nonatomic, copy, readonly) NSString *toolTip;

/// The rectangle containing the contents being annotated by the tool tip. Value is CGRectNull if the tool tip applies to the entire view.
@property (nonatomic, readonly) CGRect sourceRect;

/// Creates a UIToolTipConfiguration with the provided string, applied to the entire view.
+ (instancetype)configurationWithToolTip:(NSString *)toolTip;

/// Creates a UIToolTipConfiguration with the provided string, applied to the specified region.
+ (instancetype)configurationWithToolTip:(NSString *)toolTip inRect:(CGRect)sourceRect;

+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;

@end


UIKIT_EXTERN API_AVAILABLE(ios(15.0)) API_UNAVAILABLE(watchos, tvos)
@protocol UIToolTipInteractionDelegate <NSObject>

@optional

/*!
 * @abstract Called when the interaction is about to begin.
 *
 * @param interaction  This UIToolTipInteraction.
 *
 * @return The tool tip configuration containing the string and rectangle for this interaction. Return nil if the interaction is inactive or the hit test fails.
 */
- (nullable UIToolTipConfiguration *)toolTipInteraction:(UIToolTipInteraction *)interaction configurationAtPoint:(CGPoint)point;

@end

NS_ASSUME_NONNULL_END

#else
#import <UIKitCore/UIToolTipInteraction.h>
#endif
