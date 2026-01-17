//
//  CKDatabaseOperation.h
//  CloudKit
//
//  Copyright (c) 2014 Apple Inc. All rights reserved.
//

#import <CloudKit/CKOperation.h>

@class CKDatabase;

NS_CLASS_AVAILABLE(10_10, 8_0)
@interface CKDatabaseOperation : CKOperation

/* If no database is set, [self.container privateCloudDatabase] is used. */
@property (nonatomic, strong) CKDatabase *database;

@end
