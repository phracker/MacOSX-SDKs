//
//  AXTechnology.h
//  AccessibilitySharedSupport
//
//  Created by Daniel Golden on 5/22/24.
//  Copyright © 2024 Apple. All rights reserved.
//

#import <Accessibility/AXFoundation.h>

typedef NSString *const AXTechnology NS_TYPED_ENUM NS_SWIFT_NAME(AccessibilityTechnology);

AX_EXTERN AXTechnology AXTechnologyVoiceOver API_AVAILABLE(ios(18.0), macos(15.0), tvos(18.0), watchos(11.0), visionos(2.0));
AX_EXTERN AXTechnology AXTechnologySwitchControl API_AVAILABLE(ios(18.0), macos(15.0), tvos(18.0), watchos(11.0), visionos(2.0));
AX_EXTERN AXTechnology AXTechnologyVoiceControl API_AVAILABLE(ios(18.0), macos(15.0), tvos(18.0), watchos(11.0), visionos(2.0));
AX_EXTERN AXTechnology AXTechnologyFullKeyboardAccess API_AVAILABLE(ios(18.0), macos(15.0), tvos(18.0), watchos(11.0), visionos(2.0));
AX_EXTERN AXTechnology AXTechnologySpeakScreen API_AVAILABLE(ios(18.0), macos(15.0), tvos(18.0), watchos(11.0), visionos(2.0));
AX_EXTERN AXTechnology AXTechnologyAutomation API_AVAILABLE(ios(18.0), macos(15.0), tvos(18.0), watchos(11.0), visionos(2.0));
AX_EXTERN AXTechnology AXTechnologyHoverText API_AVAILABLE(ios(18.0), macos(15.0), tvos(18.0), watchos(11.0), visionos(2.0));
AX_EXTERN AXTechnology AXTechnologyZoom API_AVAILABLE(ios(18.0), macos(15.0), tvos(18.0), watchos(11.0), visionos(2.0));
