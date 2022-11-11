//
//  PKLassoTool.h
//  PencilKit
//
//  Copyright © 2019 Apple. All rights reserved.
//

#import <PencilKit/PencilKit.h>
#import <PencilKit/PKTool.h>

NS_ASSUME_NONNULL_BEGIN

/// A lasso tool for selection parts of a drawing.
API_AVAILABLE(ios(13.0), macos(10.15))
@interface PKLassoTool : PKTool

- (instancetype)init NS_DESIGNATED_INITIALIZER;

@end

NS_ASSUME_NONNULL_END
