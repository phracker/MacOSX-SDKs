//
//  QLPreviewSceneActivationConfiguration.h
//  Mobile Quick Look
//
//  Copyright 2021 Apple Inc. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <UIKit/UIWindowSceneActivationConfiguration.h>

#import <QuickLook/QLBase.h>


NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(15.0))
API_UNAVAILABLE(visionos)
NS_SWIFT_NAME(QLPreviewSceneActivationConfiguration.Options)
QL_EXPORT @interface QLPreviewSceneOptions : NSObject
    /*!
     * @abstract The index of the item to preview initially .
     */
     @property (assign) NSInteger initialPreviewIndex;
@end

API_AVAILABLE(ios(15.0))
API_UNAVAILABLE(visionos)
QL_EXPORT @interface QLPreviewSceneActivationConfiguration : UIWindowSceneActivationConfiguration

    /**
    * @abstract Create a new  scene configuration to preview items at `urls`.
    * @param urls The urls of the items to preview.
    * @param options Additional information to preview the items.
    */
- (instancetype)initWithItemsAtURLs:(NSArray <NSURL *> *)urls options:(nullable QLPreviewSceneOptions *)options NS_DESIGNATED_INITIALIZER;

- (instancetype)initWithUserActivity:(NSUserActivity *)userActivity NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
