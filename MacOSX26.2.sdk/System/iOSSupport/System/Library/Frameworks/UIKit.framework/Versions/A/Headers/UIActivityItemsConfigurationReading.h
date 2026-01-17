#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UIActivityItemsConfigurationReading.h>)
//
//  UIActivityItemsConfigurationReading.h
//  UIKit
//
//  Copyright © 2019 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKitDefines.h>
#import <CoreGraphics/CoreGraphics.h>

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

@class UIActivity;

typedef NSString * UIActivityItemsConfigurationMetadataKey NS_TYPED_EXTENSIBLE_ENUM API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos) API_UNAVAILABLE(tvos);

UIKIT_EXTERN UIActivityItemsConfigurationMetadataKey const UIActivityItemsConfigurationMetadataKeyTitle API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos) API_UNAVAILABLE(tvos); // NSString or NSAttributedString - title
UIKIT_EXTERN UIActivityItemsConfigurationMetadataKey const UIActivityItemsConfigurationMetadataKeyMessageBody API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos) API_UNAVAILABLE(tvos); // NSString or NSAttributedString - message body
UIKIT_EXTERN UIActivityItemsConfigurationMetadataKey const UIActivityItemsConfigurationMetadataKeyLinkPresentationMetadata API_AVAILABLE(ios(15.0)) API_UNAVAILABLE(watchos) API_UNAVAILABLE(tvos); // LPLinkMetadata


typedef NSString * UIActivityItemsConfigurationPreviewIntent NS_TYPED_EXTENSIBLE_ENUM API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos) API_UNAVAILABLE(tvos);

UIKIT_EXTERN UIActivityItemsConfigurationPreviewIntent const UIActivityItemsConfigurationPreviewIntentFullSize API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos) API_UNAVAILABLE(tvos); // Full size preview image
UIKIT_EXTERN UIActivityItemsConfigurationPreviewIntent const UIActivityItemsConfigurationPreviewIntentThumbnail API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos) API_UNAVAILABLE(tvos); // Thumbnail preview image


typedef NSString * UIActivityItemsConfigurationInteraction NS_TYPED_EXTENSIBLE_ENUM API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos) API_UNAVAILABLE(tvos);

UIKIT_EXTERN UIActivityItemsConfigurationInteraction const UIActivityItemsConfigurationInteractionShare API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos) API_UNAVAILABLE(tvos);
UIKIT_EXTERN UIActivityItemsConfigurationInteraction const UIActivityItemsConfigurationInteractionCopy API_AVAILABLE(ios(16.4)) API_UNAVAILABLE(watchos) API_UNAVAILABLE(tvos);


API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos) API_UNAVAILABLE(tvos) NS_SWIFT_UI_ACTOR
@protocol UIActivityItemsConfigurationReading <NSObject>

@property (nonatomic, readonly, copy) NSArray<NSItemProvider *> *itemProvidersForActivityItemsConfiguration;

@optional

- (BOOL)activityItemsConfigurationSupportsInteraction:(UIActivityItemsConfigurationInteraction)interaction NS_SWIFT_NAME(activityItemsConfigurationSupports(interaction:)); // If not implemented, defaults to YES.

- (nullable id)activityItemsConfigurationMetadataForKey:(UIActivityItemsConfigurationMetadataKey)key NS_SWIFT_NAME(activityItemsConfigurationMetadata(key:));

- (nullable id)activityItemsConfigurationMetadataForItemAtIndex:(NSInteger)index key:(UIActivityItemsConfigurationMetadataKey)key;

- (nullable NSItemProvider *)activityItemsConfigurationPreviewForItemAtIndex:(NSInteger)index intent:(UIActivityItemsConfigurationPreviewIntent)intent suggestedSize:(CGSize)suggestedSize;

@property (nonatomic, readonly, nullable, copy) NSArray <UIActivity *> *applicationActivitiesForActivityItemsConfiguration;

@end


/// Protocol adopted by classes that can provide activity items configurations
API_AVAILABLE(ios(15.0)) API_UNAVAILABLE(watchos) API_UNAVAILABLE(tvos)
@protocol UIActivityItemsConfigurationProviding <NSObject>

@property (nonatomic, nullable, readonly, strong) id<UIActivityItemsConfigurationReading> activityItemsConfiguration API_AVAILABLE(ios(15.0)) API_UNAVAILABLE(watchos) API_UNAVAILABLE(tvos);

@end
NS_HEADER_AUDIT_END(nullability, sendability)

#else
#import <UIKitCore/UIActivityItemsConfigurationReading.h>
#endif
