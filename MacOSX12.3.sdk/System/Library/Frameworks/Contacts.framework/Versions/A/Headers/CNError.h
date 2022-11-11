//
//  CNError.h
//  Contacts
//
//  Copyright (c) 2015–2019 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <Contacts/ContactsDefines.h>

CONTACTS_EXTERN NSString * const CNErrorDomain NS_AVAILABLE(10_11, 9_0);

typedef NS_ENUM(NSInteger, CNErrorCode)
{
    CNErrorCodeCommunicationError = 1,
    CNErrorCodeDataAccessError = 2,
    
    CNErrorCodeAuthorizationDenied = 100,
    CNErrorCodeNoAccessableWritableContainers NS_ENUM_AVAILABLE(10_13_3, 11_3) = 101,
    CNErrorCodeUnauthorizedKeys API_AVAILABLE(macos(10.14), ios(13.0), watchos(6.0)) = 102,
    CNErrorCodeFeatureDisabledByUser API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0)) = 103,

    CNErrorCodeRecordDoesNotExist = 200,
    CNErrorCodeInsertedRecordAlreadyExists = 201,
    CNErrorCodeContainmentCycle = 202,
    CNErrorCodeContainmentScope = 203,
    CNErrorCodeParentRecordDoesNotExist = 204,
    CNErrorCodeRecordIdentifierInvalid = 205,
    CNErrorCodeRecordNotWritable API_AVAILABLE(macos(10.14), ios(13.0), watchos(6.0)) = 206,
    CNErrorCodeParentContainerNotWritable API_AVAILABLE(macos(10.14), ios(13.0), watchos(6.0)) = 207,
    
    CNErrorCodeValidationMultipleErrors = 300,
    CNErrorCodeValidationTypeMismatch = 301,
    CNErrorCodeValidationConfigurationError = 302,

    CNErrorCodePredicateInvalid = 400,
    
    CNErrorCodePolicyViolation = 500,
    
    CNErrorCodeClientIdentifierInvalid = 600,
    CNErrorCodeClientIdentifierDoesNotExist = 601,
    CNErrorCodeClientIdentifierCollision = 602,
    CNErrorCodeChangeHistoryExpired = 603,
    CNErrorCodeChangeHistoryInvalidAnchor = 604,
    CNErrorCodeChangeHistoryInvalidFetchRequest = 605,

    CNErrorCodeVCardMalformed NS_ENUM_AVAILABLE(10_13, 11_0) = 700,
    CNErrorCodeVCardSummarizationError NS_ENUM_AVAILABLE(10_14, 12_0) = 701,
    
}  NS_ENUM_AVAILABLE(10_11, 9_0);

/*! When available an array of one or more CNContact, CNGroup, CNContainer, CNSaveRequest, or CNFetchRequest objects for which the error code applies. */
CONTACTS_EXTERN NSString * const CNErrorUserInfoAffectedRecordsKey NS_AVAILABLE(10_11, 9_0);

/*! When available an array of one or more NSString objects for which the error code applies. */
CONTACTS_EXTERN NSString * const CNErrorUserInfoAffectedRecordIdentifiersKey NS_AVAILABLE(10_11, 9_0);

/*! An array of NSErrors for CNErrorCodeValidationMultipleErrors. */
CONTACTS_EXTERN NSString * const CNErrorUserInfoValidationErrorsKey NS_AVAILABLE(10_11, 9_0);

/*! An array of key paths associated with a given error. For validation errors this will contain key paths to specific object properties. */
CONTACTS_EXTERN NSString * const CNErrorUserInfoKeyPathsKey NS_AVAILABLE(10_11, 9_0);
