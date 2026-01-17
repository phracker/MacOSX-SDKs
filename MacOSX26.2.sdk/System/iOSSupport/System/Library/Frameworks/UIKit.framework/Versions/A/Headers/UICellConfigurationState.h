#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UICellConfigurationState.h>)
//
//  UICellConfigurationState.h
//  UIKit
//
//  Copyright © 2020 Apple Inc. All rights reserved.
//

#import <UIKit/UIViewConfigurationState.h>

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

typedef NS_ENUM(NSInteger, UICellConfigurationDragState) {
    /// The cell is not associated with a drag session.
    UICellConfigurationDragStateNone,
    /// The cell is being lifted, before has joined a drag session.
    UICellConfigurationDragStateLifting,
    /// The cell is part of an active drag session.
    UICellConfigurationDragStateDragging
} API_AVAILABLE(ios(14.0)) API_UNAVAILABLE(tvos, watchos);

typedef NS_ENUM(NSInteger, UICellConfigurationDropState) {
    /// The cell is not associated with a drag session.
    UICellConfigurationDropStateNone,
    /// A drag session is active and may perform a drop in the cell's container, but the cell itself
    /// is not the drop target.
    UICellConfigurationDropStateNotTargeted,
    /// The cell is the drop target for a drag session.
    UICellConfigurationDropStateTargeted
} API_AVAILABLE(ios(14.0)) API_UNAVAILABLE(tvos, watchos);


UIKIT_EXTERN API_AVAILABLE(ios(14.0), tvos(14.0)) API_UNAVAILABLE(watchos) NS_SWIFT_UI_ACTOR
@interface UICellConfigurationState : UIViewConfigurationState

@property (nonatomic, getter=isEditing) BOOL editing;
@property (nonatomic, getter=isExpanded) BOOL expanded;
@property (nonatomic, getter=isSwiped) BOOL swiped;
@property (nonatomic, getter=isReordering) BOOL reordering;

@property (nonatomic) UICellConfigurationDragState cellDragState API_UNAVAILABLE(tvos, watchos);
@property (nonatomic) UICellConfigurationDropState cellDropState API_UNAVAILABLE(tvos, watchos);

@end

NS_HEADER_AUDIT_END(nullability, sendability)

#else
#import <UIKitCore/UICellConfigurationState.h>
#endif
