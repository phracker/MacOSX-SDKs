//
//  CKRecord.h
//  CloudKit
//
//  Copyright (c) 2014 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreLocation/CLLocation.h>
#import <CloudKit/CKAsset.h>
#import <CloudKit/CKReference.h>
#import <CloudKit/CKDefines.h>

@class CKRecordID, CKRecordZoneID;

NS_ASSUME_NONNULL_BEGIN

/* Use this constant for the recordType parameter when fetching User Records. */
CK_EXTERN NSString * const CKRecordTypeUserRecord NS_AVAILABLE(10_10, 8_0);

/* Use these keys in queries to match on the record's parent or share reference */
CK_EXTERN NSString * const CKRecordParentKey NS_AVAILABLE(10_12, 10_0);
CK_EXTERN NSString * const CKRecordShareKey NS_AVAILABLE(10_12, 10_0);

@protocol CKRecordValue <NSObject>
@end

NS_CLASS_AVAILABLE(10_10, 8_0)
@interface CKRecord : NSObject <NSSecureCoding, NSCopying>

- (instancetype)init NS_UNAVAILABLE;

/* These create the record in the default zone. */
- (instancetype)initWithRecordType:(NSString *)recordType;
- (instancetype)initWithRecordType:(NSString *)recordType recordID:(CKRecordID *)recordID;

- (instancetype)initWithRecordType:(NSString *)recordType zoneID:(CKRecordZoneID *)zoneID;

@property (nonatomic, readonly, copy) NSString *recordType;
@property (nonatomic, readonly, copy) CKRecordID *recordID;

/* Change tags are updated by the server to a unique value every time a record is modified.
   A different change tag necessarily means that the contents of the record are different. */
@property (nonatomic, readonly, copy, nullable) NSString *recordChangeTag;

/* This is a User Record recordID, identifying the user that created this record. */
@property (nonatomic, readonly, copy, nullable) CKRecordID *creatorUserRecordID;
@property (nonatomic, readonly, copy, nullable) NSDate *creationDate;

/* This is a User Record recordID, identifying the user that last modified this record. */
@property (nonatomic, readonly, copy, nullable) CKRecordID *lastModifiedUserRecordID;
@property (nonatomic, readonly, copy, nullable) NSDate *modificationDate;

/* 
    In addition to objectForKey: and setObject:forKey:, dictionary-style subscripting (record[key] and record[key] = value) can be used to get and set values.
    Acceptable value object classes are:
        CKReference
        CKAsset
        CLLocation
        NSData
        NSDate
        NSNumber
        NSString
        NSArray containing objects of any of the types above
 
    Any other classes will result in an exception with name NSInvalidArgumentException.

    Derived field keys are prefixed with '_'. Attempting to set a key prefixed with a '_' will result in an error.
 
    Key names roughly match C variable name restrictions. They must begin with an ASCII letter and can contain ASCII
     letters and numbers and the underscore character.
    The maximum key length is 255 characters.
*/
- (nullable __kindof id <CKRecordValue>)objectForKey:(NSString *)key;
- (void)setObject:(nullable __kindof id <CKRecordValue>)object forKey:(NSString *)key;
- (NSArray<NSString *> *)allKeys;

/* A special property that returns an array of token generated from all the string field values in the record.
   These tokens have been normalized for the current locale, so they are suitable for performing full-text searches. */
- (NSArray<NSString *> *)allTokens;

- (nullable __kindof id <CKRecordValue>)objectForKeyedSubscript:(NSString *)key;
- (void)setObject:(nullable __kindof id <CKRecordValue>)object forKeyedSubscript:(NSString *)key;

/* A list of keys that have been modified on the local CKRecord instance */
- (NSArray<NSString *> *)changedKeys;

/* CKRecord supports NSSecureCoding.  When you invoke
 -encodeWithCoder: on a CKRecord, it encodes all its values.  Including the record values you've set.
 If you want to store a CKRecord instance locally, AND you're already storing the record values locally,
 that's overkill.  In that case, you can use
 -encodeSystemFieldsWithCoder:.  This will encode all parts of a CKRecord except the record keys / values you
 have access to via the -changedKeys and -objectForKey: methods.
 If you use initWithCoder: to reconstitute a CKRecord you encoded via encodeSystemFieldsWithCoder:, then be aware that
 - any record values you had set on the original instance, but had not saved, will be lost
 - the reconstituted CKRecord's changedKeys will be empty
 */
- (void)encodeSystemFieldsWithCoder:(NSCoder *)coder;

/* The share property on a record can be set by creating a share using -[CKShare initWithRootRecord:].
 
 The share property on a record will be removed when the corresponding CKShare is deleted from the server. Send this record in the same batch as the share delete and this record's share property will be updated.
 
 Sharing is only supported in zones with the CKRecordZoneCapabilitySharing capability. The default zone does not support sharing.
 
 If any records have a parent reference to this record, they are implicitly shared alongside this record.
 
 Note that records in a hierarchy must only exist within one share. If a child record in a hierarchy already has a share reference set then you will get a CKErrorAlreadyShared error if you try to share any of that record's parents.
 
 Whenever possible, it is suggested that you construct your parent hierarchies such that you will only need to share the topmost record of that hierarchy.
*/
@property (nonatomic, readonly, copy, nullable) CKReference *share NS_AVAILABLE(10_12, 10_0);

/* Use a parent reference to teach CloudKit about the hierarchy of your records. This hierarchy of records will be shared if the share reference is set on a record.
 
 A parent record reference must have CKReferenceActionNone set. You can create a separate reference with CKReferenceActionDeleteSelf if you would like your hierarchy cleaned up when the parent record is deleted.
 
 The target of a parent reference must exist at save time - either already on the server, or part of the same CKModifyRecordsOperation batch.

 You are encouraged to set up the parent relationships as part of normal record saves, even if you're not planning on sharing records at this time.  
 This allows you to share and unshare a hierarchy of records at a later date by only modifying the "top level" record, setting or clearing its 'share' reference.
*/
@property (nonatomic, copy, nullable) CKReference *parent NS_AVAILABLE(10_12, 10_0);

/* Convenience wrappers around creating a CKReference to a parent record. The resulting CKReference will have action = CKReferenceActionNone */
- (void)setParentReferenceFromRecord:(nullable CKRecord *)parentRecord NS_AVAILABLE(10_12, 10_0);
- (void)setParentReferenceFromRecordID:(nullable CKRecordID *)parentRecordID NS_AVAILABLE(10_12, 10_0);

@end

@interface NSString (CKRecordValue) <CKRecordValue>
@end

@interface NSNumber (CKRecordValue) <CKRecordValue>
@end

@interface NSArray (CKRecordValue) <CKRecordValue>
@end

@interface NSDate (CKRecordValue) <CKRecordValue>
@end

@interface NSData (CKRecordValue) <CKRecordValue>
@end

@interface CKReference (CKRecordValue) <CKRecordValue>
@end

@interface CKAsset (CKRecordValue) <CKRecordValue>
@end

@interface CLLocation (CKRecordValue) <CKRecordValue>
@end

NS_ASSUME_NONNULL_END
