#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UIGuidedAccessRestrictions.h>)
//
//  UIGuidedAccessRestrictions.h
//  UIKit
//
//  Copyright (c) 2012-2018 Apple Inc. All rights reserved.
//

// This header exists for backwards compatibility. The relevant declarations have moved into UIGuidedAccess.h
#import <UIKit/UIGuidedAccess.h>

#else
#import <UIKitCore/UIGuidedAccessRestrictions.h>
#endif
