//
//  BELayerHierarchyHostingView.h
//  BrowserEngineKit
//
//  Copyright © 2023 Apple Inc. All rights reserved.
//

#import <BrowserEngineKit/BELayerHierarchyHandle.h>
#import <BrowserEngineKit/BEMacros.h>
#import <Foundation/Foundation.h>

#if BROWSERENGINEKIT_HAS_UIVIEW

#import <UIKit/UIKit.h>


NS_ASSUME_NONNULL_BEGIN


API_AVAILABLE(ios(17.4))
API_UNAVAILABLE(macos, watchos, tvos, visionos)
BROWSERENGINE_EXPORT
NS_SWIFT_UI_ACTOR
NS_SWIFT_NAME(LayerHierarchyHostingView)
@interface BELayerHierarchyHostingView : UIView

/// a reference to a BELayerHierarchy whose contents should appear as the contents of this view
@property (nonatomic, strong, nullable) BELayerHierarchyHandle *handle NS_SWIFT_NAME(handle);

@end


NS_ASSUME_NONNULL_END

#endif
