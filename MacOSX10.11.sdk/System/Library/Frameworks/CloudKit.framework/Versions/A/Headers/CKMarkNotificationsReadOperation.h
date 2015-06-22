//
//  CKMarkNotificationsReadOperation.h
//  CloudKit
//
//  Copyright (c) 2014 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CloudKit/CKOperation.h>

@class CKNotificationID;

NS_ASSUME_NONNULL_BEGIN
NS_CLASS_AVAILABLE(10_10, 8_0)
@interface CKMarkNotificationsReadOperation : CKOperation

- (instancetype)init NS_UNAVAILABLE;

- (instancetype)initWithNotificationIDsToMarkRead:(NSArray <CKNotificationID *> *)notificationIDs NS_DESIGNATED_INITIALIZER;

@property (nonatomic, copy) NSArray <CKNotificationID *> *notificationIDs;

@property (nonatomic, copy, nullable) void (^markNotificationsReadCompletionBlock)(NSArray <CKNotificationID *> * __nullable notificationIDsMarkedRead, NSError * __nullable operationError);

@end
NS_ASSUME_NONNULL_END
