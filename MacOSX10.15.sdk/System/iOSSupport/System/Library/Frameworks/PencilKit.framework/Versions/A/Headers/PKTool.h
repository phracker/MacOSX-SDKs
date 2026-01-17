//
//  PKTool.h
//  PencilKit
//
//  Copyright © 2019 Apple. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/// An interaction behavior for a PKCanvasView.
/// Should not be subclassed outside of the PencilKit framework.
NS_REFINED_FOR_SWIFT
API_AVAILABLE(ios(13.0))
@interface PKTool : NSObject <NSCopying>

- (instancetype)init NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
