//
//  AXRequest.h
//  AccessibilitySharedSupport
//
//  Created by Daniel Golden on 5/22/24.
//  Copyright © 2024 Apple. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <Accessibility/AXFoundation.h>
#import <Accessibility/AXTechnology.h>

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(18.0), macos(15.0), tvos(18.0), watchos(11.0), visionos(2.0))
NS_SWIFT_NAME(AccessibilityRequest)
AX_EXTERN
@interface AXRequest : NSObject <NSCopying, NSSecureCoding>

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

// If the currentRequest is nil, you must still return a valid reasonable default value from accessibility APIs
@property (nullable, class, nonatomic, readonly) AXRequest *currentRequest NS_SWIFT_NAME(current);
@property (nonatomic, readonly) AXTechnology technology;

@end

NS_ASSUME_NONNULL_END
