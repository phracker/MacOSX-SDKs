//
//  CKMarkNotificationsReadOperation.h
//  CloudKit
//
//  Copyright (c) 2014 Apple Inc. All rights reserved.
//

#import <CloudKit/CKOperation.h>

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

CK_NEWLY_UNAVAILABLE("Marking notifications read is no longer supported.  Consider using CKDatabaseSubscription, CKFetchDatabaseChangesOperation, and CKFetchRecordZoneChangesOperation")
@interface CKMarkNotificationsReadOperation : CKOperation
@end

NS_HEADER_AUDIT_END(nullability, sendability)
