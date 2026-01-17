#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UINib.h>)
//
//  UINib.h
//  UIKit
//
//  Copyright (c) 2008-2018 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKitDefines.h>
#import <UIKit/UINibLoading.h>

NS_HEADER_AUDIT_BEGIN(nullability, sendability)
    
UIKIT_EXTERN API_AVAILABLE(ios(4.0)) API_UNAVAILABLE(watchos) NS_SWIFT_UI_ACTOR API_DEPRECATED("Loading Interface Builder products will not be supported in a future version of visionOS.", visionos(1.0, 1.0))
@interface UINib : NSObject

// If the bundle parameter is nil, the main bundle is used.
// Releases resources in response to memory pressure (e.g. memory warning), reloading from the bundle when necessary.
+ (UINib *)nibWithNibName:(NSString *)name bundle:(nullable NSBundle *)bundleOrNil;

// If the bundle parameter is nil, the main bundle is used.
+ (UINib *)nibWithData:(NSData *)data bundle:(nullable NSBundle *)bundleOrNil;

// Returns an array containing the top-level objects from the NIB.
// The owner and options parameters may both be nil.
// If the owner parameter is nil, connections to File's Owner are not permitted.
// Options are identical to the options specified with -[NSBundle loadNibNamed:owner:options:]
- (NSArray *)instantiateWithOwner:(nullable id)ownerOrNil options:(nullable NSDictionary<UINibOptionsKey, id> *)optionsOrNil;
@end

NS_HEADER_AUDIT_END(nullability, sendability)

#else
#import <UIKitCore/UINib.h>
#endif
