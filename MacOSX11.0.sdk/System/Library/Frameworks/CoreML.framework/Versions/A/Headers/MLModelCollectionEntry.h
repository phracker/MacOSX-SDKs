//
//  MLModelCollectionEntry.h
//  CoreML
//
//  Copyright © 2019 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreML/MLExport.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 * MLModelCollectionEntry
 * Information about a model in a model collection.
 */
API_AVAILABLE(macos(11.0), ios(14.0))
API_UNAVAILABLE(tvos, watchos)
ML_EXPORT
@interface MLModelCollectionEntry : NSObject

@property (readonly, nonatomic) NSString *modelIdentifier;

@property (readonly, nonatomic) NSURL *modelURL;

- (BOOL)isEqualToModelCollectionEntry:(MLModelCollectionEntry *)entry;

- (instancetype)init NS_UNAVAILABLE;

+ (id)new NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
