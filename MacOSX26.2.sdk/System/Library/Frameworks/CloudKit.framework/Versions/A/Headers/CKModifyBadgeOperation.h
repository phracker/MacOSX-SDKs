//
//  CKModifyBadgeOperation.h
//  CloudKit
//
//  Copyright (c) 2014 Apple Inc. All rights reserved.
//

#import <CloudKit/CKOperation.h>

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

CK_NEWLY_UNAVAILABLE("Modifying badge counts is no longer supported")
@interface CKModifyBadgeOperation : CKOperation
@end

NS_HEADER_AUDIT_END(nullability, sendability)
