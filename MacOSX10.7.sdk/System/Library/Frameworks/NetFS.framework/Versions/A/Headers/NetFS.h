/*
 *  NetFS.h
 *
 *  Copyright (c) 2008-2009 Apple Inc. All rights reserved.
 */
#ifndef _NETFS_H_
#define _NETFS_H_

#include <CoreFoundation/CoreFoundation.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef SInt32 netfsError;

/*
 * Dictionary keys for the server parameters dictionary returned by
 * GetServerInfo methods and for the open options passed to OpenSession
 * methods.
 */

/*
 * For GetServerInfo, information about the authentication for the connection;
 * for OpenSession, information about the authentication to use for the
 * connection.
 *
 * This is a dictionary as returned by NAHSelectionCopyAuthInfo().
 */
#define kNetFSAuthenticationInfoKey	CFSTR("AuthenticationInfo")

/*
 * Dictionary keys for the server parameters dictionary returned by
 * GetServerInfo methods.
 *
 * Note:
 * 1)  If an authentication mechanism that uses an authentication info
 *     dictionary, such as Kerberos or NTLMSSP, is supported, then
 *     kNetFSAuthenticationInfoKey is that dictionary
 */
#define kNetFSServerDisplayNameKey	CFSTR("ServerDisplayName")
#define kNetFSSupportsChangePasswordKey	CFSTR("SupportsChangePassword")
#define kNetFSSupportsGuestKey		CFSTR("SupportsGuest")
#define kNetFSSupportsKerberosKey	CFSTR("SupportsKerberos")
#define kNetFSGuestOnlyKey		CFSTR("GuestOnly")
#define kNetFSNoMountAuthenticationKey	CFSTR("NoMountAuthentication")
/*
 * XXX - the strings for these will change when NetAuth changes to
 * use these #defines rather than the kMountedBy... #defines.
 */
#define kNetFSConnectedWithAuthenticationInfoKey	CFSTR("ConnectedWithAuthenticationInfo")
#define kNetFSConnectedAsUserKey			CFSTR("MountedByUser")
#define kNetFSConnectedAsGuestKey			CFSTR("MountedByGuest")
#define kNetFSConnectedMultiUserKey			CFSTR("ConnectedMultiUser")

#define kNetFSMechTypesSupportedKey	CFSTR("MechTypesSupported")

/*
 * Dictionary keys for the URL parameters dictionary returned by ParseURL
 * methods and passed as an argument to CreateURL methods.
 */
#define kNetFSSchemeKey			CFSTR("Scheme")
#define kNetFSHostKey			CFSTR("Host")
#define kNetFSAlternatePortKey		CFSTR("AlternatePort")
#define kNetFSAuthorityParamsKey	CFSTR("AuthorityParams")
#define kNetFSUserNameKey		CFSTR("UserName")
#define kNetFSPasswordKey		CFSTR("Password")
#define kNetFSPathKey			CFSTR("Path")

/*
 * Dictionary keys for the open options passed to OpenSession methods.
 *
 * kNetFSNoUserPreferencesKey is set when automounting volumes, as we
 * might be automounting a user's home directory, and can't look in that
 * directory for preferences before we mount that directory.
 */
#define kNetFSNoUserPreferencesKey	CFSTR("NoUserPreferences")
#define kNetFSForceNewSessionKey	CFSTR("ForceNewSession")
#define kNetFSUseAuthenticationInfoKey	CFSTR("UseAuthenticationInfo")
#define kNetFSUseGuestKey		CFSTR("Guest")
#define kNetFSChangePasswordKey		CFSTR("ChangePassword")
#define kNetFSAllowLoopbackKey		CFSTR("AllowLoopback")

/*
 * XXX - for backwards compatibility.
 * Use kNetFSUseAuthenticationInfoKey instead.
 */
#define kNetFSUseKerberosKey		CFSTR("Kerberos")

/*
 * Dictionary keys for the session information returned by OpenSession
 * and GetMountInfo methods.
 */
#define kNetFSMountedWithAuthenticationInfoKey	CFSTR("MountedWithAuthenticationInfo")
#define kNetFSMountedByUserKey			CFSTR("MountedByUser")
#define kNetFSMountedByGuestKey			CFSTR("MountedByGuest")
#define kNetFSMountedMultiUserKey		CFSTR("MountedMultiUser")

/*
 * XXX - for backwards compatibility.
 * Use kNetFSMountedWithAuthenticationInfoKey instead.
 */
#define	kNetFSMountedByKerberosKey	CFSTR("MountedByKerberos")

/*
 * Additional non-errno values that can be returned by various routines.
 *
 * ENETFSPWDNEEDSCHANGE should be returned if the password needs to be
 * changed, for whatever reason (expired, admin set the "must change"
 * bit, new account so the "must change" bit was set by default, etc.).
 * It has the same numerical value as kFPPwdNeedsChangeErr/afpPwdNeedsChangeErr,
 * which is the AFP error for "you must change this, for a reason other
 * than 'it expired'".
 *
 * XXX - AFP and SMB both distinguish between "your password has expired"
 * and "your password must be changed even though it hasn't yet expired".
 * We could have separate errors for them, but that would be useful only
 * if it's useful to the user to know why they have to change their
 * password; in *either* case they'll have to change it, so I'm not sure
 * what they'd do differently in the two different cases.
 *
 * ENETFSPWDPOLICY should be returned if you're trying to change the
 * password and the server rejects the choice of password, for whatever
 * reason.  It has the same numerical value as kFPwdPolicyErr/afpPwdPolicyErr,
 * which is the AFP error for "that password doesn't conform to the
 * server's password policy".
 *
 * XXX - AFP has different errors for "your new password is the same as
 * the old password" and "your password is too short"; we could add
 * errors for those.  SMB has errors such as NT_STATUS_PWD_TOO_SHORT,
 * NT_STATUS_PWD_TOO_RECENT, NT_STATUS_PWD_HISTORY_CONFLICT, and
 * NT_STATUS_PASSWORD_RESTRICTION; we could return separate errors
 * for those as well.
 *
 * ENETFSACCOUNTRESTRICTED should be returned if the account has been
 * locked, or is only allowed to access the server during certain time
 * periods and we're not in one of those time periods, or some other such
 * account restriction.  There *is* no specific AFP error for that, so we
 * picked -5999 in the hopes that it wouldn't collide with any other error.
 *
 * ENETFSNOSHARESAVAIL should be returned if the user can log in but
 * no share points are available to them.  There is no AFP error for
 * that, so we picked -5998.
 *
 * ENETFSNOAUTHMECHSUPP should be returned if the server does not support
 * any authentication mechanisms that the client can use.  There is no
 * AFP error for that, so we picked -5997.
 *
 * ENETFSNOPROTOVERSSUPP should be returned if the server does not support
 * any of the versions/dialects of the file access protocol that the
 * client can use.  There is no AFP error for that, so we picked -5996.
 *
 * XXX - SMB has a bunch of different errors giving more detail as to the
 * reason why the account is restricted; we could have separate errors
 * for all of them, so that different messages could be displayed.
 */
#define ENETFSPWDNEEDSCHANGE		-5045
#define ENETFSPWDPOLICY			-5046
#define ENETFSACCOUNTRESTRICTED		-5999
#define ENETFSNOSHARESAVAIL		-5998
#define ENETFSNOAUTHMECHSUPP		-5997
#define ENETFSNOPROTOVERSSUPP		-5996

/*
 * Dictionary keys for options passed to EnumerateShares methods.
 */
#define kNetFSGetAccessRightsKey	CFSTR("GetAccessRights")

/*
 * Dictionary keys for the dictionary for a sharepoint, as returned
 * by EnumerateShares methods in the dictionary of sharepoints.
 * Entries in the dictionary of sharepoints have the sharepoint name
 * as the key and the dictionary for that sharepoint as the value.
 * Also used for the dictionary of mount information returned by
 * Mount methods.
 *
 * Note:
 * 1)  only one of the following may be set when a sharepoint is currently
 *     mounted - kNetFSMountedByUser or kNetFSMountedByGuest
 * 2)  If the sharepoint is currently mounted, then kNetFSMountPathKey is
 *     the path to the mounted sharepoint
 * 3)  kNetFSDisplayNameKey is optional and if not present, then use the
 *     name of the dictionary to display the sharepoint name.
 *     kNetFSDisplayName is for sharepoint names that need special handling
 *     (ie '/' in AFP sharepoint name).
 * 4)  If there are no available sharepoints, then an empty dictionary is
 *     returned with no error.
 */
#define kNetFSAlreadyMountedKey		CFSTR("AlreadyMounted")
#define kNetFSMountPathKey		CFSTR("MountPath")
//#define kNetFSMountedByUserKey	CFSTR("MountedByUser")		/* defined for OpenSession above */
//#define kNetFSMountedByGuestKey	CFSTR("MountedByGuest")		/* defined for OpenSession above */
//#define kNetFSMountedByKerberosKey	CFSTR("MountedByKerberos")	/* defined for OpenSession above */
//#define kNetFSMountedMultiUserKey	CFSTR("MountedMultiUser")	/* defined for OpenSession above */
#define kNetFSHasPasswordKey		CFSTR("HasPassword")
#define kNetFSIsHiddenKey		CFSTR("IsHidden")
#define kNetFSPrinterShareKey		CFSTR("PrinterShare")
#define kNetFSAccessRightsKey		CFSTR("AccessRights")
#define kNetFSDisplayNameKey		CFSTR("DisplayName")

/*
 * Dictionary keys for the mount options dictionary passed to Mount methods.
 *
 * Note:
 * 1)  kNetFSMountFlagsKey is a collection of MNT_ flags for mount(2), such
 *     as MNT_DONTBROWSE, MNT_RDONLY, MNT_AUTOMOUNTED, MNT_NOSUID, MNT_NODEV,
 *     and MNT_QUARANTINE.
 * 2)  kNetFSNoUserPreferencesKey is set when automounting volumes, as we
 *     might be automounting a user's home directory, and can't look in that
 *     directory for preferences before we mount that directory
 * 3)  for file systems without the notion of shares (for the file systems
 *     we ship, that's everything except AFP and SMB; NFS has the notion
 *     of exports, at least for NFSv2 and v3, but it's a different notion,
 *     and we've always supported NFS submounts, so we continue to do so)
 *     the kNetFSAllowSubMountsKey has no effect, as there's no notion of
 *     submounts
 */
//#define kNetFSNoUserPreferencesKey	CFSTR("NoUserPreferences")	/* defined for GetServerInfo above */
#define kNetFSPasswordKey		CFSTR("Password")
#define kNetFSSoftMountKey		CFSTR("SoftMount")
//#define kNetFSForceNewSessionKey	CFSTR("ForceNewSession")	/* defined for OpenSession above */
#define kNetFSMountFlagsKey		CFSTR("MountFlags")
#define kNetFSAllowSubMountsKey		CFSTR("AllowSubMounts")

/*
 * Dictionary keys for the mount information dictionary returned by
 * GetMountInfo methods.
 */
#define kNetFSMountedURLKey		CFSTR("MountedURL")
//#define kNetFSMountedByUserKey	CFSTR("MountedByUser")		/* defined for OpenSession above */
//#define kNetFSMountedByGuestKey	CFSTR("MountedByGuest")		/* defined for OpenSession above */
//#define kNetFSMountedByKerberosKey	CFSTR("MountedByKerberos")	/* defined for OpenSession above */
//#define kNetFSMountedMultiUserKey	CFSTR("MountedMultiUser")	/* defined for OpenSession above */

#ifdef __cplusplus
}
#endif

#endif /* !_NETFS_H_ */
