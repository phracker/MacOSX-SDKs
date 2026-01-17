//
//  CKModifyBadgeOperation.h
//  CloudKit
//
//  Copyright (c) 2014 Apple Inc. All rights reserved.
//

#import <CloudKit/CKOperation.h>

NS_ASSUME_NONNULL_BEGIN
API_DEPRECATED("No longer supported, will cease working at some point in the future", macos(10.10, 10.13), ios(8.0, 11.0), tvos(9.0, 11.0), watchos(3.0, 4.0))
@interface CKModifyBadgeOperation : CKOperation

- (instancetype)init NS_DESIGNATED_INITIALIZER;
- (instancetype)initWithBadgeValue:(NSUInteger)badgeValue;

@property (nonatomic, assign) NSUInteger badgeValue;

/*  This block is called when the operation completes.
    The [NSOperation completionBlock] will also be called if both are set. */
@property (nonatomic, copy, nullable) void (^modifyBadgeCompletionBlock)(NSError * _Nullable operationError);

@end
NS_ASSUME_NONNULL_END
