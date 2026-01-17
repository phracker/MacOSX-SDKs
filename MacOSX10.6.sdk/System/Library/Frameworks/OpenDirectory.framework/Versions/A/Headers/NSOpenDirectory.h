/*
 * Copyright (c) 2005-2009 Apple Inc. All rights reserved.
 *
 * @APPLE_LICENSE_HEADER_START@
 * 
 * This file contains Original Code and/or Modifications of Original Code
 * as defined in and that are subject to the Apple Public Source License
 * Version 2.0 (the 'License'). You may not use this file except in
 * compliance with the License. Please obtain a copy of the License at
 * http://www.opensource.apple.com/apsl/ and read it before using this
 * file.
 * 
 * The Original Code and all software distributed under the License are
 * distributed on an 'AS IS' basis, WITHOUT WARRANTY OF ANY KIND, EITHER
 * EXPRESS OR IMPLIED, AND APPLE HEREBY DISCLAIMS ALL SUCH WARRANTIES,
 * INCLUDING WITHOUT LIMITATION, ANY WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE, QUIET ENJOYMENT OR NON-INFRINGEMENT.
 * Please see the License for the specific language governing rights and
 * limitations under the License.
 * 
 * @APPLE_LICENSE_HEADER_END@
 */

/*!
    @header     NSOpenDirectory
    @abstract   NSOpenDirectory is a toll-free bridged version of the CF-based OD objects
    @discussion The goal of these APIs is to supply a common library with Cocoa-based APIs to manipulate data
                in Open Directory supported Directories.  All API are completely thread safe due to the
                nature of shared objects implementation.
*/

#import <AvailabilityMacros.h>
#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_6

#import <Foundation/Foundation.h>
#import <CFOpenDirectory/CFOpenDirectoryErrors.h>
#import <CFOpenDirectory/CFOpenDirectoryTypes.h>
#import <CFOpenDirectory/CFOpenDirectoryConstants.h>

@class ODSession, ODNode, ODRecord, ODQuery;

@protocol ODQueryDelegate;

#pragma mark -
#pragma mark Const

/*!
    @const      ODSessionProxyAddress
    @abstract   the address to connect to via proxy, used when making the options dictionary
    @discussion the address to connect to via proxy, used when making the options dictionary
*/
FOUNDATION_EXPORT NSString *const ODSessionProxyAddress;

/*!
    @const      ODSessionProxyPort
    @abstract   the port to connect to via proxy, used when making the options dictionary
    @discussion the port to connect to via proxy, used when making the options dictionary.  This parameter
                is optional and should not be passed normally.
*/
FOUNDATION_EXPORT NSString *const ODSessionProxyPort;

/*!
    @const      ODSessionProxyUsername
    @abstract   the username to connect with via proxy, used when making the options dictionary
    @discussion the username to connect with via proxy, used when making the options dictionary
*/
FOUNDATION_EXPORT NSString *const ODSessionProxyUsername;

/*!
    @const      ODSessionProxyPassword
    @abstract   the password to connect with via proxy, used when making the options dictionary
    @discussion the password to connect with via proxy, used when making the options dictionary
*/
FOUNDATION_EXPORT NSString *const ODSessionProxyPassword;

/*!
    @const      ODFrameworkErrorDomain
    @abstract   the error domain for the OpenDirectory framework
    @discussion the error domain for the OpenDirectory framework
*/
FOUNDATION_EXPORT NSString *const ODFrameworkErrorDomain;

#pragma mark -

/*!
    @class       ODQuery
    @abstract    ODQuery object used to query Open Directory for types of objects
    @discussion  ODQuery object used to query Open Directory for types of objects
*/
@interface ODQuery : NSObject
{
    void        *_internal;
}

/*!
    @method     queryWithNode: forRecordTypes: attribute: matchType: queryValues: returnAttributes: maximumResults: error:
    @abstract   Creates an autoreleased query with the node using the parameters provided
    @discussion Creates an autoreleased query with the node using the supplied query parameters.  Some parameters
                can either be NSString or NSData or an NSArray of either NSString or NSData.  Passing nil for 
                returnAttributes is equivalent to passing kODAttributeTypeStandardOnly.  outError is optional parameter,
                nil can be passed if error details are not needed.  
*/
+ (ODQuery *)queryWithNode:(ODNode *)inNode forRecordTypes:(id)inRecordTypeOrList attribute:(ODAttributeType)inAttribute
                 matchType:(ODMatchType)inMatchType queryValues:(id)inQueryValueOrList 
          returnAttributes:(id)inReturnAttributeOrList maximumResults:(NSInteger)inMaximumResults
                     error:(NSError **)outError;

/*!
    @method     initWithNode: forRecordTypes: attribute: matchType: queryValues: returnAttributes: maximumResults: error:
    @abstract   Creates a query with the node using the parameters provided
    @discussion Creates a query with the node using the supplied query parameters.  Some parameters
                can either be NSString or NSData or an NSArray of either NSString or NSData.  Passing nil for 
                returnAttributes is equivalent to passing kODAttributeTypeStandardOnly. outError is optional parameter,
                nil can be passed if error details are not needed.
*/
- (id)initWithNode:(ODNode *)inNode forRecordTypes:(id)inRecordTypeOrList attribute:(ODAttributeType)inAttribute
         matchType:(ODMatchType)inMatchType queryValues:(id)inQueryValueOrList 
  returnAttributes:(id)inReturnAttributeOrList maximumResults:(NSInteger)inMaximumResults error:(NSError **)outError;

/*!
    @method     resultsAllowingPartial: error:
    @abstract   Returns results from a provided ODQuery synchronously
    @discussion Returns results from a provided ODQuery synchronously.  Passing NO to inAllowPartialResults
                will block the call until all results are returned or an error occurs.  YES can be passed at any time
                even if previous calls were made with NO.  outError is optional parameter, nil can be passed if error 
                details are not needed.
*/
- (NSArray *)resultsAllowingPartial:(BOOL)inAllowPartialResults error:(NSError **)outError;

/*!
    @method     delegate
    @abstract   Returns the currently set delegate
    @discussion Returns the current delegate set for this ODQuery
*/
/*!
    @method     setDelegate:
    @abstract   Sets a delegate to receive results from the NSRunLoop-based asynchronous results
    @discussion Sets the delegate provided to receive messages from NSRunLoop-based asynchronous results.
*/
@property (nonatomic, readwrite, assign) id <ODQueryDelegate> delegate;

/*!
    @method     scheduleInRunLoop: forMode:
    @abstract   Adds the query object to the specified NSRunLoop to receive asynchronous results
    @discussion Adds the query object to the specified NSRunLoop to receive asynchronous results.  A delegate must be set
                in advance otherwise results may be lost due to the lack of a receiver.
*/
- (void)scheduleInRunLoop:(NSRunLoop *)inRunLoop forMode:(NSString *)inMode;

/*!
    @method     removeFromRunLoop: forMode:
    @abstract   Removes the query object from the specified NSRunLoop
    @discussion Removes the query object from the specified NSRunLoop.
*/
- (void)removeFromRunLoop:(NSRunLoop *)inRunLoop forMode:(NSString *)inMode;

/*!
    @method     synchronize
    @abstract   Will dispose of any results and restart the query.
    @discussion Will dispose of any results and restart the query for subsequent resultsAllowingPartial: calls.  If the query
                is currently scheduled on a RunLoop, then the delegate will be called with inResults == nil and
                [inError code] == kODErrorQuerySynchronize and [inError domain] == ODFrameworkErrorDomain, signifying that
                all existing results should be thrown away in preparation for new results.
*/
- (void)synchronize;

/*!
    @property   operationQueue
    @abstract   The NSOperationQueue on which asynchronous results are delivered to the delegate.
    @discussion The NSOperationQueue on which asynchronous results are delivered to the delegate.
 */
@property (readwrite, retain) NSOperationQueue * operationQueue;

@end

#pragma mark

/*!
    @category    ODQueryDelegate
    @abstract    The delegate method for receiving query results from the NSRunLoop-based queries
    @discussion  The delegate method called as results are returned from an NSRunLoop-based query.  These results are only partial
                 and delegate is called repeatedly as results are available.  The incoming result must be retained or copied.  The 
                 array will be released by the NSRunLoop upon return.  Incoming results do not include previous results,
                 only the most resent results are returned.  inResults can be nil if an error occurs or the query is complete.  If 
                 inResults and inError are nil then the query has completed.
*/
@protocol ODQueryDelegate <NSObject>
@required
- (void)query:(ODQuery *)inQuery foundResults:(NSArray *)inResults error:(NSError *)inError;
@end

#pragma mark -

/*!
    @class       ODSession
    @abstract    Class used for ODSession setup
    @discussion  ODSession class can be manually instantiated and passed to ODNode.  Typically
                 API callers can just pass ODSessionDefault to ODNode object creation when a specific
                 one is not needed.
*/
@interface ODSession : NSObject
{
    void    *_internal;
}

/*!
    @method     defaultSession
    @abstract   Returns a shared instance of a local ODSession
    @discussion Returns a shared instance of a local ODSession.  This can be used for most situations unless
                more control is needed over the session.
*/
+ (id)defaultSession;

/*!
    @method     sessionWithOptions: error:
    @abstract   Creates an autoreleased instance of ODSession directed over Proxy to another host
    @discussion Creates an autoreleased instance of ODSession directed over Proxy to another host.  nil
                can be passed for no options. outError is optional parameter, nil can be passed if error
                details are not needed.  Options include:

                If proxy is required then a dictionary with keys should be:
                            Key                             Value
                    ODSessionProxyAddress        NSString(hostname or IP)
                    ODSessionProxyPort           NSNumber(IP port, should not be set as it will default)
                    ODSessionProxyUsername       NSString(username)
                    ODSessionProxyPassword       NSString(password)
*/
+ (id)sessionWithOptions:(NSDictionary *)inOptions error:(NSError **)outError;

/*!
    @method     initWithOptions: error:
    @abstract   Creates an instance of ODSession directed over Proxy to another host
    @discussion Creates an instance of ODSession directed over Proxy to another host.  nil can be
                passed for no options. outError is optional parameter, nil can be passed if error
                details are not needed. Options include:
     
                If proxy is required then a dictionary with keys should be:
                            Key                             Value
                    ODSessionProxyAddress        NSString(hostname or IP)
                    ODSessionProxyPort           NSNumber(IP port, should not be set as it will default)
                    ODSessionProxyUsername       NSString(username)
                    ODSessionProxyPassword       NSString(password)
*/
- (id)initWithOptions:(NSDictionary *)inOptions error:(NSError **)outError;

/*!
    @method     nodeNamesAndReturnError:
    @abstract   Returns the node names that are registered on this ODSession
    @discussion Returns the node names that are registered on this ODSession.  outError can be nil if
                error details are not needed.
*/
- (NSArray *)nodeNamesAndReturnError:(NSError **)outError;

@end

#pragma mark -

/*!
    @class       ODNode
    @abstract    This class is used to work with a Node in Directory Service
    @discussion  This class is used to work with a Node in Directory Service.
*/
@interface ODNode : NSObject
{
    void    *_internal;
}

/*!
    @method     nodeWithSession: type: error:
    @abstract   autoreleased instance of an ODNode with a provided ODSession and ODNodeType
    @discussion autoreleased instance of an ODNode with a provided ODSession and ODNodeType.  outError is 
                optional parameter, nil can be passed if error details are not needed.
*/
+ (id)nodeWithSession:(ODSession *)inSession type:(ODNodeType)inType error:(NSError **)outError;

/*!
    @method     nodeWithSession: name: error:
    @abstract   autoreleased instance of an ODNode with a provided ODSession and node name
    @discussion autoreleased instance of an ODNode with a provided ODSession and node name.  outError is 
                optional parameter, nil can be passed if error details are not needed.
*/
+ (id)nodeWithSession:(ODSession *)inSession name:(NSString *)inName error:(NSError **)outError;

/*!
    @method     initWithSession: type: error:
    @abstract   initialize instance of an ODNode with a provided ODSession and ODNodeType
    @discussion initialize instance of an ODNode with a provided ODSession and ODNodeType.  outError is 
                optional parameter, nil can be passed if error details are not needed.
*/
- (id)initWithSession:(ODSession *)inSession type:(ODNodeType)inType error:(NSError **)outError;

/*!
    @method     initWithSession: name: error:
    @abstract   initialize instance of an ODNode with a provided ODSession and node name
    @discussion initialize instance of an ODNode with a provided ODSession and node name.  outError is optional
                parameter, nil can be passed if error details are not needed.
*/
- (id)initWithSession:(ODSession *)inSession name:(NSString *)inName error:(NSError **)outError;

/*!
    @method     subnodeNamesAndReturnError:
    @abstract   Returns NSArray of node names for this node, which may contain sub-nodes or search policy nodes
    @discussion Returns NSArray of node names for this node, which may contain sub-nodes or search policy nodes.
                Commonly used with Search policy nodes.  outError is optional parameter, nil can be passed if error
                details are not needed.
*/
- (NSArray *)subnodeNamesAndReturnError:(NSError **)outError;

/*!
    @method     unreachableSubnodeNamesAndReturnError:
    @abstract   Will return NSArray of names of subnodes that are not currently reachable.
    @discussion Will return NSArray of names of subnodes that are not currently reachable.  Commonly used with Search policy 
                nodes to determine if any nodes are currently unreachable, but may also return other subnodes if the
                Open Directory plugin supports.  outError is optional parameter, nil can be passed if error details are not needed.
*/
- (NSArray *)unreachableSubnodeNamesAndReturnError:(NSError **)outError;

/*!
    @method     nodeName
    @abstract   Returns the currently open Node name for this instance of ODNode
    @discussion Returns the currently open Node name for this instance of ODNode
*/
@property (nonatomic, readonly, copy) NSString * nodeName;

/*!
    @method     nodeDetails: error:
    @abstract   Returns a dictionary of information about the instance of ODNode
    @discussion Returns a dictionary of information about the instance of ODNode.  Details such as Trust information
                \@"dsAttrTypeStandard:TrustInformation" or other Node details can be retrieved.  outError is optional parameter,
                nil can be passed if error details are not needed.
                
*/
- (NSDictionary *)nodeDetailsForKeys:(NSArray *)inKeys error:(NSError **)outError;

/*!
    @method     supportedRecordTypesAndReturnError:
    @abstract   Returns a NSArray of the record types supported by this node.
    @discussion Returns a NSArray of the record types supported by this node.  If node does not support the check
                then all possible types will be returned.  outError is optional parameter, nil can be passed if error details
                are not needed.
*/
- (NSArray *)supportedRecordTypesAndReturnError:(NSError **)outError;

/*!
    @method     supportedAttributesForRecordType: error:
    @abstract   Will return a list of attribute types supported for that attribute if possible
    @discussion Will return a list of attribute types supported for that attribute if possible.  If no specific
                types are available, then all possible values will be returned instead.  outError is optional parameter,
                nil can be passed if error details are not needed.
*/
- (NSArray *)supportedAttributesForRecordType:(ODRecordType)inRecordType error:(NSError **)outError;

/*!
    @method     setCredentialsWithRecordType: recordName: password: error:
    @abstract   Sets the credentials for interaction with the ODNode
    @discussion Sets the credentials for interaction with the ODNode.  Record references, etc. will use these credentials
                to query or change data.  Setting the credentials on a node referenced by other OD object types will
                change the credentials for all for all references.  outError is optional parameter, nil can be passed if error
                details are not needed.
*/
- (BOOL)setCredentialsWithRecordType:(ODRecordType)inRecordType recordName:(NSString *)inRecordName password:(NSString *)inPassword
                               error:(NSError **)outError;

/*!
    @method     setCredentialsWithRecordType: authType: authItems: outAuthItems: context: error:
    @abstract   Allows use of other Open Directory types of authentications to set the credentials for an ODNode
    @discussion Allows the caller to use other types of authentications that are available in Open Directory, that may
                require response-request loops, etc.  Not all OD plugins will support this call, look for 
                kODErrorCredentialsMethodNotSupported in outError.  outError is optional parameter, nil can be passed if 
				error details is not needed.
*/
- (BOOL)setCredentialsWithRecordType:(ODRecordType)inRecordType authenticationType:(ODAuthenticationType)inType 
                 authenticationItems:(NSArray *)inItems continueItems:(NSArray **)outItems
                             context:(id *)outContext error:(NSError **)outError;

/*!
    @method     setCredentialsUsingKerberosCache: error:
    @abstract   Similar to -[ODNode setCredentialsWithRecordType:] except it will use Kerberos cache to set the credentials.
    @discussion Allows the caller to use an existing Kerberos cache to authenticate to the directory.  Not all directories
                or plugins will support this capability.  If the authentication fails it may be necessary to use other
                methods.
*/
- (BOOL)setCredentialsUsingKerberosCache:(NSString *)inCacheName error:(NSError **)outError;

/*!
    @method     createRecordWithRecordType: name: attributes: error:
    @abstract   Takes a record and all of the provided attributes and creates the record in the node
    @discussion Takes all the provided attributes and type to create an entire record.  The function will assign a
                UUID to the record automatically.  This UUID can be overwritten by the client by passing with the
                other attributes.  inAttributes is optional, nil can be passed if no other attributes are to be set.
*/
- (ODRecord *)createRecordWithRecordType:(ODRecordType)inRecordType name:(NSString *)inRecordName 
                              attributes:(NSDictionary *)inAttributes error:(NSError **)outError;

/*!
    @method     recordWithRecordType: name: attributes: error:
    @abstract   Returns an ODRecord object that references the requested type and name
    @discussion Returns an ODRecord object that references the requested type and name.  The record will have cached the
                attributes requested.  Further attributes can be requested via ODRecord APIs.  For performance it is best
                to ask for as many attributes that are needed as possible up front.
*/
- (ODRecord *)recordWithRecordType:(ODRecordType)inRecordType name:(NSString *)inRecordName attributes:(NSArray *)inAttributes
                             error:(NSError **)outError;

/*!
    @method     customCall: sendData: error:
    @abstract   Sends a custom code to the node, send and receive data formats are specific to the call
    @discussion Sends a custom code to the node, send and receive data formats are specific to the call.  outError is 
                optional parameter, nil can be passed if error details are not needed.
*/
- (NSData *)customCall:(NSInteger)inCustomCode sendData:(NSData *)inSendData error:(NSError **)outError;

@end

#pragma mark -

/*!
    @class       ODRecord
    @abstract    This class is used to read, update and modify records within the directory
    @discussion  This class is used to read, update and modify records within the directory.  outError is optional parameter,
                 nil can be passed if error details are not needed.
*/
@interface ODRecord : NSObject

/*!
    @method     setNodeCredentials: password: error:
    @abstract   Similar to calling -[ODNode setCredentials:] except credentials are only set for this particular
                record's node
    @discussion Sets the credentials if necessary on the ODNode referenced by this ODRecord.  Very similar to
                calling -[ODNode setCredentials:] except other records referencing the underlying node will not get
                authenticated, therefore inadvertant changes cannot occur.  If all records referencing a particular 
                node need to be updated, then use -[ODNode setCredentials:] on the original node instead.  If the
                node is already authenticated with the same name and password, it will be a NOOP call.  The original
                ODNode held by an ODRecord will be released when the credentials are changed for the connection
                associated with the record.  outError is optional parameter, nil can be passed if error details are not needed.
*/
- (BOOL)setNodeCredentials:(NSString *)inUsername password:(NSString *)inPassword error:(NSError **)outError;

/*!
    @method     setNodeCredentialsWithRecordType: authenticationType: authItems: outAuthItems: context: error:
    @abstract   Similar to calling -[ODNode setCredentialsWithRecordType:] except credentials are only set for this particular record's
                node
    @discussion Allows the caller to use other types of authentications that are available in Open Directory, that may
                require response-request loops, etc.  Not all OD plugins will support this call, look for 
                kODErrorCredentialsMethodNotSupported in outError.  Same behavior as ODRecordSetNodeCredentials.  outError 
				is optional parameter, nil can be passed if error details are not needed.
*/
- (BOOL)setNodeCredentialsWithRecordType:(ODRecordType)inRecordType authenticationType:(ODAuthenticationType)inType 
                     authenticationItems:(NSArray *)inItems continueItems:(NSArray **)outItems
                                 context:(id *)outContext error:(NSError **)outError;

/*!
    @method     setNodeCredentialsUsingKerberosCache: error:
    @abstract   Similar to calling -[ODNode setCredentialsUsingKerberosCache:] except credentials are only set for this 
                particular record's node.
    @discussion Allows the caller to use an existing Kerberos cache to authenticate to the directory.  Not all directories
                or plugins will support this capability.  If the authentication fails it may be necessary to use other
                methods.
*/
- (BOOL)setNodeCredentialsUsingKerberosCache:(NSString *)inCacheName error:(NSError **)outError;

/*!
    @method     passwordPolicyAndReturnError:
    @abstract   Returns a dictionary containing the password policy for the record if available.
    @discussion Returns a dictionary containing the password policy for the record if available.  If no policy for record
                nil will be returned.  outError is optional parameter, nil can be passed if error details are not needed.
*/
- (NSDictionary *)passwordPolicyAndReturnError:(NSError **)outError;

/*!
    @method     verifyPassword: error:
    @abstract   Verifies the password provided is valid for the record
    @discussion Verifies the password provided is valid for the record.  outError is optional parameter, nil can be passed if 
                error details are not needed.
*/
- (BOOL)verifyPassword:(NSString *)inPassword error:(NSError **)outError;

/*!
    @method     verifyExtendedWithAuthenticationType: authenticationItems: continueItems: context: error:
    @abstract   Allows use of other Open Directory types of authentications
    @discussion Allows the caller to use other types of authentications that are available in Open Directory, that may 
                require response-request loops, etc.  A bool with the result of the operation.  
                If it fails, outError can be checked for more specific error.  Some ODNodes may not support the call
                so an error code of kODErrorCredentialsMethodNotSupported may be returned.  outError is optional 
                parameter, nil can be passed if error details are not needed.
*/
- (BOOL)verifyExtendedWithAuthenticationType:(ODAuthenticationType)inType authenticationItems:(NSArray *)inItems 
                               continueItems:(NSArray **)outItems context:(id *)outContext error:(NSError **)outError;

/*!
    @method     changePassword: toPassword: error:
    @abstract   Changes the password for a record
    @discussion Changes the password for a record.  The oldPassword can be nil if password is being set assuming the appropriate
                privileges are in place.  outError is optional parameter, nil can be passed if error details are not needed.
*/
- (BOOL)changePassword:(NSString *)oldPassword toPassword:(NSString *)newPassword error:(NSError **)outError;

/*!
    @method     synchronizeAndReturnError:
    @abstract   Synchronizes the record from the Directory in order to get current data and/or commit pending changes
    @discussion Synchronizes the record from the Directory in order to get current data.  Any previously fetched attributes
                will be re-fetch from the Directory.  This will not re-fetch the entire record, unless the entire record
                has been accessed.  Additionally, any changes made to the record will be committed to the directory,
                if the node does not do immediate commits.  outError is optional parameter, nil can be passed if error details
                are not needed.
*/
- (BOOL)synchronizeAndReturnError:(NSError **)outError;

/*!
    @method     recordType:
    @abstract   Returns the record type of the ODRecord
    @discussion Returns the record type of the ODRecord
*/
@property (nonatomic, readonly, copy) NSString * recordType;

/*!
    @method     recordName:
    @abstract   Returns the official record name of the ODRecord
    @discussion Returns the official record name of the ODRecord.
*/
@property (nonatomic, readonly, copy) NSString * recordName;

/*!
    @method     recordDetailsForAttributes: error:
    @abstract   Returns the attributes and values in the form of a key-value pair set.
    @discussion Returns the attributes and values in the form of a key-value pair set for this record.  The key is a 
                NSString of the attribute name (e.g., kODAttributeTypeRecordName, etc.) and the value is an NSArray
                of either NSData or NSString depending on the type of data.  Binary data will be returned as NSData.
                If nil is passed, then all currently retrieved attributes will be returned.  outError is optional parameter, 
                nil can be passed if error details are not needed.
*/
- (NSDictionary *)recordDetailsForAttributes:(NSArray *)inAttributes error:(NSError **)outError;

/*!
    @method     valuesForAttribute: error:
    @abstract   Returns an NSArray of NSString or NSData values of the attribute
    @discussion Returns an NSArray of NSString or NSData depending on the type of data.  Binary data will be 
                returned as NSData.  outError is optional parameter, nil can be passed if error details are not needed.
*/
- (NSArray *)valuesForAttribute:(ODAttributeType)inAttribute error:(NSError **)outError;

/*!
	@method     setValue: forAttribute: error:
	@abstract   Will take a mixture of NSData or NSString or an NSArray of either type when setting the values of an attribute
	@discussion Will take a mixture of NSData or NSString or an NSArray of either type when setting the values of an attribute.
				outError is optional parameter, nil can be passed if error details are not needed.
*/
- (BOOL)setValue:(id)inValueOrValues forAttribute:(ODAttributeType)inAttribute error:(NSError **)outError;

/*!
    @method     removeValuesForAttribute: error:
    @abstract   Removes all the values for an attribute.
    @discussion Removes all the values for an attribute.  outError is optional parameter, nil can be passed if 
                error details are not needed.
*/
- (BOOL)removeValuesForAttribute:(ODAttributeType)inAttribute error:(NSError **)outError;

/*!
    @method     addValue: toAttribute: error:
    @abstract   Will add a value to an attribute
    @discussion Will add a value to an attribute.  Should be either NSData or NSString type.  outError is optional 
                parameter, nil can be passed if error details are not needed.
*/
- (BOOL)addValue:(id)inValue toAttribute:(ODAttributeType)inAttribute error:(NSError **)outError;

/*!
    @method     removeValue: fromAttribute: error:
    @abstract   Will remove a value from an attribute
    @discussion Will remove a value from an attribute.  Should be either NSData or NSString type.  outError is optional 
                parameter, nil can be passed if error details are not needed.
*/
- (BOOL)removeValue:(id)inValue fromAttribute:(ODAttributeType)inAttribute error:(NSError **)outError;

/*!
    @method     deleteRecordAndReturnError:
    @abstract   Deletes the record from the node and invalidates the record.
    @discussion Deletes the record from the node and invalidates the record.  The ODRecord should be
                released after deletion.  outError is optional parameter, nil can be passed if error details are not needed.
*/
- (BOOL)deleteRecordAndReturnError:(NSError **)outError;

@end

@interface ODRecord (ODRecordGroupExtensions)

/*!
    @method     addMemberRecord: error:
    @abstract   Will add the record as a member of the group record
    @discussion Will add the record as a member of the group record.  An error will be returned if the record is not
                a group record.  Additionally, if the member record is not an appropriate type allowed as part of a group
                an error will be returned.  outError is optional parameter, nil can be passed if error details are not needed.
*/
- (BOOL)addMemberRecord:(ODRecord *)inRecord error:(NSError **)outError;

/*!
    @method     removeMemberRecord: error:
    @abstract   Will remove the record as a member from the group record
    @discussion Will remove the record as a member from the group record. An error will be returned if the record is not
                a group record.  Additionally, if the member record is not an appropriate type allowed as part of a group
                an error will be returned.  outError is optional parameter, nil can be passed if error details are not needed.
*/
- (BOOL)removeMemberRecord:(ODRecord *)inRecord error:(NSError **)outError;

/*!
    @method     isMemberRecord: error:
    @abstract   Will use membership APIs to determine if inRecord is a member of the group
    @discussion Will use membership APIs to determine if inRecord is a member of the group.  If the receiving
                object is not a group then NO will still be returned.  outError is optional parameter, nil can be passed if 
                error details are not needed.
*/
- (BOOL)isMemberRecord:(ODRecord *)inRecord error:(NSError **)outError;

@end

#endif
