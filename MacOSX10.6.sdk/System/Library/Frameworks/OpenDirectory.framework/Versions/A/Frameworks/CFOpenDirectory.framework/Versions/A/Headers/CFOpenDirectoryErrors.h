/*
 * Copyright (c) 2005-2008 Apple Inc. All rights reserved.
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
    @header		CFOpenDirectoryErrors
    @abstract   A list of error codes
    @discussion Contains a list of error codes that can be returned by OpenDirectory APIs.
*/

#ifndef __CFOPENDIRECTORYERRORS_H
#define __CFOPENDIRECTORYERRORS_H

/*!
 @enum   	ODFrameworkErrors
 @abstract   Errors specific to the framework and to underlying calls
 @discussion Errors specific to the framework and to underlying calls
 @constant kODErrorSessionLocalOnlyDaemonInUse is when a Local Only session was initiated and is still active
 @constant kODErrorSessionNormalDaemonInUse is when the Normal daemon is still in use but request was issued for Local only
 @constant kODErrorSessionDaemonNotRunning is when the daemon is not running
 @constant kODErrorSessionDaemonRefused is when the daemon refused the session
 @constant kODErrorSessionProxyCommunicationError is when there was a communication error with the remote daemon
 @constant kODErrorSessionProxyVersionMismatch is when versions mismatch between the remote daemon and local framework
 @constant kODErrorSessionProxyIPUnreachable is when the provided kODSessionProxyAddress did not respond
 @constant kODErrorSessionProxyUnknownHost is when the provided kODSessionProxyAddress cannot be resolved
 @constant kODErrorNodeUnknownName is when the node name provided does not exist and cannot be opened
 @constant kODErrorNodeUnknownType is when the node type provided is not a known value
 @constant kODErrorNodeConnectionFailed is when a node connection failed (commonly server closed connection, etc.)
 @constant kODErrorNodeUnknownHost is when an invalid host is provided
 @constant kODErrorQuerySynchronize is an error code that is returned when a synchronize has been initiated
 @constant kODErrorQueryInvalidMatchType is when an invalid match type is provided in a query
 @constant kODErrorQueryUnsupportedMatchType is when plugin does not support the requirested match type
 @constant kODErrorQueryTimeout is when a query timed out during request
 @constant kODErrorRecordReadOnlyNode is when a record cannot be modified
 @constant kODErrorRecordPermissionError is when the changes requested were denied due to insufficient permissions
 @constant kODErrorRecordParameterError is when an invalid parameter was provided
 @constant kODErrorRecordInvalidType is when an invalid record type was provided
 @constant kODErrorRecordAlreadyExists is when a record create failed because the record already exists
 @constant kODErrorRecordTypeDisabled is when a particular record type is disabled by policy for a plugin
 @constant kODErrorRecordAttributeUnknownType is when an unknown attribute type is provided
 @constant kODErrorRecordAttributeNotFound is when an attribute requested is not found in the record
 @constant kODErrorRecordAttributeValueSchemaError is when an attribute value does not meet schema requirements
 @constant kODErrorRecordAttributeValueNotFound is when an attribute value is not found in a record
 @constant kODErrorCredentialsInvalid is when credentials provided are invalid with the current node
 @constant kODErrorCredentialsMethodNotSupported is when a particular extended method is not supported by the node
 @constant kODErrorCredentialsNotAuthorized is when an operation such as changing a password is not authorized with current privileges
 @constant kODErrorCredentialsParameterError is when a parameter provided is invalid
 @constant kODErrorCredentialsOperationFailed is when the requested operation failed (usually due to some unrecoverable error)
 @constant kODErrorCredentialsServerUnreachable is when the authententication server is not reachabable
 @constant kODErrorCredentialsServerNotFound is when the authentication server could not be found for the operation requested
 @constant kODErrorCredentialsServerError is when the authentication server encountered an error
 @constant kODErrorCredentialsServerTimeout is when the authentication server timed out
 @constant kODErrorCredentialsContactMaster is when the authentication server is not the master and the operation requires the master
 @constant kODErrorCredentialsServerCommunicationError is when the authentication server had a communications error
 @constant kODErrorCredentialsAccountNotFound is when the authentication server could not find the account provided
 @constant kODErrorCredentialsAccountDisabled is when the account is disabled
 @constant kODErrorCredentialsAccountExpired is when the account is expired
 @constant kODErrorCredentialsAccountInactive is when the account is inactive
 @constant kODErrorCredentialsPasswordExpired is when the password has expired and must be changed
 @constant kODErrorCredentialsPasswordChangeRequired is when a password change is required
 @constant kODErrorCredentialsPasswordQualityFailed is when a password provided for change did not meet quality minimum requirements
 @constant kODErrorCredentialsPasswordTooShort is when a password provided is too short
 @constant kODErrorCredentialsPasswordTooLong is when a password provided is too long
 @constant kODErrorCredentialsPasswordNeedsLetter is when a password needs a letter
 @constant kODErrorCredentialsPasswordNeedsDigit is when a password needs a digit
 @constant kODErrorCredentialsPasswordChangeTooSoon is when a an attempt to change a password too soon before last change
 @constant kODErrorCredentialsPasswordUnrecoverable is when password was not recoverable from the authentication database
 @constant kODErrorCredentialsInvalidLogonHours is when an account attempts to login outside of set logon hours
 @constant kODErrorCredentialsInvalidComputer is when an account attempts to login to a computer they are not authorized
 @constant kODErrorPluginOperationNotSupported is when a plugin does not support the requested operation
 @constant kODErrorPluginError is when a plugin has encountered some undefined error
 @constant kODErrorDaemonError is when some error occurred inside the daemon
*/

enum ODFrameworkErrors
{
	/* ODSession error codes */
	kODErrorSessionLocalOnlyDaemonInUse			=	1000,
	kODErrorSessionNormalDaemonInUse			=	1001,
	kODErrorSessionDaemonNotRunning				=	1002,
	kODErrorSessionDaemonRefused				=	1003,

	kODErrorSessionProxyCommunicationError		=	1100,
	kODErrorSessionProxyVersionMismatch			=	1101,
	kODErrorSessionProxyIPUnreachable			=	1102,
	kODErrorSessionProxyUnknownHost				=	1103,
	
	/* ODNode error codes */
	kODErrorNodeUnknownName						=	2000,
	kODErrorNodeUnknownType						=	2001,

	kODErrorNodeConnectionFailed				=	2100,
	
	/* ODNode miscellaneous error codes */
	kODErrorNodeUnknownHost						=	2200,
	
	/* ODQuery error codes */
	kODErrorQuerySynchronize					=	3000,
	
	kODErrorQueryInvalidMatchType				=	3100,
	kODErrorQueryUnsupportedMatchType			=	3101,
	kODErrorQueryTimeout						=	3102,
	
	/* ODRecord error codes */
	kODErrorRecordReadOnlyNode					=	4000,
	kODErrorRecordPermissionError				=	4001,
	
	kODErrorRecordParameterError				=	4100,
	kODErrorRecordInvalidType					=	4101,
	kODErrorRecordAlreadyExists					=	4102,
	kODErrorRecordTypeDisabled					=	4103,
	
	kODErrorRecordAttributeUnknownType			=	4200,
	kODErrorRecordAttributeNotFound				=	4201,
	kODErrorRecordAttributeValueSchemaError		=	4202,
	kODErrorRecordAttributeValueNotFound		=   4203,
	
	/* Credential specific error codes */
	kODErrorCredentialsInvalid					=	5000,
	
	kODErrorCredentialsMethodNotSupported		=	5100,
	kODErrorCredentialsNotAuthorized			=	5101,
	kODErrorCredentialsParameterError			=	5102,
	kODErrorCredentialsOperationFailed			=	5103,
	
	kODErrorCredentialsServerUnreachable		=	5200,
	kODErrorCredentialsServerNotFound			=	5201,
	kODErrorCredentialsServerError				=	5202,
	kODErrorCredentialsServerTimeout			=	5203,
	kODErrorCredentialsContactMaster			=	5204,
	kODErrorCredentialsServerCommunicationError	=	5205,
	
	kODErrorCredentialsAccountNotFound			=	5300,
	kODErrorCredentialsAccountDisabled			=	5301,
	kODErrorCredentialsAccountExpired			=	5302,
	kODErrorCredentialsAccountInactive			=	5303,
	
	kODErrorCredentialsPasswordExpired			=	5400,
	kODErrorCredentialsPasswordChangeRequired	=	5401,
	kODErrorCredentialsPasswordQualityFailed	=	5402,
	kODErrorCredentialsPasswordTooShort			=	5403,
	kODErrorCredentialsPasswordTooLong			=	5404,
	kODErrorCredentialsPasswordNeedsLetter		=	5405,
	kODErrorCredentialsPasswordNeedsDigit		=	5406,
	kODErrorCredentialsPasswordChangeTooSoon	=	5407,
	kODErrorCredentialsPasswordUnrecoverable	=	5408,

	kODErrorCredentialsInvalidLogonHours		= 	5500,
	kODErrorCredentialsInvalidComputer			= 	5501,

	/* Underlying plugin errors */
	kODErrorPluginOperationNotSupported			=	10000,
	kODErrorPluginError							=	10001,
	kODErrorDaemonError							=	10002,
};

#endif
