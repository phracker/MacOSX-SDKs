//
//  CNFetchResult.h
//  Contacts
//
//  Copyright (c) 2019 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@class CNChangeHistoryAnchor;

API_AVAILABLE(macosx(10.15), ios(13.0), watchos(6.0))
@interface CNFetchResult<ValueType> : NSObject

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new  NS_UNAVAILABLE;

@property (nonatomic, readonly, strong) ValueType value;

@property (nonatomic, readonly, copy) NSData * currentHistoryToken;

@end

NS_ASSUME_NONNULL_END
