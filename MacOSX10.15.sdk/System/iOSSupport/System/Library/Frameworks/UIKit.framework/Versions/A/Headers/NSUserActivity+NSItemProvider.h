#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/NSUserActivity+NSItemProvider.h>)
//
//  NSUserActivity+NSItemProvider.h
//  UIKit Framework
//
//  Copyright © 2019 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKitDefines.h>

UIKIT_EXTERN API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos, tvos) @interface NSUserActivity (NSItemProvider) <NSItemProviderReading, NSItemProviderWriting>
@end


#else
#import <UIKitCore/NSUserActivity+NSItemProvider.h>
#endif
