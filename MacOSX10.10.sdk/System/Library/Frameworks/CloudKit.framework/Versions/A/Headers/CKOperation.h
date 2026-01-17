//
//  CKOperation.h
//  CloudKit
//
//  Copyright (c) 2014 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

@class CKContainer;

NS_CLASS_AVAILABLE(10_10, 8_0)
@interface CKOperation : NSOperation

- (instancetype)init NS_DESIGNATED_INITIALIZER;

/* All CKOperations default to self.qualityOfService == NSOperationQualityOfServiceUserInitiated */

/* If no container is set, [CKContainer defaultContainer] is used */
@property (nonatomic, strong) CKContainer *container;

/* If set, network traffic will happen on a background NSURLSession.
 Defaults to (NSOperationQualityOfServiceBackground == self.qualityOfService) */
@property (nonatomic, assign) BOOL usesBackgroundSession;

/* Defaults to YES */
@property (nonatomic, assign) BOOL allowsCellularAccess;

@end


