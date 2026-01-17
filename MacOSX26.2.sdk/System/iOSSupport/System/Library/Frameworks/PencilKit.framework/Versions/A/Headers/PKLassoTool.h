//
//  PKLassoTool.h
//  PencilKit
//
//  Copyright © 2019 Apple Inc. All rights reserved.
//

#import <PencilKit/PKTool.h>

NS_ASSUME_NONNULL_BEGIN

/// A lasso tool for selecting parts of a drawing.
API_AVAILABLE(ios(13.0), macos(10.15))
NS_SWIFT_SENDABLE
@interface PKLassoTool : PKTool

- (instancetype)init NS_DESIGNATED_INITIALIZER;

@end

NS_ASSUME_NONNULL_END
