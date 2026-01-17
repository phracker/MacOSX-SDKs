#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<ShareSheet/UIActivityItemsConfigurationReading+ShareSheet.h>)
//
//  UIActivityItemsConfigurationReading+ShareSheet.h
//  ShareSheet
//
//  Created by Miranda Zhou on 3/7/24.
//  Copyright © 2024 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKitDefines.h>
#import <UIKit/UIActivityItemsConfigurationReading.h>

/// @abstract A key for an array of INPerson objects representing recipients who will be filled in by default in the compose view if that sharing app supports it.
/// @discussion This might fail to pre-fill correctly if the sharing app chosen by the user can't recognize the provided person. Also, if a people suggestion is chosen, that suggestion will override this provided value.
UIKIT_EXTERN UIActivityItemsConfigurationMetadataKey const UIActivityItemsConfigurationMetadataKeyShareRecipients API_AVAILABLE(ios(18.0)) API_UNAVAILABLE(watchos) API_UNAVAILABLE(tvos);

#else
#import <ShareSheet/UIActivityItemsConfigurationReading+ShareSheet.h>
#endif
