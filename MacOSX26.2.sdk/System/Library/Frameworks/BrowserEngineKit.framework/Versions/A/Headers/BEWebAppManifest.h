//
//  BEWebAppManifest.h
//  BrowserEngineKit
//
//  Copyright © 2024 Apple Inc. All rights reserved.
//

#import <BrowserEngineKit/BEMacros.h>
#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/// An object that represents a web application manifest
API_AVAILABLE(ios(17.5))
BROWSERENGINE_EXPORT
@interface BEWebAppManifest : NSObject

- (instancetype)init NS_UNAVAILABLE;

/// Returns nil if manifestURL is invalid or jsonData cannot be parsed.
- (nullable BEWebAppManifest*)initWithJSONData:(NSData *)jsonData manifestURL:(NSURL *)manifestURL NS_DESIGNATED_INITIALIZER;

@property (nonatomic, readonly, copy) NSData *jsonData;
@property (nonatomic, readonly, copy) NSURL *manifestURL;

@end

NS_ASSUME_NONNULL_END
