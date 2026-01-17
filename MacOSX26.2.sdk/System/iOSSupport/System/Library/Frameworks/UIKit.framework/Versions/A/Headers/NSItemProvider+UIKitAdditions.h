#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/NSItemProvider+UIKitAdditions.h>)
//
//  NSItemProvider+UIKitAdditions.h
//  UIKit
//
//  Copyright © 2017-2018 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKitDefines.h>
#import <CoreGraphics/CoreGraphics.h>


NS_HEADER_AUDIT_BEGIN(nullability, sendability)

UIKIT_SWIFT_FORWARD_DECLARE(@class NSItemProvider)

typedef NS_ENUM(NSInteger, UIPreferredPresentationStyle) {
    UIPreferredPresentationStyleUnspecified = 0,
    UIPreferredPresentationStyleInline,
    UIPreferredPresentationStyleAttachment,
} API_AVAILABLE(watchos(4.0));

@interface NSItemProvider (UIKitAdditions)

@property (nonatomic, copy, nullable) NSData *teamData API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(watchos, tvos);

// Estimated presentation size, in points. CGSizeZero value indicates this information is not available.
@property (nonatomic) CGSize preferredPresentationSize API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(watchos, tvos);

@property (nonatomic) UIPreferredPresentationStyle preferredPresentationStyle API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(watchos, tvos);

@end

API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(watchos, tvos) NS_SWIFT_UI_ACTOR
@protocol UIItemProviderPresentationSizeProviding <NSObject>

// Implement this on an object which conforms to the NSItemProviderWriting protocol.
// When the object is registered to NSItemProvider, this property will be used to automatically set
// the `preferredPresentationSize` property on NSItemProvider.
// Return CGSizeZero to indicate that this information is not available.
@property (nonatomic, readonly) CGSize preferredPresentationSizeForItemProvider;

@end

API_AVAILABLE(watchos(10.4)) @protocol UIItemProviderReadingAugmentationProviding
// Conforming classes should not fall through to [requestedClass objectWithItemProviderData:typeIdentifier:error:.
// UIItemProvider does this on your behalf.
+ (nullable id)objectWithItemProviderData:(NSData *)data
                           typeIdentifier:(NSString *)typeIdentifier
                           requestedClass:(Class)requestedClass
                                    error:(NSError **)outError;
// Conforming classes should not fall through to -readableTypeIdentifiersForItemProvider of the original NSItemProviderReading clas.
// UIItemProvider does this on your behalf.
@property (class, NS_NONATOMIC_IOSONLY, readonly, copy) NSArray<NSString *> *additionalLeadingReadableTypeIdentifiersForItemProvider;
@property (class, NS_NONATOMIC_IOSONLY, readonly, copy) NSArray<NSString *> *additionalTrailingReadableTypeIdentifiersForItemProvider;
@end

API_AVAILABLE(watchos(10.4)) @protocol UIItemProviderReadingAugmentationDesignating <NSItemProviderReading>
+ (Class<UIItemProviderReadingAugmentationProviding>)_ui_augmentingNSItemProviderReadingClass;
@end


NS_HEADER_AUDIT_END(nullability, sendability)

#else
#import <UIKitCore/NSItemProvider+UIKitAdditions.h>
#endif
