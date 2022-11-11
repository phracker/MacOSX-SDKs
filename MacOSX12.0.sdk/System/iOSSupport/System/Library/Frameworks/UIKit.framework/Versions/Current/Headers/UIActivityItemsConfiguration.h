#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UIActivityItemsConfiguration.h>)
//
//  UIActivityItemsConfiguration.h
//  UIKit
//
//  Copyright © 2019 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKitDefines.h>
#import <UIKit/UIActivityItemsConfigurationReading.h>
#import <CoreGraphics/CoreGraphics.h>

NS_ASSUME_NONNULL_BEGIN

@class UIActivity;
@class UIViewController;
@class UIView;


// A configuration that allows a responder to export data through a variety of interactions.
UIKIT_EXTERN API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos) API_UNAVAILABLE(tvos) NS_SWIFT_UI_ACTOR
@interface UIActivityItemsConfiguration : NSObject <UIActivityItemsConfigurationReading>

@property (nonatomic, strong, nullable) id localObject; // A local object retained for the convenience of the app developer
@property (nonatomic, copy) NSArray<UIActivityItemsConfigurationInteraction> *supportedInteractions; // Defaults to all known interactions
@property (nonatomic, strong, nullable) id _Nullable (^metadataProvider)(UIActivityItemsConfigurationMetadataKey key);
@property (nonatomic, strong, nullable) id _Nullable (^perItemMetadataProvider)(NSInteger index, UIActivityItemsConfigurationMetadataKey key);
@property (nonatomic, strong, nullable) NSItemProvider *_Nullable (^previewProvider)(NSInteger index, UIActivityItemsConfigurationPreviewIntent intent, CGSize suggestedSize);
@property (nonatomic, strong, nullable) NSArray<UIActivity *> *(^applicationActivitiesProvider)(void);

+ (instancetype)activityItemsConfigurationWithObjects:(NSArray<id<NSItemProviderWriting> > *)objects; // Provide data up front
+ (instancetype)activityItemsConfigurationWithItemProviders:(NSArray<NSItemProvider *> *)itemProviders; // Provide promised items

- (instancetype)initWithObjects:(NSArray<id<NSItemProviderWriting> > *)objects NS_DESIGNATED_INITIALIZER; // Provide data up front
- (instancetype)initWithItemProviders:(NSArray<NSItemProvider *> *)itemProviders NS_DESIGNATED_INITIALIZER; // Provide promised items

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END

#else
#import <UIKitCore/UIActivityItemsConfiguration.h>
#endif
