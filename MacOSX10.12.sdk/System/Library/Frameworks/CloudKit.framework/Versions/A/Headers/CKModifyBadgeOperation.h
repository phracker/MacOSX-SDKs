//
//  CKModifyBadgeOperation.h
//  CloudKit
//
//  Copyright (c) 2014 Apple Inc. All rights reserved.
//

#import <CloudKit/CKOperation.h>

NS_ASSUME_NONNULL_BEGIN
NS_CLASS_AVAILABLE(10_10, 8_0)
@interface CKModifyBadgeOperation : CKOperation

- (instancetype)init NS_DESIGNATED_INITIALIZER;
- (instancetype)initWithBadgeValue:(NSUInteger)badgeValue;

@property (nonatomic, assign) NSUInteger badgeValue;

/*  This block is called when the operation completes.
    The [NSOperation completionBlock] will also be called if both are set. */
@property (nonatomic, copy, nullable) void (^modifyBadgeCompletionBlock)(NSError * _Nullable operationError);

@end
NS_ASSUME_NONNULL_END
