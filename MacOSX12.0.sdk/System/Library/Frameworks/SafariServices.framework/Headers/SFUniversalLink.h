//
//  SFUniversalLink.h
//  SafariServices
//
//  Copyright © 2019 Apple Inc. All rights reserved.
//

#import <SafariServices/SFFoundation.h>
#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/// This class represents a universal link available on the current system.
/// Universal links can be opened in a browser or directly in an application.
///
/// @warning The use of this class requires an entitlement.
NS_CLASS_AVAILABLE_MAC(10_15)
@interface SFUniversalLink : NSObject
+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;

/// Initialize the receiver with a web URL that may or may not be a universal link.
- (nullable instancetype)initWithWebpageURL:(NSURL *)url;

/// The URL passed when initializing the receiver.
@property (readonly) NSURL *webpageURL;

/// The file URL to the application that can handle this universal link.
@property (readonly) NSURL *applicationURL;

/// Whether or not this universal link is enabled. If it is enabled, the URL
/// will open in the application instead of the browser. Set this property when
/// the user indicates they wish to enable or disable this universal link.
@property (getter=isEnabled) BOOL enabled;
@end

NS_ASSUME_NONNULL_END
