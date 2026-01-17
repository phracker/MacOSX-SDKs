/*
	SFCertificateView.h
	SecurityInterface
	Copyright (c) 2002-2004 Apple Computer, Inc.
	All rights reserved.
*/

#ifndef _SFCERTIFICATEVIEW_H_
#define _SFCERTIFICATEVIEW_H_

#import <AppKit/AppKit.h>
#include <Security/SecCertificate.h>

/*!
	@class SFCertificateView
    @abstract SFCertificateView is a NSView that displays the contents of a certificate.
*/

@interface SFCertificateView : NSView
{
@private
    id _reserved;
}

/*!
    @method setCertificate:
	@abstract Specifies the certificate that's displayed in the view.
    @param certificate The new certificate for the view.
*/
- (void)setCertificate:(SecCertificateRef)certificate;

/*!
	@method certificate
	@abstract Returns the certificate currently displayed in the view.
*/
- (SecCertificateRef)certificate;

/*!
    @method setEditableTrust:
	@abstract Specifies whether the user can edit the certificate's trust settings.
    @param editable Pass YES if the trust settings should be editable.
*/
- (void)setEditableTrust:(BOOL)editable;

/*!
	@method isEditable
	@abstract Indicates if the view allows the user to edit the certificate's trust.
*/
- (BOOL)isEditable;

/*!
    @method setDisplayTrust:
	@abstract Specifies whether the user can see the certificate's trust settings.
    @param display Pass YES to display the trust settings, or NO to hide them.
	@discussion Certificate trust settings are not displayed by default.
	To show the certificate's trust settings, you must explicitly set the display value to YES.
*/
- (void)setDisplayTrust:(BOOL)display;

/*!
	@method isTrustDisplayed
	@abstract Indicates if the view currently shows the certificate's trust settings.
*/
- (BOOL)isTrustDisplayed;

/*!
	@method saveTrustSettings
	@abstract Saves the user's current trust settings for the displayed certificate.
	@discussion If trust settings are not editable, this method effectively does nothing.
	You can use SecTrustGetUserTrust (see <Security/SecTrust.h>) to subsequently retrieve the trust settings.
*/
- (void)saveTrustSettings;

/*!
    @method setDisplayDetails:
	@abstract Specifies whether the user can see the certificate's entire contents.
    @param display Pass YES to display the certificate's details, or NO to hide them.
	@discussion For behavioral compatibility with Panther, certificate details are displayed by default.
	To hide the details of a certificate, you must explicitly set the display value to NO.
*/
- (void)setDisplayDetails:(BOOL)display;

/*!
	@method detailsDisplayed
	@abstract Indicates if the view currently shows the certificate's details.
*/
- (BOOL)detailsDisplayed;

/*!
    @method setPolicies:
	@abstract Specifies one or more policies that apply to the displayed certificate.
    @param policies The policies to use when evaluating this certificate's status.
		You can pass either a SecPolicyRef or a NSArray (containing one or more SecPolicyRef instances) in this parameter.
		If policies is set to nil, the Apple X.509 Basic Policy will be used.
	@discussion Applications will typically display a SFCertificateView in the context of a specific usage, such as SSL or S/MIME.
	You should set only the policy references which apply to your intended usage.
*/
- (void)setPolicies:(id)policies;

/*!
    @method policies
	@abstract Returns an array of policies used to evaluate the status of the displayed certificate.
	@discussion This method returns an autoreleased NSArray containing one or more SecPolicyRef instances, as set by a previous
	setPolicies: call. The array will always contain at least one item (the Apple X.509 Basic Policy).
*/
- (NSArray *)policies;


@end

#endif /* !_SFCERTIFICATEVIEW_H_ */

