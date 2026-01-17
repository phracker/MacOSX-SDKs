/*
 * Copyright (c) 2002-2010 Apple Inc. All Rights Reserved.
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
	@header SecTrust
	The functions and data types in SecTrust implement trust computation
    and allow the caller to apply trust decisions to the evaluation.
*/

#ifndef _SECURITY_SECTRUST_H_
#define _SECURITY_SECTRUST_H_

#include <Security/SecBase.h>
#include <Security/cssmtype.h>
#include <Security/cssmapple.h>
#include <CoreFoundation/CoreFoundation.h>
#include <AvailabilityMacros.h>


#if defined(__cplusplus)
extern "C" {
#endif

/*!
	@typedef SecTrustResultType
	@abstract Specifies the trust result type.
	@constant kSecTrustResultInvalid Indicates an invalid setting or result.
	@constant kSecTrustResultProceed Indicates you may proceed.  This value
    may be returned by the SecTrustEvaluate function or stored as part of
    the user trust settings. 
	@constant kSecTrustResultConfirm Indicates confirmation with the user
    is required before proceeding.  This value may be returned by the
    SecTrustEvaluate function or stored as part of the user trust settings. 
	@constant kSecTrustResultDeny Indicates a user-configured deny; do not
    proceed. This value may be returned by the SecTrustEvaluate function
    or stored as part of the user trust settings. 
	@constant kSecTrustResultUnspecified Indicates user intent is unknown.
    This value may be returned by the SecTrustEvaluate function or stored
    as part of the user trust settings. 
	@constant kSecTrustResultRecoverableTrustFailure Indicates a trust
    framework failure; retry after fixing inputs. This value may be returned
    by the SecTrustEvaluate function but not stored as part of the user
    trust settings. 
	@constant kSecTrustResultFatalTrustFailure Indicates a trust framework
    failure; no "easy" fix. This value may be returned by the
    SecTrustEvaluate function but not stored as part of the user trust
    settings.
	@constant kSecTrustResultOtherError Indicates a failure other than that
    of trust evaluation. This value may be returned by the SecTrustEvaluate
    function but not stored as part of the user trust settings.
 */
typedef uint32_t SecTrustResultType;
enum {
    kSecTrustResultInvalid,
    kSecTrustResultProceed,
    kSecTrustResultConfirm,
    kSecTrustResultDeny,
    kSecTrustResultUnspecified,
    kSecTrustResultRecoverableTrustFailure,
    kSecTrustResultFatalTrustFailure,
    kSecTrustResultOtherError
};

/*!
	@typedef SecTrustUserSetting
	@abstract Specifies user-specified trust settings.
*/
typedef SecTrustResultType SecTrustUserSetting;
	
/*!
 	@typedef SecTrustOptionFlags
	@abstract Options for customizing trust evaluation.
	@constant kSecTrustOptionAllowExpired Allow expired certs.
	@constant kSecTrustOptionLeafIsCA Allow CA as leaf certificate.
	@constant kSecTrustOptionFetchIssuerFromNet Allow network fetch of CA cert.
	@constant kSecTrustOptionAllowExpiredRoot Allow expired roots.
	@constant kSecTrustOptionRequireRevPerCert Require positive revocation
	check per certificate.
	@constant kSecTrustOptionUseTrustSettings Use TrustSettings instead of
	anchors.
	@constant kSecTrustOptionImplicitAnchors Properly self-signed certs are
	treated as anchors implicitly.
 */
typedef uint32_t SecTrustOptionFlags;
enum {
	kSecTrustOptionAllowExpired       = 0x00000001,
	kSecTrustOptionLeafIsCA           = 0x00000002,
	kSecTrustOptionFetchIssuerFromNet = 0x00000004,
	kSecTrustOptionAllowExpiredRoot   = 0x00000008,
	kSecTrustOptionRequireRevPerCert  = 0x00000010,
	kSecTrustOptionUseTrustSettings   = 0x00000020, 
	kSecTrustOptionImplicitAnchors    = 0x00000040
};

/*!
    @enum Trust Property Constants
    @discussion Predefined property key constants used to obtain values in
        a dictionary of trust evaluation results.
	@constant kSecPropertyTypeTitle Specifies a key whose value is a
		CFStringRef containing the title (display name) of this certificate.
	@constant kSecPropertyTypeError Specifies a key whose value is a
		CFStringRef containing the reason for a trust evaluation failure.
*/
extern CFTypeRef kSecPropertyTypeTitle
    __OSX_AVAILABLE_STARTING(__MAC_10_7, __IPHONE_NA);
extern CFTypeRef kSecPropertyTypeError
    __OSX_AVAILABLE_STARTING(__MAC_10_7, __IPHONE_NA);


/*!
	@typedef SecTrustRef
	@abstract A pointer to an opaque trust management structure.
*/
typedef struct OpaqueSecTrustRef *SecTrustRef;

#ifdef __BLOCKS__
/*!
	@typedef SecTrustCallback
	@abstract Delivers the result from an asynchronous trust evaluation.
    @param trustRef A reference to the trust object which has been evaluated.
    @param trustResult The trust result of the evaluation. Additional status
	information can be obtained by calling SecTrustCopyProperties().
*/
typedef void (^SecTrustCallback)(SecTrustRef trustRef, SecTrustResultType trustResult);
#endif

/*!
	@function SecTrustGetTypeID
	@abstract Returns the type identifier of SecTrust instances.
	@result The CFTypeID of SecTrust instances.
*/
CFTypeID SecTrustGetTypeID(void)
    __OSX_AVAILABLE_STARTING(__MAC_10_3, __IPHONE_2_0);

/*!
	@function SecTrustCreateWithCertificates
	@abstract Creates a trust object based on the given certificates and
    policies.
    @param certificates The group of certificates to verify.
    @param policies An array of one or more policies. You may pass a
    SecPolicyRef to represent a single policy.
	@param trustRef On return, a pointer to the trust management reference.
	@result A result code.  See "Security Error Codes" (SecBase.h).
    @discussion If multiple policies are passed in, all policies must verify
    for the chain to be considered valid.
*/
OSStatus SecTrustCreateWithCertificates(CFArrayRef certificates,
    CFTypeRef policies, SecTrustRef *trustRef)
    __OSX_AVAILABLE_STARTING(__MAC_10_3, __IPHONE_2_0);


/*!
    @function SecTrustSetPolicies
    @abstract Set (replace) the set of policies to evaluate.
    @param trust The reference to the trust to change.
    @param policies An array of one or more policies. You may pass a
    SecPolicyRef to represent a single policy.
    @result A result code. See "Security Error Codes" (SecBase.h).
*/    
OSStatus SecTrustSetPolicies(SecTrustRef trust, CFTypeRef policies)
    __OSX_AVAILABLE_STARTING(__MAC_10_3, __IPHONE_NA);

/*!
	@function SecTrustSetOptions
	@abstract Sets optional flags and data for customizing a trust evaluation.
	@param trustRef The reference to the trust to change.
	@param options Flags to change evaluation behavior for this trust.
	@result A result code. See "Security Error Codes" (SecBase.h).
 */
OSStatus SecTrustSetOptions(SecTrustRef trustRef, SecTrustOptionFlags options)
    __OSX_AVAILABLE_STARTING(__MAC_10_7, __IPHONE_NA);

/*!
	@function SecTrustSetParameters
	@abstract Sets the action and action data for a trust object.
	@param trustRef The reference to the trust to change.
	@param action A trust action.
	@param actionData A reference to data associated with this action.
	@result A result code. See "Security Error Codes" (SecBase.h).
	@discussion This function is deprecated in Mac OS X 10.7 and later;
	use SecTrustSetOptions instead.
 */
OSStatus SecTrustSetParameters(SecTrustRef trustRef,
	CSSM_TP_ACTION action, CFDataRef actionData)
	DEPRECATED_IN_MAC_OS_X_VERSION_10_7_AND_LATER;
	
/*!
	@function SecTrustSetAnchorCertificates
	@abstract Sets the anchor certificates for a given trust.
	@param trust A reference to a trust object.
	@param anchorCertificates An array of anchor certificates.
	@result A result code.  See "Security Error Codes" (SecBase.h).
    @discussion Calling this function without also calling
    SecTrustSetAnchorCertificatesOnly() will disable trusting any
    anchors other than the ones in anchorCertificates.
*/
OSStatus SecTrustSetAnchorCertificates(SecTrustRef trust,
    CFArrayRef anchorCertificates)
    __OSX_AVAILABLE_STARTING(__MAC_10_3, __IPHONE_2_0);

/*!
	@function SecTrustSetAnchorCertificatesOnly
	@abstract Reenables trusting anchor certificates in addition to those
    passed in via the SecTrustSetAnchorCertificates API.
	@param trust A reference to a trust object.
	@param anchorCertificatesOnly If true, disables trusting any anchors other
    than the ones passed in via SecTrustSetAnchorCertificates().  If false,
    the built in anchor certificates are also trusted.
	@result A result code.  See "Security Error Codes" (SecBase.h).
*/
OSStatus SecTrustSetAnchorCertificatesOnly(SecTrustRef trust,
    Boolean anchorCertificatesOnly)
    __OSX_AVAILABLE_STARTING(__MAC_10_6, __IPHONE_2_0);

/*!
	@function SecTrustSetKeychains
	@abstract Sets the keychains for a given trust object.
	@param trust A reference to a trust object.
    @param keychainOrArray A reference to an array of keychains to search, a 
	single keychain, or NULL to use the default keychain search list.
	@result A result code. See "Security Error Codes" (SecBase.h).
	@discussion By default, the user's keychain search list and the system
	anchors keychain are searched for certificates to complete the chain. You 
	can specify a zero-element array if you do not want any keychains searched.
*/
OSStatus SecTrustSetKeychains(SecTrustRef trust, CFTypeRef keychainOrArray)
    __OSX_AVAILABLE_STARTING(__MAC_10_3, __IPHONE_NA);

/*!
	@function SecTrustSetVerifyDate
	@abstract Set the date for which the trust should be verified.
	@param trust A reference to a trust object.
	@param verifyDate The date for which to verify trust.
	@result A result code.  See "Security Error Codes" (SecBase.h).
    @discussion This function lets you evaluate certificate validity for a
	given date (for example, to determine if a signature was valid on the date
	it was signed, even if the certificate has since expired.) If this function
	is not called, the time at which SecTrustEvaluate() is called is used
	implicitly as the verification time.
*/
OSStatus SecTrustSetVerifyDate(SecTrustRef trust, CFDateRef verifyDate)
    __OSX_AVAILABLE_STARTING(__MAC_10_3, __IPHONE_2_0);

/*!
	@function SecTrustGetVerifyTime
	@abstract Returns the verify time.
	@param trust A reference to the trust object being verified.
	@result A CFAbsoluteTime value representing the time at which certificates
	should be checked for validity.
    @discussion This function retrieves the verification time for the given
	trust reference, as set by a prior call to SecTrustSetVerifyDate(). If the
	verification time has not been set, this function returns a value of 0,
	indicating that the current date/time is implicitly used for verification.
*/
CFAbsoluteTime SecTrustGetVerifyTime(SecTrustRef trust)
    __OSX_AVAILABLE_STARTING(__MAC_10_6, __IPHONE_2_0);

/*!
	@function SecTrustEvaluate
	@abstract Evaluates a trust reference synchronously.
	@param trust A reference to the trust object to evaluate.
	@param result A pointer to a result type.
	@result A result code. See "Security Error Codes" (SecBase.h).	
    @discussion This function will completely evaluate trust before returning,
	possibly including network access to fetch intermediate certificates or to
	perform revocation checking. Since this function can block during those
	operations, you should call it from within a function that is placed on a
	dispatch queue, or in a separate thread from your application's main
	run loop. Alternatively, you can use the SecTrustEvaluateAsync() function
	in Mac OS X 10.7 and later.
*/
OSStatus SecTrustEvaluate(SecTrustRef trust, SecTrustResultType *result)
    __OSX_AVAILABLE_STARTING(__MAC_10_3, __IPHONE_2_0);

#ifdef __BLOCKS__
/*!
	@function SecTrustEvaluateAsync
	@abstract Evaluates a trust reference asynchronously.
	@param trust A reference to the trust object to evaluate.
	@param queue A dispatch queue on which the result callback should be
	executed. Pass NULL to use the current dispatch queue.
	@param result A SecTrustCallback block which will be executed when the
	trust evaluation is complete.
	@result A result code. See "Security Error Codes" (SecBase.h).	
*/
OSStatus SecTrustEvaluateAsync(SecTrustRef trust,
	dispatch_queue_t queue, SecTrustCallback result)
    __OSX_AVAILABLE_STARTING(__MAC_10_7, __IPHONE_NA);
#endif

/*!
	@function SecTrustGetResult
	@abstract Returns detailed information on the outcome of an evaluation.
	@param trustRef A reference to a trust object.
	@param result A pointer to the result from the call to SecTrustEvaluate.
	@param certChain On return, a pointer to the certificate chain used to
	validate the input certificate. Call the CFRelease function to release
	this pointer.
	@param statusChain On return, a pointer to the status of the certificate
	chain. Do not attempt to free this pointer; it remains valid until the
	trust is destroyed or the next call to SecTrustEvaluate.
	@result A result code. See "Security Error Codes" (SecBase.h).
	@discussion This function is deprecated in Mac OS X 10.7 and later.
	To get the complete certificate chain, use SecTrustGetCertificateCount and
	SecTrustGetCertificateAtIndex. To get detailed status information for each
	certificate, use SecTrustCopyProperties. To get the overall trust result
	for the evaluation, use SecTrustGetTrustResult.
*/
OSStatus SecTrustGetResult(SecTrustRef trustRef, SecTrustResultType *result,
	CFArrayRef *certChain, CSSM_TP_APPLE_EVIDENCE_INFO **statusChain)
	DEPRECATED_IN_MAC_OS_X_VERSION_10_7_AND_LATER;

/*!
	@function SecTrustGetCssmResult
	@abstract Gets the CSSM trust result.
	@param trust A reference to a trust.
	@param result On return, a pointer to the CSSM trust result.
	@result A result code. See "Security Error Codes" (SecBase.h).
	@discussion This function is deprecated in Mac OS X 10.7 and later.
	To get detailed status information for each certificate, use
	SecTrustCopyProperties. To get the overall trust result for the evaluation,
	use SecTrustGetTrustResult.
*/
OSStatus SecTrustGetCssmResult(SecTrustRef trust,
	CSSM_TP_VERIFY_CONTEXT_RESULT_PTR *result)
	DEPRECATED_IN_MAC_OS_X_VERSION_10_7_AND_LATER;

/*!
	@function SecTrustGetCssmResultCode
	@abstract Gets the result code from the most recent call to SecTrustEvaluate
	for the specified trust.
	@param trust A reference to a trust.
	@param resultCode On return, the result code produced by the most recent
	evaluation of the given trust (cssmerr.h). The value of resultCode is
	undefined if SecTrustEvaluate has not been called.
	@result A result code. See "Security Error Codes" (SecBase.h). Returns
	errSecTrustNotAvailable if SecTrustEvaluate has not been called for the
	specified trust.
	@discussion This function is deprecated in Mac OS X 10.7 and later.
	To get detailed status information for each certificate, use
	SecTrustCopyProperties. To get the overall trust result for the evaluation,
	use SecTrustGetTrustResult.
*/
OSStatus SecTrustGetCssmResultCode(SecTrustRef trust, OSStatus *resultCode)
	DEPRECATED_IN_MAC_OS_X_VERSION_10_7_AND_LATER;

/*!
	@function SecTrustGetTrustResult
	@param trustRef A reference to a trust object.
	@param result A pointer to the result from the most recent call to
	SecTrustEvaluate for this trust reference. If SecTrustEvaluate has not been
	called, the result is kSecTrustResultInvalid.
	@result A result code. See "Security Error Codes" (SecBase.h).
	@discussion This function replaces SecTrustGetResult for the purpose of
	obtaining the current evaluation result of a given trust reference.
*/
OSStatus SecTrustGetTrustResult(SecTrustRef trustRef,
	SecTrustResultType *result)
    __OSX_AVAILABLE_STARTING(__MAC_10_7, __IPHONE_NA);

/*!
	@function SecTrustGetTPHandle
	@abstract Gets the CSSM trust handle
	@param trust A reference to a trust.
	@param handle On return, a CSSM trust handle.
	@result A result code. See "Security Error Codes" (SecBase.h).
	@discussion This function is deprecated in Mac OS X 10.7 and later.
*/
OSStatus SecTrustGetTPHandle(SecTrustRef trust, CSSM_TP_HANDLE *handle)
	DEPRECATED_IN_MAC_OS_X_VERSION_10_7_AND_LATER;

/*!
    @function SecTrustCopyPolicies
    @abstract Returns an array of policies used by a given trust.
    @param trust  A reference to a trust object.
    @param policies On return, an array of policies used by this trust.
	Call the CFRelease function to release this reference.
    @result A result code. See "Security Error Codes" (SecBase.h).
*/    
OSStatus SecTrustCopyPolicies(SecTrustRef trust, CFArrayRef *policies)
    __OSX_AVAILABLE_STARTING(__MAC_10_3, __IPHONE_NA);

/*!
    @function SecTrustCopyCustomAnchorCertificates
    @abstract Returns an array of custom anchor certificates used by a given
	trust, as set by a prior call to SecTrustSetAnchorCertificates, or NULL if
	no custom anchors have been specified.
    @param trust  A reference to a trust.
    @param anchors On return, an array of custom anchor certificates (roots)
	used by this trust, or NULL if no custom anchors have been specified. Call
	the CFRelease function to release this reference.
    @result A result code. See "Security Error Codes" (SecBase.h).
*/    
OSStatus SecTrustCopyCustomAnchorCertificates(SecTrustRef trust,
	CFArrayRef *anchors)
    __OSX_AVAILABLE_STARTING(__MAC_10_5, __IPHONE_NA);

/*!
    @function SecTrustCopyAnchorCertificates
    @abstract Returns an array of default anchor (root) certificates used by
	the system.
    @param anchors On return, an array containing the system's default anchors
	(roots). Call the CFRelease function to release this pointer.
    @result A result code. See "Security Error Codes" (SecBase.h).
*/
OSStatus SecTrustCopyAnchorCertificates(CFArrayRef *anchors)
    __OSX_AVAILABLE_STARTING(__MAC_10_3, __IPHONE_NA);

/*!
	@function SecTrustCopyPublicKey
	@abstract Return the public key for the leaf certificate after trust has 
	been evaluated.
	@param trust A reference to the trust object which has been evaluated.
	@result The certificate's public key, or NULL if it the public key could
	not be extracted (this can happen with DSA certificate chains if the
    parameters in the chain cannot be found).  The caller is responsible
    for calling CFRelease on the returned key when it is no longer needed.
*/
SecKeyRef SecTrustCopyPublicKey(SecTrustRef trust)
    __OSX_AVAILABLE_STARTING(__MAC_10_7, __IPHONE_2_0);

/*!
	@function SecTrustGetCertificateCount
	@abstract Returns the number of certificates in an evaluated certificate
    chain.
	@param trust Reference to a trust object.
	@result The number of certificates in the trust chain.  This function will
    return 1 if the trust has not been evaluated, and the number of
    certificates in the chain including the anchor if it has.
*/
CFIndex SecTrustGetCertificateCount(SecTrustRef trust)
    __OSX_AVAILABLE_STARTING(__MAC_10_7, __IPHONE_2_0);

/*!
	@function SecTrustGetCertificateAtIndex
	@abstract Returns a certificate from the trust chain.
	@param trust Reference to a trust object.
	@param ix The index of the requested certificate.  Indices run from 0
    (leaf) to the anchor (or last certificate found if no anchor was found).
    The leaf cert (index 0) is always present regardless of whether the trust
    reference has been evaluated or not.
	@result A SecCertificateRef for the requested certificate.
*/
SecCertificateRef SecTrustGetCertificateAtIndex(SecTrustRef trust, CFIndex ix)
    __OSX_AVAILABLE_STARTING(__MAC_10_7, __IPHONE_2_0);
	
/*!
	@function SecTrustCopyProperties
	@abstract Return a property array for this trust evaluation.
	@param trust A reference to the trust object. If the trust has not been
	evaluated, the returned property array will be empty.
    @result A property array. It is the caller's responsibility to CFRelease
    the returned array when it is no longer needed.
	@discussion This function returns an ordered array of CFDictionaryRef
	instances for each certificate in the chain. Indices run from 0 (leaf) to
    the anchor (or last certificate found if no anchor was found). The property
	at index 0 of the array may also include general information about the
	entire chain's validity in the context of this trust evaluation. See the
	"Trust Property Constants" section for a list of currently defined keys.
*/
CFArrayRef SecTrustCopyProperties(SecTrustRef trust)
    __OSX_AVAILABLE_STARTING(__MAC_10_7, __IPHONE_2_0);


#if defined(__cplusplus)
}
#endif

#endif /* !_SECURITY_SECTRUST_H_ */
