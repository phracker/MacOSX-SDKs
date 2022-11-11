//
//  AXColorUtilities.h
//  Accessibility
//
//  Copyright © 2020 Apple Inc. All rights reserved.
//

#import <Accessibility/AXFoundation.h>

NS_ASSUME_NONNULL_BEGIN

// Returns a localized description of the CGColorRef for use in accessibility attributes.
AX_EXTERN
NSString *AXNameFromColor(CGColorRef color) API_AVAILABLE(ios(14.0), tvos(14.0), watchos(7.0), macos(11.0));

NS_ASSUME_NONNULL_END
