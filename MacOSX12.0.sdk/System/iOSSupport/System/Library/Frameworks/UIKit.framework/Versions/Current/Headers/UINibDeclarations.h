#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UINibDeclarations.h>)
//
//  UINibDeclarations.h
//  UIKit
//
//  Copyright (c) 2005-2019 Apple Inc. All rights reserved.
//

#ifndef IBOutlet
#define IBOutlet
#endif

#ifndef IBOutletCollection
#define IBOutletCollection(ClassName)
#endif

#ifndef IBAction
#define IBAction void
#endif

#ifndef IBInspectable
#define IBInspectable
#endif

#ifndef IB_DESIGNABLE
#define IB_DESIGNABLE
#endif

#ifndef IBSegueAction
#define IBSegueAction
#endif


#else
#import <UIKitCore/UINibDeclarations.h>
#endif
