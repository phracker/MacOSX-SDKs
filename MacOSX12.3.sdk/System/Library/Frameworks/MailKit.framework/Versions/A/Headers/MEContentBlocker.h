//
//  MEContentBlocker.h
//  MailKit
//
//  Copyright © 2021 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/// @brief Methods in this protocol can be used by a mail app extension to block content in mail messages.
API_AVAILABLE(macos(12.0)) API_UNAVAILABLE(ios, watchos, tvos, macCatalyst)
@protocol MEContentBlocker <NSObject>
/// @brief This is invoked when Mail configures its @c WKWebViewConfiguration or if the extension is enabled. The returned data should contain UTF8 encoded String data with the filter list.
- (NSData *)contentRulesJSON;
@end

NS_ASSUME_NONNULL_END
