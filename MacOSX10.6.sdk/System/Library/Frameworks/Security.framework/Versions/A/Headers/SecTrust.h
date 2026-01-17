/*
 * Copyright (c) 2002-2009 Apple Inc. All Rights Reserved.
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
	The functions and data types in SecTrust implement trust computation and allow the user to apply trust decisions to the trust configuration.
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
	@constant kSecTrustResultProceed Indicates you may proceed.  This value may be returned by the SecTrustEvaluate function or stored as part of the user trust settings. 
	@constant kSecTrustResultConfirm Indicates confirmation with the user is required before proceeding.  This value may be returned by the SecTrustEvaluate function or stored as part of the user trust settings. 
	@constant kSecTrustResultDeny Indicates a user-configured deny; do not proceed. This value may be returned by the SecTrustEvaluate function or stored as part of the user trust settings. 
	@constant kSecTrustResultUnspecified Indicates user intent is unknown. This value may be returned by the SecTrustEvaluate function or stored as part of the user trust settings. 
	@constant kSecTrustResultRecoverableTrustFailure Indicates a trust framework failure; retry after fixing inputs. This value may be returned by the SecTrustEvaluate function but not stored as part of the user trust settings. 
	@constant kSecTrustResultFatalTrustFailure Indicates a trust framework failure; no "easy" fix. This value may be returned by the SecTrustEvaluate function but not stored as part of the user trust settings.
	@constant kSecTrustResultOtherError Indicates a failure other than that of trust evaluation. This value may be returned by the SecTrustEvaluate function but not stored as part of the user trust settings.
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
	@typedef SecTrustRef
	@abstract A pointer to an opaque trust management structure.
*/
typedef struct OpaqueSecTrustRef *SecTrustRef;

/*!
	@function SecTrustGetTypeID
	@abstract Returns the type identifier of SecTrust instances.
	@result The CFTypeID of SecTrust instances.
*/
CFTypeID SecTrustGetTypeID(void);

/*!
	@function SecTrustCreateWithCertificates
	@abstract Creates a trust based on the given certificates and policies.
    @param certificates The group of certificates to verify.
    @param policies An array of one or more policies. You may pass a SecPolicyRef to represent a single policy.
	@param trustRef On return, a pointer to the trust management reference.
	@result A result code. See "Security Error Codes" (SecBase.h).
*/
OSStatus SecTrustCreateWithCertificates(CFArrayRef certificates, CFTypeRef policies, SecTrustRef *trustRef);

/*!
    @function SecTrustSetPolicies
    @abstract Set (replace) the set of policies to evaluate.
    @param trust The reference to the trust to change.
    @param policies An array of one or more policies. A single SecPolicyRef may also be passed, representing an array of one policy.
    @result A result code. See "Security Error Codes" (SecBase.h).
*/    
OSStatus SecTrustSetPolicies(SecTrustRef trust, CFTypeRef policies);

/*!
	@function SecTrustSetParameters
	@abstract Sets the action and action data for a trust.
	@param trustRef The reference to the trust to change.
	@param action A CSSM trust action.
	@param actionData A reference to action data.
	@result A result code. See "Security Error Codes" (SecBase.h).
 */
OSStatus SecTrustSetParameters(SecTrustRef trustRef, CSSM_TP_ACTION action, CFDataRef actionData);

/*!
	@function SecTrustSetAnchorCertificates
	@abstract Sets the anchor certificates for a given trust.
	@param trust A reference to a trust.
	@param anchorCertificates An array of anchor certificates.
	@result A result code. See "Security Error Codes" (SecBase.h).
*/
OSStatus SecTrustSetAnchorCertificates(SecTrustRef trust, CFArrayRef anchorCertificates);

/*!
	@function SecTrustSetAnchorCertificatesOnly
	@abstract Reenables trusting anchor certificates in addition to those passed in
    via the SecTrustSetAnchorCertificates API.
	@param trust A reference to a trust object.
	@param anchorCertificatesOnly If true, disables trusting any anchors other
    than the ones passed in via SecTrustSetAnchorCertificates().  If false,
    the built in anchor certificates are also trusted.
	@result A result code.  See "Security Error Codes" (SecBase.h).
*/
OSStatus SecTrustSetAnchorCertificatesOnly(SecTrustRef trust,
    Boolean anchorCertificatesOnly);

/*!
	@function SecTrustSetKeychains
	@abstract Sets the keychains for a given trust.
	@param trust A reference to a trust.
    @param keychainOrArray A reference to an array of keychains to search, a single keychain or NULL to search the user's default keychain search list.
	@result A result code. See "Security Error Codes" (SecBase.h).
*/
OSStatus SecTrustSetKeychains(SecTrustRef trust, CFTypeRef keychainOrArray);

/*!
	@function SecTrustSetVerifyDate
	@abstract Specifies the date for verification of a given trust.
	@param trust A reference to the trust to verify.
	@param verifyDate The date to verify.
	@result A result code. See "Security Error Codes" (SecBase.h).
*/
OSStatus SecTrustSetVerifyDate(SecTrustRef trust, CFDateRef verifyDate);

/*!
	@function SecTrustGetVerifyTime
	@abstract Returns the verify time.
	@param trust A reference to the trust object to verify.
	@result A CFAbsoluteTime value representing the time at which certificates
	should be checked for validity.
*/
CFAbsoluteTime SecTrustGetVerifyTime(SecTrustRef trust);

/*!
	@function SecTrustEvaluate
	@abstract Evaluates a trust.
	@param trust A reference to the trust to evaluate.
	@param result A pointer to a result type.
	@result A result code. See "Security Error Codes" (SecBase.h).	
*/
OSStatus SecTrustEvaluate(SecTrustRef trust, SecTrustResultType *result);

/*!
	@function SecTrustGetResult
	@abstract Returns detail information on the outcome of a call to SecTrustEvaluate.
	@param trustRef A reference to a trust.
	@param result A pointer to the result from the call to SecTrustEvaluate.
	@param certChain On return, a pointer to the certificate chain used to validate the input certificate. Call the CFRelease function to release this pointer.
	@param statusChain On return, a pointer to the status of the certificate chain. Do not attempt to free this pointer; it remains valid until the trust is destroyed or the next call to SecTrustEvaluate.
	@result A result code. See "Security Error Codes" (SecBase.h).
*/
OSStatus SecTrustGetResult(SecTrustRef trustRef, SecTrustResultType *result, CFArrayRef *certChain, CSSM_TP_APPLE_EVIDENCE_INFO **statusChain);

/*!
	@function SecTrustGetCssmResult
	@abstract Gets the CSSM trust result.
	@param trust A reference to a trust.
	@param result On return, a pointer to the CSSM trust result.
	@result A result code. See "Security Error Codes" (SecBase.h).
*/
OSStatus SecTrustGetCssmResult(SecTrustRef trust, CSSM_TP_VERIFY_CONTEXT_RESULT_PTR *result);

/*!
	@function SecTrustGetCssmResultCode
	@abstract Gets the result code from the most recent call to SecTrustEvaluate for the specified trust.
	@param trust A reference to a trust.
	@param resultCode On return, the result code produced by the most recent evaluation of the given trust (cssmerr.h). The value of resultCode is undefined if SecTrustEvaluate has not been called.
	@result A result code. See "Security Error Codes" (SecBase.h). Returns errSecTrustNotAvailable if SecTrustEvaluate has not been called for the specified trust.
*/
OSStatus SecTrustGetCssmResultCode(SecTrustRef trust, OSStatus *resultCode);

/*!
	@function SecTrustGetTPHandle
	@abstract Gets the CSSM trust handle
	@param trust A reference to a trust.
	@param handle On return, a CSSM trust handle.
	@result A result code. See "Security Error Codes" (SecBase.h).
*/
OSStatus SecTrustGetTPHandle(SecTrustRef trust, CSSM_TP_HANDLE *handle);

/*!
    @function SecTrustCopyPolicies
    @abstract Returns an array of policies used by a given trust.
    @param trust  A reference to a trust.
    @param policies On return, an array of policies used by this trust. Call the CFRelease function to release this reference.
    @result A result code. See "Security Error Codes" (SecBase.h).
*/    
OSStatus SecTrustCopyPolicies(SecTrustRef trust, CFArrayRef *policies);

/*!
    @function SecTrustCopyCustomAnchorCertificates
    @abstract Returns an array of custom anchor certificates used by a given trust, as set by a prior call to SecTrustSetAnchorCertificates, or NULL if no custom anchors have been specified.
    @param trust  A reference to a trust.
    @param anchors On return, an array of custom anchor certificates (roots) used by this trust, or NULL if no custom anchors have been specified. Call the CFRelease function to release this reference.
    @result A result code. See "Security Error Codes" (SecBase.h).
	@availability Mac OS X version 10.5.
*/    
OSStatus SecTrustCopyCustomAnchorCertificates(SecTrustRef trust, CFArrayRef *anchors);

/*!
    @function SecTrustCopyAnchorCertificates
    @abstract Returns an array of default anchor (root) certificates used by the system.
    @param anchors On return, an array containing the system's default anchors (roots). Call the CFRelease function to release this pointer.
    @result A result code. See "Security Error Codes" (SecBase.h).
*/
OSStatus SecTrustCopyAnchorCertificates(CFArrayRef *anchors);

/*!
	@function SecTrustGetCSSMAnchorCertificates
	@abstract Retrieves the CSSM anchor certificates.
	@param cssmAnchors A pointer to an array of anchor certificates.
	@param cssmAnchorCount A pointer to the number of certificates in anchors.
	@result A result code. See "Security Error Codes" (SecBase.h).
	@availability Mac OS X version 10.4. Deprecated in Mac OS X version 10.5.
*/
OSStatus SecTrustGetCSSMAnchorCertificates(const CSSM_DATA **cssmAnchors, uint32 *cssmAnchorCount)
	DEPRECATED_IN_MAC_OS_X_VERSION_10_5_AND_LATER;

/*!
	@function SecTrustGetUserTrust
	@abstract Gets the user-specified trust settings of a certificate and policy.
	@param certificate A reference to a certificate.
	@param policy A reference to a policy.
	@param trustSetting On return, a pointer to the user specified trust settings.
	@result A result code. See "Security Error Codes" (SecBase.h).
	@availability Mac OS X version 10.4. Deprecated in Mac OS X version 10.5.
*/
OSStatus SecTrustGetUserTrust(SecCertificateRef certificate, SecPolicyRef policy, SecTrustUserSetting *trustSetting)
	DEPRECATED_IN_MAC_OS_X_VERSION_10_5_AND_LATER;

/*!
	@function SecTrustSetUserTrust
	@abstract Sets the user-specified trust settings of a certificate and policy.
	@param certificate A reference to a certificate.
	@param policy A reference to a policy.
	@param trustSetting The user-specified trust settings.
	@result A result code. See "Security Error Codes" (SecBase.h).
	@availability Mac OS X version 10.4. Deprecated in Mac OS X version 10.5.
	@discussion as of Mac OS version 10.5, this will result in a call to 
	 SecTrustSettingsSetTrustSettings(). 
*/
OSStatus SecTrustSetUserTrust(SecCertificateRef certificate, SecPolicyRef policy, SecTrustUserSetting trustSetting)
	DEPRECATED_IN_MAC_OS_X_VERSION_10_5_AND_LATER;


#if defined(__cplusplus)
}
#endif

#endif /* !_SECURITY_SECTRUST_H_ */
