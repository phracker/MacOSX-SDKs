/*
	CoreDataErrors.h
	Core Data
	Copyright (c) 2004-2005 Apple Computer, Inc.
	All rights reserved.
 */

#import <Foundation/NSObject.h>

#if MAC_OS_X_VERSION_10_4 <= MAC_OS_X_VERSION_MAX_ALLOWED

/* NSError codes for Core Data added errors in NSCocoaErrorDomain. Foundation error codes can be found in <Foundation/FoundationErrors.h>. AppKit error codes can be found in <AppKit/AppKitErrors.h>.
*/

#import <CoreData/CoreDataDefines.h>

// User info keys for errors created by Core Data:
COREDATA_EXTERN NSString * const NSDetailedErrorsKey;           // if multiple validation errors occur in one operation, they are collected in an array and added with this key to the "top-level error" of the operation

COREDATA_EXTERN NSString * const NSValidationObjectErrorKey;    // object that failed to validate for a validation error
COREDATA_EXTERN NSString * const NSValidationKeyErrorKey;       // key that failed to validate for a validation error
COREDATA_EXTERN NSString * const NSValidationPredicateErrorKey; // for predicate-based validation, the predicate for the condition that failed to validate
COREDATA_EXTERN NSString * const NSValidationValueErrorKey;     // if non-nil, the value for the key that failed to validate for a validation error

COREDATA_EXTERN NSString * const NSAffectedStoresErrorKey;      // stores prompting an error
COREDATA_EXTERN NSString * const NSAffectedObjectsErrorKey;     // objects prompting an error

enum {
    NSManagedObjectValidationError                   = 1550,   // generic validation error
    NSValidationMultipleErrorsError                  = 1560,   // generic message for error containing multiple validation errors
    NSValidationMissingMandatoryPropertyError        = 1570,   // non-optional property with a nil value
    NSValidationRelationshipLacksMinimumCountError   = 1580,   // to-many relationship with too few destination objects
    NSValidationRelationshipExceedsMaximumCountError = 1590,   // bounded, to-many relationship with too many destination objects
    NSValidationRelationshipDeniedDeleteError        = 1600,   // some relationship with NSDeleteRuleDeny is non-empty
    NSValidationNumberTooLargeError                  = 1610,   // some numerical value is too large
    NSValidationNumberTooSmallError                  = 1620,   // some numerical value is too small
    NSValidationDateTooLateError                     = 1630,   // some date value is too late
    NSValidationDateTooSoonError                     = 1640,   // some date value is too soon
    NSValidationInvalidDateError                     = 1650,   // some date value fails to match date pattern
    NSValidationStringTooLongError                   = 1660,   // some string value is too long
    NSValidationStringTooShortError                  = 1670,   // some string value is too short
    NSValidationStringPatternMatchingError           = 1680,   // some string value fails to match some pattern
    
    NSManagedObjectContextLockingError               = 132000, // can't acquire a lock in a managed object context
    NSPersistentStoreCoordinatorLockingError         = 132010, // can't acquire a lock in a persistent store coordinator
    
    NSManagedObjectReferentialIntegrityError         = 133000, // attempt to fire a fault pointing to an object that does not exist (we can see the store, we can't see the object)
    NSManagedObjectExternalRelationshipError         = 133010, // an object being saved has a relationship containing an object from another store
    NSManagedObjectMergeError                        = 133020, // merge policy failed - unable to complete merging
    
    NSPersistentStoreInvalidTypeError                = 134000, // unknown persistent store type/format/version
    NSPersistentStoreTypeMismatchError               = 134010, // returned by persistent store coordinator if a store is accessed that does not match the specified type
    NSPersistentStoreIncompatibleSchemaError         = 134020, // store returned an error for save operation (database level errors ie missing table, no permissions)
    NSPersistentStoreSaveError                       = 134030, // store returned an error for save operation (database level errors ie missing table, no permissions)
    NSPersistentStoreIncompleteSaveError             = 134040  // one or more of the stores returned an error during save (stores/objects that failed will be in userInfo)
};

#endif
