//
//  HKCDADocumentSample.h
//  HealthKit
//
//  Copyright © 2015 Apple. All rights reserved.
//
//  HealthKit support for storing and retrieving
//  Consolidated Clinical Document records.
//

#import <HealthKit/HKDocumentSample.h>

NS_ASSUME_NONNULL_BEGIN

@class HKCDADocument;

/*!
 @class         HKCDADocumentSample
 @abstract      A sample object representing a CDA document.
 */
HK_EXTERN API_AVAILABLE(ios(10.0)) API_UNAVAILABLE(watchos)
@interface HKCDADocumentSample : HKDocumentSample

/*!
 @property      document
 @abstract      The contents of the document.
 @discussion    Access to each CDA instance must be authorized by the user in order for the document data to be
                accessible to an app.  The authorization request occurs the first time a document matches the predicate
                of an executed HKDocumentQuery.  This property will always be nil if the sample is returned by an
                HKSampleQuery or an HKAnchoredObjectQuery.
 */
@property (readonly, nullable) HKCDADocument *document;

/*!
 @method                CDADocumentSampleWithData:startDate:endDate:device:metadata:validationError:
 @abstract              Creates a new document sample with the specified attributes.
 @param documentData    Document contents in an XML format that meets the CDA standard.
 @param startDate       The start date for the document.
 @param endDate         The end date for the document.
 @param metadata        Metadata for the document.
 @param validationError The XML content will be validated against the standard for CDA content.  If that validation
                        fails, then this parameter will be set with the relavant error.  Detailed information about the
                        failure may be obtained by examining the value for the HKDetailedCDAValidationErrorKey key of
                        the NSError's userInfo dictionary.
 @return                The new instance or nil if the documentData does not pass validation.
 @discussion            Attributes of the document, such as title, patient name, etc. will be extracted automatically
                        from the document content.
 */
+ (nullable instancetype)CDADocumentSampleWithData:(NSData *)documentData
                                         startDate:(NSDate *)startDate
                                           endDate:(NSDate *)endDate
                                          metadata:(nullable NSDictionary<NSString *, id> *)metadata
                                   validationError:(NSError **)validationError __WATCHOS_UNAVAILABLE;

@end

HK_EXTERN API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(watchos)
@interface HKCDADocument : NSObject

/*!
 @property  documentData
 @abstract  The CDA document content in XML format as specified in the CDA standard. This may be nil if the
            includeDocumentData option in HKDocumentQuery is specified as NO.
 */
@property (readonly, copy, nullable) NSData *documentData API_AVAILABLE(ios(10.0));

/*!
 @property      title
 @abstract      The title of the document.
 @discussion    This property is extracted automatically from the document.
 */
@property (readonly, copy) NSString *title API_AVAILABLE(ios(10.0));

/*!
 @property      patientName
 @abstract      The name of the patient receiving treatment.
 @discussion    This property is extracted automatically from the document.
 */
@property (readonly, copy) NSString *patientName API_AVAILABLE(ios(10.0));

/*!
 @property      authorName
 @abstract      The person responsible for authoring the document.  Usually, this is the treating physician.
 @discussion    This property is extracted automatically from the document.
 */
@property (readonly, copy) NSString *authorName API_AVAILABLE(ios(10.0));

/*!
 @property      custodianName
 @abstract      The organization responsible for the document.  This is usually the treating institution name.
 @discussion    This property is extracted automatically from the document.
 */
@property (readonly, copy) NSString *custodianName API_AVAILABLE(ios(10.0));

@end

/*!
 @constant  HKPredicateKeyPathCDATitle
 */
HK_EXTERN NSString * const HKPredicateKeyPathCDATitle API_AVAILABLE(ios(10.0), watchos(3.0));

/*!
 @constant  HKPredicateKeyPathCDAPatientName
 */
HK_EXTERN NSString * const HKPredicateKeyPathCDAPatientName API_AVAILABLE(ios(10.0), watchos(3.0));

/*!
 @constant  HKPredicateKeyPathCDAAuthorName
 */
HK_EXTERN NSString * const HKPredicateKeyPathCDAAuthorName API_AVAILABLE(ios(10.0), watchos(3.0));

/*!
 @constant  HKPredicateKeyPathCDACustodianName
 */
HK_EXTERN NSString * const HKPredicateKeyPathCDACustodianName API_AVAILABLE(ios(10.0), watchos(3.0));

/*!
 @constant      HKDetailedCDAValidationErrorKey
 @discussion    This may be used with the validationError parameter of
                CDADocumentSampleWithData:startDate:endDate:device:metadata:validationError: to obtain a detailed
                description of the validation errors encountered when creating a CDA document.
 */
HK_EXTERN NSString * const HKDetailedCDAValidationErrorKey API_AVAILABLE(ios(10.0), watchos(3.0));

NS_ASSUME_NONNULL_END
