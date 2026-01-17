/*
	SFCertificateView.h
	SecurityInterface
	Copyright (c) 2002-2003, Apple Computer, Inc.
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
    void *_reserved;
}

/*!
    @method setCertificate:
	@abstract Changes the certificate that's associated with the view.
    @param certificate The new certificate for the view.
*/
- (void)setCertificate:(SecCertificateRef)certificate;

/*!
	@method certificate
	@abstract Returns the certificate associated with the view.
*/
- (SecCertificateRef)certificate;

/*!
    @method setEditableTrust:
	@abstract Allows the user to change the certificate's trust settings in the view.
    @param editable Pass YES if the trust settings should be editable, NO if not.
*/
- (void)setEditableTrust:(BOOL)editable;

/*!
	@method isEditable
	@abstract Indicates if the view allows the user to edit the certificate's trust.
*/
- (BOOL)isEditable;

/*!
    @method setDisplayTrust:
	@abstract Specifies whether the certificate's trust settings are shown in the view.
    @param display Pass YES if the trust settings should be displayed, NO if not.
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
	If trust settings are not editable, this method effectively does nothing.
	You can use SecTrustGetUserTrust (SecTrust.h) to subsequently retrieve the trust settings.
*/
- (void)saveTrustSettings;

@end

#endif /* !_SFCERTIFICATEVIEW_H_ */

