/*    NLEmbedding.h
      Copyright (c) 2018-2019, Apple Inc. All rights reserved.
*/

#import <Foundation/Foundation.h>
#import <NaturalLanguage/NLLanguage.h>

NS_ASSUME_NONNULL_BEGIN

/* NLEmbedding is a class representing a map from a set of strings into a finite-dimensional real vector space. Predefined word embeddings are provided for certain languages.
*/

typedef NS_ENUM(NSInteger, NLDistanceType) {
    NLDistanceTypeCosine    /*  A cosine distance in embedding space, i.e. 1 - cosine similarity, in the range [0.0, 2.0]. */
};

typedef double NLDistance;

NS_CLASS_AVAILABLE(10_15, 13_0)
@interface NLEmbedding : NSObject

+ (nullable NLEmbedding *)wordEmbeddingForLanguage:(NLLanguage)language API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0), tvos(13.0)) NS_SWIFT_NAME(wordEmbedding(for:));
+ (nullable NLEmbedding *)wordEmbeddingForLanguage:(NLLanguage)language revision:(NSUInteger)revision API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0), tvos(13.0)) NS_SWIFT_NAME(wordEmbedding(for:revision:));

+ (nullable instancetype)embeddingWithContentsOfURL:(NSURL *)url error:(NSError **)error API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0), tvos(13.0));

- (BOOL)containsString:(NSString *)string API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0), tvos(13.0));
- (NLDistance)distanceBetweenString:(NSString *)firstString andString:(NSString *)secondString distanceType:(NLDistanceType)distanceType API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0), tvos(13.0)) NS_REFINED_FOR_SWIFT;

- (void)enumerateNeighborsForString:(NSString *)string maximumCount:(NSUInteger)maxCount distanceType:(NLDistanceType)distanceType usingBlock:(void (NS_NOESCAPE ^)(NSString *neighbor, NLDistance distance, BOOL *stop))block API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0), tvos(13.0)) NS_REFINED_FOR_SWIFT;
- (void)enumerateNeighborsForString:(NSString *)string maximumCount:(NSUInteger)maxCount maximumDistance:(NLDistance)maxDistance distanceType:(NLDistanceType)distanceType usingBlock:(void (NS_NOESCAPE ^)(NSString *neighbor, NLDistance distance, BOOL *stop))block API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0), tvos(13.0)) NS_REFINED_FOR_SWIFT;
- (nullable NSArray <NSString *> *)neighborsForString:(NSString *)string maximumCount:(NSUInteger)maxCount distanceType:(NLDistanceType)distanceType API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0), tvos(13.0)) NS_REFINED_FOR_SWIFT;
- (nullable NSArray <NSString *> *)neighborsForString:(NSString *)string maximumCount:(NSUInteger)maxCount maximumDistance:(NLDistance)maxDistance distanceType:(NLDistanceType)distanceType API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0), tvos(13.0)) NS_REFINED_FOR_SWIFT;

- (nullable NSArray <NSNumber *> *)vectorForString:(NSString *)string API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0), tvos(13.0)) NS_REFINED_FOR_SWIFT;
- (BOOL)getVector:(float *)vector forString:(NSString *)string API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0), tvos(13.0)) NS_SWIFT_UNAVAILABLE("Use 'vector(for:)' instead");

- (void)enumerateNeighborsForVector:(NSArray <NSNumber *> *)vector maximumCount:(NSUInteger)maxCount distanceType:(NLDistanceType)distanceType usingBlock:(void (NS_NOESCAPE ^)(NSString *neighbor, NLDistance distance, BOOL *stop))block API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0), tvos(13.0)) NS_REFINED_FOR_SWIFT;
- (void)enumerateNeighborsForVector:(NSArray <NSNumber *> *)vector maximumCount:(NSUInteger)maxCount maximumDistance:(NLDistance)maxDistance distanceType:(NLDistanceType)distanceType usingBlock:(void (NS_NOESCAPE ^)(NSString *neighbor, NLDistance distance, BOOL *stop))block API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0), tvos(13.0)) NS_REFINED_FOR_SWIFT;
- (NSArray <NSString *> *)neighborsForVector:(NSArray <NSNumber *> *)vector maximumCount:(NSUInteger)maxCount distanceType:(NLDistanceType)distanceType API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0), tvos(13.0)) NS_REFINED_FOR_SWIFT;
- (NSArray <NSString *> *)neighborsForVector:(NSArray <NSNumber *> *)vector maximumCount:(NSUInteger)maxCount maximumDistance:(NLDistance)maxDistance distanceType:(NLDistanceType)distanceType API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0), tvos(13.0)) NS_REFINED_FOR_SWIFT;

@property (readonly) NSUInteger dimension API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0), tvos(13.0));
@property (readonly) NSUInteger vocabularySize API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0), tvos(13.0));
@property (nullable, readonly, copy) NLLanguage language API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0), tvos(13.0));
@property (readonly) NSUInteger revision API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0), tvos(13.0));

+ (NSIndexSet *)supportedRevisionsForLanguage:(NLLanguage)language API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0), tvos(13.0)) NS_SWIFT_NAME(supportedRevisions(for:));
+ (NSUInteger)currentRevisionForLanguage:(NLLanguage)language API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0), tvos(13.0)) NS_SWIFT_NAME(currentRevision(for:));

+ (BOOL)writeEmbeddingForDictionary:(NSDictionary <NSString *, NSArray <NSNumber *> *> *)dictionary language:(nullable NLLanguage)language revision:(NSUInteger)revision toURL:(NSURL *)url error:(NSError **)error API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0), tvos(13.0)) NS_REFINED_FOR_SWIFT;

@end

NS_ASSUME_NONNULL_END
