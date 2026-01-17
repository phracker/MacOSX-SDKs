//
//  HKDocumentQuery.h
//  HealthKit
//
//  Copyright (c) 2016 Apple Inc. All rights reserved.
//

#include <HealthKit/HKQuery.h>

NS_ASSUME_NONNULL_BEGIN

@class HKDocumentSample;
@class HKDocumentType;

/*!
 @class         HKDocumentQuery
 @abstract      A concrete subclass of HKQuery that provides an interface to retrieve documents from the Health store.
 
 */
HK_EXTERN API_AVAILABLE(ios(10.0))
@interface HKDocumentQuery : HKQuery

/*!
 @property      limit
 @abstract      The maximum number of documents the receiver will return upon completion.
 */
@property (readonly) NSUInteger limit;

/*!
 @property      sortDescriptors
 @abstract      An array of NSSortDescriptors.
 */
@property (readonly, copy, nullable) NSArray<NSSortDescriptor *> *sortDescriptors;

/*!
 @property      includeDocumentData
 @abstract      The XML content for documents may be large.  This property can be used to control whether the query
                returns the XML content for each record.
 */
@property (readonly) BOOL includeDocumentData;

/*!
 @method        initWithDocumentType:predicate:limit:sortDescriptors:includeDocumentData:resultsHandler:
 @abstract      Returns a query that will retrieve HKDocumentSamples matching the given predicate.
 
 @param         documentType        The type of document to retreive.
 @param         predicate           The predicate which documents should match.
 @param         limit               The maximum number of documents to return.  Pass HKObjectQueryNoLimit for no limit.
 @param         sortDescriptors     The sort descriptors to use to order the resulting documents.
 @param         includeDocumentData If true, the document content will be returned with the HKDocumentSample instance.
                                    This option can be used to limit the size of the content returned since the content
                                    may be large.
 @param         resultsHandler      The block that will receive query results.  Results will be returned incrementally
                                    through several calls to this block.  When there are no more results, the done 
                                    parameter will be YES and the results array will be empty.  If results is nil, then
                                    an error has occurred and the error parameter will be set.  Delivery of results can
                                    be stopped by calling HKHealthStore's stopQuery: method.

 @discussion    Health documents may contain sensitive data that a user may want to control explicitly. HKDocumentSample
                objects returned by HKSampleQuery and HKAnchoredObjectQuery do not include this data (i.e., the document
                property is nil).  This query can be used to retrieve fully populated HKDocumentSample instances.  The 
                query will prompt the user to authorize your app to read individual documents.  The query will then
                return the documents that your app is authorized to read. The user will only be asked to authorize your
                app to read documents that are new since the last time an HKDocumentQuery was executed.
 */
- (instancetype)initWithDocumentType:(HKDocumentType *)documentType
                           predicate:(nullable NSPredicate *)predicate
                               limit:(NSUInteger)limit
                     sortDescriptors:(nullable NSArray<NSSortDescriptor *> *)sortDescriptors
                 includeDocumentData:(BOOL)includeDocumentData
                      resultsHandler:(void(^)(HKDocumentQuery *query,
                                              NSArray<__kindof HKDocumentSample *> * _Nullable results,
                                              BOOL done,
                                              NSError * _Nullable error))resultsHandler;


@end

NS_ASSUME_NONNULL_END
