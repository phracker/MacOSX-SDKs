//
//  CKQuery.h
//  CloudKit
//
//  Copyright (c) 2014 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

#import <CloudKit/CKRecord.h>

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

/*! @class CKQuery
 *
 *  @discussion Only AND compound predicates are allowed.
 *
 *  Key names must begin with either an upper or lower case character ([a-zA-Z]) and may be followed by characters, numbers, or underscores ([0-9a-zA-Z_]). Keypaths may only resolve to the currently evaluated object, so the '.' character is not allowed in key names.
 *
 *  A limited subset of classes are allowed as predicate arguments:
 *  - NSString
 *  - NSDate
 *  - NSData
 *  - NSNumber
 *  - NSArray
 *  - CKReference
 *  - CKRecord
 *  - CLLocation
 *
 * Any other class as an argument will result in an error when executing the query.
 */
API_AVAILABLE(macos(10.10), ios(8.0), watchos(3.0))
CK_SUBCLASSING_DEPRECATED // should not be subclassed, or Sendable may no longer apply
// NS_SWIFT_SENDABLE on macos(14.0), ios(17.0), tvos(17.0), watchos(10.0)
@interface CKQuery : NSObject <NSSecureCoding, NSCopying>

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)initWithCoder:(NSCoder *)aDecoder NS_DESIGNATED_INITIALIZER;

/*! Use @code [NSPredicate predicateWithValue:YES] / NSPredicate(value: true) @endcode if you want to query for all records of a given type. */
- (instancetype)initWithRecordType:(CKRecordType)recordType predicate:(NSPredicate *)predicate NS_DESIGNATED_INITIALIZER;

@property (readonly, copy) CKRecordType recordType;
@property (readonly, copy) NSPredicate *predicate;

@property (nullable, copy) NSArray<NSSortDescriptor *> *sortDescriptors;

@end

NS_HEADER_AUDIT_END(nullability, sendability)
