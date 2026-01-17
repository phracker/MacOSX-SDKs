/*
 * Copyright (c) 2002-2020 Apple Inc. All Rights Reserved.
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
    @header SFCertificateView
*/

#ifndef _SFCERTIFICATEVIEW_H_
#define _SFCERTIFICATEVIEW_H_

#import <AppKit/AppKit.h>
#include <Security/SecCertificate.h>
#import <Availability.h>

API_UNAVAILABLE_BEGIN(ios, tvos, watchos, macCatalyst)

/*!
	@class SFCertificateView
    @abstract SFCertificateView is a NSView that displays the contents of a certificate.
*/

@interface SFCertificateView : NSVisualEffectView
{
@private
    id	_reserved_SFCertificateView;
}

/*!
    @method setCertificate:
	@abstract Specifies the certificate that's displayed in the view.
    @param certificate The new certificate for the view.
*/
- (void)setCertificate:(SecCertificateRef)certificate API_AVAILABLE(macos(10.3)) API_UNAVAILABLE(ios, tvos, watchos, macCatalyst);

/*!
	@method certificate
	@abstract Returns the certificate currently displayed in the view.
*/
- (SecCertificateRef)certificate API_AVAILABLE(macos(10.3)) API_UNAVAILABLE(ios, tvos, watchos, macCatalyst);

/*!
    @method setPolicies:
	@abstract Specifies one or more policies that apply to the displayed certificate.
    @param policies The policies to use when evaluating this certificate's status.
		You can pass either a SecPolicyRef or a NSArray (containing one or more SecPolicyRef instances) in this parameter.
		If policies is set to nil, the Apple X.509 Basic Policy will be used.
	@discussion Applications will typically display a SFCertificateView in the context of a specific usage, such as SSL or S/MIME.
	You should set only the policy references which apply to your intended usage.
*/
- (void)setPolicies:(id)policies API_AVAILABLE(macos(10.4)) API_UNAVAILABLE(ios, tvos, watchos, macCatalyst);

/*!
    @method policies
	@abstract Returns an array of policies used to evaluate the status of the displayed certificate.
	@discussion This method returns an autoreleased NSArray containing one or more SecPolicyRef instances, as set by a previous
	setPolicies: call. The array will always contain at least one item (the Apple X.509 Basic Policy).
*/
- (NSArray *)policies API_AVAILABLE(macos(10.4)) API_UNAVAILABLE(ios, tvos, watchos, macCatalyst);

/*!
    @method setEditableTrust:
	@abstract Specifies whether the user can edit the certificate's trust settings.
    @param editable Pass YES if the trust settings should be editable.
*/
- (void)setEditableTrust:(BOOL)editable API_AVAILABLE(macos(10.3)) API_UNAVAILABLE(ios, tvos, watchos, macCatalyst);

/*!
	@method isEditable
	@abstract Indicates if the view allows the user to edit the certificate's trust.
*/
- (BOOL)isEditable API_AVAILABLE(macos(10.3)) API_UNAVAILABLE(ios, tvos, watchos, macCatalyst);

/*!
    @method setDisplayTrust:
	@abstract Specifies whether the user can see the certificate's trust settings.
    @param display Pass YES to display the trust settings, or NO to hide them.
	@discussion Certificate trust settings are not displayed by default.
	To show the certificate's trust settings, you must explicitly set the display value to YES.
*/
- (void)setDisplayTrust:(BOOL)display API_AVAILABLE(macos(10.3)) API_UNAVAILABLE(ios, tvos, watchos, macCatalyst);

/*!
	@method isTrustDisplayed
	@abstract Indicates if the view currently shows the certificate's trust settings.
*/
- (BOOL)isTrustDisplayed API_AVAILABLE(macos(10.3)) API_UNAVAILABLE(ios, tvos, watchos, macCatalyst);

/*!
	@method saveTrustSettings
	@abstract Saves the user's current trust settings for the displayed certificate.
	@discussion If trust settings are not editable, this method effectively does nothing.
	You can use SecTrustGetUserTrust (see <Security/SecTrust.h>) to subsequently retrieve the trust settings.
*/
- (void)saveTrustSettings API_AVAILABLE(macos(10.3)) API_UNAVAILABLE(ios, tvos, watchos, macCatalyst);

/*!
    @method setDisplayDetails:
	@abstract Specifies whether the user can see the certificate's entire contents.
    @param display Pass YES to display the certificate's details, or NO to hide them.
	@discussion For behavioral compatibility with Panther, certificate details are displayed by default.
	To hide the details of a certificate, you must explicitly set the display value to NO.
*/
- (void)setDisplayDetails:(BOOL)display API_AVAILABLE(macos(10.4)) API_UNAVAILABLE(ios, tvos, watchos, macCatalyst);

/*!
	@method detailsDisplayed
	@abstract Indicates if the view currently shows the certificate's details.
*/
- (BOOL)detailsDisplayed API_AVAILABLE(macos(10.4)) API_UNAVAILABLE(ios, tvos, watchos, macCatalyst);

/*!
    @method setDetailsDisclosed:
	@abstract Specifies whether the certificate details subview is disclosed (i.e. the triangle is turned down).
    @param disclosed Pass YES to disclose the certificate details subview, or NO to collapse it.
	@discussion By default, the certificate details subview is not disclosed.
	Note that changing the disclosure state of a line item does not affect whether the item itself is shown;
	use setDisplayDetails: to cause it to be displayed or hidden.
*/
- (void)setDetailsDisclosed:(BOOL)disclosed API_AVAILABLE(macos(10.5)) API_UNAVAILABLE(ios, tvos, watchos, macCatalyst);

/*!
	@method detailsDisclosed
	@abstract Indicates if the view currently discloses the certificate's details.
*/
- (BOOL)detailsDisclosed API_AVAILABLE(macos(10.5)) API_UNAVAILABLE(ios, tvos, watchos, macCatalyst);

/*!
    @method setPoliciesDisclosed:
	@abstract Specifies whether the trust policy settings are disclosed (i.e. the triangle is turned down).
    @param disclosed Pass YES to disclose the trust policies subview, or NO to collapse it.
	@discussion By default, the trust policies subview is not disclosed.
	Note that changing the disclosure state of a line item does not affect whether the item itself is shown;
	use setDisplayTrust: to cause it to be displayed or hidden.
*/
- (void)setPoliciesDisclosed:(BOOL)disclosed API_AVAILABLE(macos(10.5)) API_UNAVAILABLE(ios, tvos, watchos, macCatalyst);

/*!
	@method policiesDisclosed
	@abstract Indicates if the view currently discloses the trust policy settings.
*/
- (BOOL)policiesDisclosed API_AVAILABLE(macos(10.5)) API_UNAVAILABLE(ios, tvos, watchos, macCatalyst);

@end

/* Notifications */

APPKIT_EXTERN NSString *SFCertificateViewDisclosureStateDidChange; /* sent when disclosure status changes */

API_UNAVAILABLE_END

#endif /* !_SFCERTIFICATEVIEW_H_ */

