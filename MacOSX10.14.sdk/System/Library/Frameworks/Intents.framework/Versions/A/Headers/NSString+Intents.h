//
//  NSString+Intents.h
//  Intents
//
//  Copyright © 2017 Apple. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(12.0), watchos(5.0), macosx(10.14))
@interface NSString (Intents)

// Reads the string from the Localizable.strings file in the main app's bundle
+ (NSString *)deferredLocalizedIntentsStringWithFormat:(NSString *)format, ... NS_FORMAT_FUNCTION(1,2);

// Reads the string from the provided table file in the main app's bundle
+ (NSString *)deferredLocalizedIntentsStringWithFormat:(NSString *)format fromTable:(nullable NSString *)table, ... NS_FORMAT_FUNCTION(1,3);

// Reads the string from the provided table file in the main app's bundle
+ (NSString *)deferredLocalizedIntentsStringWithFormat:(NSString *)format fromTable:(nullable NSString *)table arguments:(va_list)arguments NS_FORMAT_FUNCTION(1,0) NS_REFINED_FOR_SWIFT;

@end

NS_ASSUME_NONNULL_END
