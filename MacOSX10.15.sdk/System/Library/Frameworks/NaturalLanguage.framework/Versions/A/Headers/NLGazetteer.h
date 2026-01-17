/*    NLGazetteer.h
      Copyright (c) 2018-2019, Apple Inc. All rights reserved.
*/

#import <Foundation/Foundation.h>
#import <NaturalLanguage/NLLanguage.h>

NS_ASSUME_NONNULL_BEGIN

/* NLGazetteer is a class representing an efficient probabilistic representation for assigning labels to a set of strings.
*/

NS_CLASS_AVAILABLE(10_15, 13_0)
@interface NLGazetteer : NSObject

+ (nullable instancetype)gazetteerWithContentsOfURL:(NSURL *)url error:(NSError **)error API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0), tvos(13.0));

- (nullable instancetype)initWithContentsOfURL:(NSURL *)url error:(NSError **)error NS_DESIGNATED_INITIALIZER API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0), tvos(13.0));
- (nullable instancetype)initWithData:(NSData *)data error:(NSError **)error NS_DESIGNATED_INITIALIZER API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0), tvos(13.0));

- (nullable instancetype)initWithDictionary:(NSDictionary <NSString *, NSArray<NSString *> *> *)dictionary language:(nullable NLLanguage)language error:(NSError **)error NS_DESIGNATED_INITIALIZER API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0), tvos(13.0));

- (nullable NSString *)labelForString:(NSString *)string API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0), tvos(13.0));

@property (nullable, readonly, copy) NLLanguage language API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0), tvos(13.0));
@property (readonly, copy) NSData *data API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0), tvos(13.0));

+ (BOOL)writeGazetteerForDictionary:(NSDictionary <NSString *, NSArray<NSString *> *> *)dictionary language:(nullable NLLanguage)language toURL:(NSURL *)url error:(NSError **)error API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0), tvos(13.0)) NS_SWIFT_NAME(write(_:language:to:));

@end

NS_ASSUME_NONNULL_END
