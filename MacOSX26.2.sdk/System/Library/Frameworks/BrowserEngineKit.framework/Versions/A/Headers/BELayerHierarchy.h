//
//  BELayerHierarchy.h
//  BrowserEngineKit
//
//  Copyright © 2023 Apple Inc. All rights reserved.
//

#import <BrowserEngineKit/BELayerHierarchyHandle.h>
#import <BrowserEngineKit/BEMacros.h>
#import <Foundation/Foundation.h>


NS_ASSUME_NONNULL_BEGIN

@class CALayer;

API_AVAILABLE(ios(17.4))
API_UNAVAILABLE(macos, watchos, tvos, visionos)
BROWSERENGINE_EXPORT
BROWSERENGINE_FINAL
NS_SWIFT_UI_ACTOR
NS_SWIFT_NAME(LayerHierarchy)
@interface BELayerHierarchy : NSObject

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

/// may fail if a connection to the render server cannot be established
+ (nullable BELayerHierarchy *)layerHierarchyWithError:(NSError **)error NS_SWIFT_NAME(init());

/// a reference to this `BELayerHierarchy` for use with `BELayerHierarchyHostingView`
@property (nonatomic, readonly, strong) BELayerHierarchyHandle *handle NS_SWIFT_NAME(handle);

/// the root layer of this hierarchy
@property (nonatomic, strong, nullable) CALayer *layer NS_SWIFT_NAME(layer);

/// invalidate must be called before this layer hierarchy is disposed of
- (void)invalidate NS_SWIFT_NAME(invalidate());

@end


NS_ASSUME_NONNULL_END
