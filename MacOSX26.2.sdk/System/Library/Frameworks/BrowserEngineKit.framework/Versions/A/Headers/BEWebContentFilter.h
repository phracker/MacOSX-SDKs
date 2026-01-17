//
//  BEWebContentFilter.h
//  BrowserEngineKit
//
//  Copyright © 2025 Apple Inc. All rights reserved.
//

#import <BrowserEngineKit/BEMacros.h>
#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/// An object that represents a web content filter
API_AVAILABLE(ios(26.2))
API_UNAVAILABLE(macos, watchos, tvos, visionos)
BROWSERENGINE_EXPORT
@interface BEWebContentFilter : NSObject
/**
 @abstract Determines whether the built-in web content filter is active.
 @returns YES if the built-in web content filter is active, and NO if it isn't.
 */
@property (class, readonly) BOOL shouldEvaluateURLs;

/**
 @abstract Evaluates whether a URL should be blocked and if so, provides a UTF-8
 encoded HTML representation of a blocking page.
 @param url The URL to be evaluated.
 @param completionHandler The completion block to be invoked with result when
 evaluation is complete. Result is YES if the url should be blocked, and NO if it isn't.
 @discussion This method performs a lazy initialization of some objects, so the
 first call could take longer than subsequent calls.
 */
- (void)evaluateURL:(NSURL *)url completionHandler:(void (^)(BOOL shouldBlock,  NSData * _Nullable blockPageRepresentation))completionHandler;

/**
 @abstract Adds blocked URL to built-in web content filter's allowlist.
 @param url The URL to be added.
 @param completionHandler The completion block to be called when the add
 operation is complete, with result of the operation. Result is YES if the url is added
 successfully, and NO if it isn't.
 */
- (void)allowURL:(NSURL *)url completionHandler:(void (^)(BOOL didAllow, NSError * _Nullable error))completionHandler;
@end

NS_ASSUME_NONNULL_END
