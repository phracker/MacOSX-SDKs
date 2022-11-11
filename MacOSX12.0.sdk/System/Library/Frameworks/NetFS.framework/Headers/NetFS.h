/*
 *  NetFS.h
 *
 *  Copyright (c) 2008-2009 Apple Inc. All rights reserved.
 */
#ifndef _NETFS_H_
#define _NETFS_H_

#include <CoreFoundation/CoreFoundation.h>

#ifdef __cplusplus
#define NETFS_EXPORT    extern "C" __attribute__((visibility ("default")))
#else
#define NETFS_EXPORT    extern __attribute__((visibility ("default")))
#endif

API_UNAVAILABLE_BEGIN(ios, tvos, watchos)

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

#ifndef kNAUIOptionKey
#define kNAUIOptionKey				CFSTR("UIOption")

// UIOption values				CFStringRef
#define kNAUIOptionNoUI				CFSTR("NoUI")
#define kNAUIOptionAllowUI			CFSTR("AllowUI")
#define kNAUIOptionForceUI			CFSTR("ForceUI")
#endif

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
 * 4)  kNetFSOpenURLMountKey is set to true to indicate that the mount is a
 *     result of an "openURL" event, and as such may be subject to auto-quarantine.
 */
//#define kNetFSNoUserPreferencesKey	CFSTR("NoUserPreferences")	/* defined for GetServerInfo above */
#define kNetFSPasswordKey		CFSTR("Password")
#define kNetFSSoftMountKey		CFSTR("SoftMount")
//#define kNetFSForceNewSessionKey	CFSTR("ForceNewSession")	/* defined for OpenSession above */
#define kNetFSMountFlagsKey		CFSTR("MountFlags")
#define kNetFSAllowSubMountsKey		CFSTR("AllowSubMounts")
#define kNetFSMountAtMountDirKey	CFSTR("MountAtMountDir")
#define kNetFSOpenURLMountKey           CFSTR("OpenURLMount")

/*
 * Dictionary keys for the mount information dictionary returned by
 * GetMountInfo methods.
 */
#define kNetFSMountedURLKey		CFSTR("MountedURL")
//#define kNetFSMountedByUserKey	CFSTR("MountedByUser")		/* defined for OpenSession above */
//#define kNetFSMountedByGuestKey	CFSTR("MountedByGuest")		/* defined for OpenSession above */
//#define kNetFSMountedByKerberosKey	CFSTR("MountedByKerberos")	/* defined for OpenSession above */
//#define kNetFSMountedMultiUserKey	CFSTR("MountedMultiUser")	/* defined for OpenSession above */

/*
 ********************************
 *
 * Public API for NetFS.framework
 *
 ********************************
 */
typedef void * AsyncRequestID;

/*
 * Given a URL that refers to a file server, connect to that server
 * and mount stuff.
 *
 * If the URL just specifies a server and you can't just mount the
 * "root directory" of the server, the user will be prompted with
 * a window to let them select one or more items to mount from that
 * server, otherwise whatever item the URL specifies to mount will
 * be mounted.
 *
 * If the mountpath is provided it will be used as the mount point.
 * If the mountpath is set to NULL, a default mount point will be used.
 *
 * If the user and passwd are set, they will override any user name
 * or password that may be set in the URL. These calls go through the NetAuth agent.
 * If the URL doesn't specify a password, and one is needed, the
 * user will be prompted with a window requesting password.
 *
 * Options can be provided for the session open and the mount itself.
 * If the mount is successful, the POSIX path to each mountpoint is
 * returned as a CFStringRef in mountpoints.
 *
 * If the return value is zero the mount has succeeded.
 *
 * A positive non-zero return value represents an errno value
 * (see /usr/include/sys/errno.h).  For instance, a missing mountpoint
 * error will be returned as ENOENT (2).
 *
 * A negative non-zero return value represents an OSStatus error.
 * For instance, error -128 is userCanceledErr, returned when a mount
 * operation is canceled by the user. These OSStatus errors are
 * extended to include:
 *
 *  from this header:
 *	ENETFSPWDNEEDSCHANGE		-5045
 *	ENETFSPWDPOLICY			-5046
 *	ENETFSACCOUNTRESTRICTED		-5999
 *	ENETFSNOSHARESAVAIL		-5998
 *	ENETFSNOAUTHMECHSUPP		-5997
 *	ENETFSNOPROTOVERSSUPP		-5996
 *
 *  from <NetAuth/NetAuthErrors.h>
 *	kNetAuthErrorInternal		-6600
 *	kNetAuthErrorMountFailed	-6602
 *	kNetAuthErrorNoSharesAvailable	-6003
 *	kNetAuthErrorGuestNotSupported	-6004
 *	kNetAuthErrorAlreadyClosed	-6005
 *
 */
NETFS_EXPORT int
NetFSMountURLSync(
	CFURLRef url,				// URL to mount, e.g. nfs://server/path
	CFURLRef mountpath,			// Path for the mountpoint
	CFStringRef user,			// Auth user name (overrides URL)
	CFStringRef passwd, 			// Auth password (overrides URL)
	CFMutableDictionaryRef open_options,	// Options for session open (see below)
	CFMutableDictionaryRef mount_options,	// Options for mounting (see below)
	CFArrayRef *mountpoints)		// Array of mountpoints
	__OSX_AVAILABLE_STARTING(__MAC_10_8, __IPHONE_NA);

/*
 * This is the block called at completion of NetFSMountURLAsync
 * The block receives the mount status (described above), the request ID
 * that was used for the mount, and an array of mountpoint paths.
 */
typedef	void (^NetFSMountURLBlock)(int status, AsyncRequestID requestID, CFArrayRef mountpoints);

/*
 * NetFSMountURLAsync is the same as NetFSMountURLSync except it does the
 * mount asynchronously.  If the mount_report block is non-NULL, at
 * the completion of the mount it is submitted to the dispatch queue
 * with the result of the mount, the request ID and an array of POSIX mountpoint paths.
 * The request ID can be used by NetFSMountURLCancel() to cancel
 * a pending mount request. The NetFSMountURLBlock is not submitted if
 * the request is cancelled.
 *
 * The return result is as described above for NetFSMountURLSync().
 */
NETFS_EXPORT int
NetFSMountURLAsync(
	CFURLRef url,				// URL to mount, e.g. nfs://server/path
	CFURLRef mountpath,			// Path for the mountpoint
	CFStringRef user,			// Auth user name (overrides URL)
	CFStringRef passwd, 			// Auth password (overrides URL)
	CFMutableDictionaryRef open_options,	// Options for session open (see below)
	CFMutableDictionaryRef mount_options,	// Options for mounting (see below)
	AsyncRequestID *requestID,		// ID of this pending request (see cancel)
	dispatch_queue_t dispatchq,		// Dispatch queue for the block
	NetFSMountURLBlock mount_report)	// Called at mount completion
	__OSX_AVAILABLE_STARTING(__MAC_10_8, __IPHONE_NA);
/*
 * Cancel a pending async mount request.
 * The AsyncRequestID is that returned by NetFSMountURLAsync().
 * The NetFSMountURLBlock is not called.
 */
NETFS_EXPORT int
NetFSMountURLCancel(AsyncRequestID requestID) 	__OSX_AVAILABLE_STARTING(__MAC_10_8, __IPHONE_NA);

/*
 * The following dictionary keys for open_options are supported:
 *
 *	kNetFSUseGuestKey:			Login as a guest user.
 *
 *	kNetFSAllowLoopbackKey			Allow a loopback mount.
 *
 *	kNAUIOptionKey = UIOption		Suppress authentication dialog UI.
 *
 * The following dictionary keys for mount_options are supported:
 *
 *	kNetFSMountFlagsKey = MNT_DONTBROWSE 	No browsable data here (see <sys/mount.h>).
 *
 *	kNetFSMountFlagsKey = MNT_RDONLY	A read-only mount (see <sys/mount.h>).
 *
 *	kNetFSAllowSubMountsKey = true		Allow a mount from a dir beneath the share point.
 *
 *	kNetFSSoftMountKey = true		Mount with "soft" failure semantics.
 *
 *	kNetFSMountAtMountDirKey = true		Mount on the specified mountpath instead of below it.
 *
 * Note that if kNetFSSoftMountKey isn't set, then it's set to TRUE.
 *
 ********************************
 */

/*
 * The user may enter a hostname in lieu of a full URL.
 * We need to determine an appropriate protocol for this host
 * and return a scheme from which a URL can be derived.  For
 * instance, if we determine that it's an SMB server then we
 * return "smb" which the caller can use to build a URL:
 * "smb://hostname".
 *
 * We start with a list of likely protocols, e.g. "smb", "afp"
 * and initiate a TCP connection to the port for each protocol. These
 * connect attempts run in parallel.  Then wait in a select() call to
 * see which connections are successful, or refused, or do not respond.
 * There is a preference order, even if a protocol later in the list
 * responds first, it may lose out if a protocol earlier in the list
 * responds within the timeout.
 */
NETFS_EXPORT CFStringRef
NetFSMountURLProbe(CFStringRef hostname);
        
/*
 * Given a CFURLRef localPathURL that refers to a location on a 
 * mounted network share, return the URL needed to remount that
 * volume.
 *
 * The return value is a CFURLRef of the server, or NULL if localPathURL
 * isn't a mounted network share.
 */
NETFS_EXPORT CFURLRef
NetFSCopyURLForRemountingVolume(CFURLRef localPathURL);

API_UNAVAILABLE_END

#endif /* !_NETFS_H_ */
