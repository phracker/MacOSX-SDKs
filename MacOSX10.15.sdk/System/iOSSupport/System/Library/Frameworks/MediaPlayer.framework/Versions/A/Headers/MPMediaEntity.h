//
//  MPMediaEntity.h
//  MediaPlayer
//
//  Copyright 2010 Apple, Inc. All rights reserved.
//

#import <MediaPlayer/MediaPlayerDefines.h>
#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@class MPMediaLibrary;

typedef uint64_t MPMediaEntityPersistentID;

// An MPMediaEntity represents an abstract member of an MPMediaLibrary.
// Concrete subclasses are MPMediaItem and MPMediaItemCollection.

MP_API(ios(4.2))
MP_PROHIBITED(tvos, macos)
@interface MPMediaEntity : NSObject <NSSecureCoding>

// Returns YES for properties which can be used to construct MPMediaPropertyPredicates.
+ (BOOL)canFilterByProperty:(NSString *)property;

// Executes a provided block with the fetched values for the given item properties, or nil if no value is available for a property.
// In some cases, enumerating the values for multiple properties can be more efficient than fetching each individual property with -valueForProperty:.
- (void)enumerateValuesForProperties:(NSSet<NSString *> *)properties usingBlock:(void (^)(NSString *property, id value, BOOL *stop))block MP_API(ios(4.0));

// Read-only support for Objective-C subscripting syntax with MPMediaEntity property constants.
- (nullable id)objectForKeyedSubscript:(id)key MP_API(ios(8.0));

// Returns the value for the given entity property.
// MPMediaItem and MPMediaPlaylist have their own properties
- (nullable id)valueForProperty:(NSString *)property;

#pragma mark - Properties

MP_EXTERN NSString * const MPMediaEntityPropertyPersistentID MP_API(ios(4.2));        // filterable
@property (nonatomic, readonly) MPMediaEntityPersistentID persistentID MP_API(ios(7.0));

@end

NS_ASSUME_NONNULL_END
