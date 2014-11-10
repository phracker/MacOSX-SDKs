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

/* Use this constant for the recordType parameter when fetching User Records. */
CK_EXTERN NSString * const CKRecordTypeUserRecord NS_AVAILABLE(10_10, 8_0);

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
@property (nonatomic, readonly, copy) NSString *recordChangeTag;

/* This is a User Record recordID, identifying the user that created this record. */
@property (nonatomic, readonly, copy) CKRecordID *creatorUserRecordID;
@property (nonatomic, readonly, copy) NSDate *creationDate;

/* This is a User Record recordID, identifying the user that last modified this record. */
@property (nonatomic, readonly, copy) CKRecordID *lastModifiedUserRecordID;
@property (nonatomic, readonly, copy) NSDate *modificationDate;

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
- (id)objectForKey:(NSString *)key;
- (void)setObject:(id <CKRecordValue>)object forKey:(NSString *)key;
- (NSArray /* NSString */ *)allKeys;

/* A special property that returns an array of token generated from all the string field values in the record.
   These tokens have been normalized for the current locale, so they are suitable for performing full-text searches. */
- (NSArray /* NSString */ *)allTokens;

- (id)objectForKeyedSubscript:(NSString *)key;
- (void)setObject:(id <CKRecordValue>)object forKeyedSubscript:(NSString *)key;

/* A list of keys that have been modified on the local CKRecord instance */
- (NSArray /* NSString */ *)changedKeys;

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
