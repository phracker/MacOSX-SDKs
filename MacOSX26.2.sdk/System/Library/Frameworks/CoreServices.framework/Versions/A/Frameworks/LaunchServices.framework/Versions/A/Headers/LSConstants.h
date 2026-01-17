//
//  LSConstants.h
//
//  Copyright © 2022 Apple. All rights reserved.
//

#ifndef __LSCONSTANTS__
#define __LSCONSTANTS__ 1

#include <MacTypes.h>
#include <Availability.h>
#include <CoreFoundation/CFAvailability.h>

#if PRAGMA_ONCE
#pragma once
#endif

/* ======================================================================================================== */
/* LaunchServices Constants                                                                                 */
/* ======================================================================================================== */
/*  -10300 .. -10399, -10400 .. -10449, -10650..-10699, -10810 .. -10829 are all reserved for LS; -10680 .. -10699 are internal errors */

CF_ENUM(OSStatus) {
	kLSNo32BitEnvironmentErr      = -10386, //!< i386 is no longer supported
	kLSMalformedLocErr            = -10400, //!< malformed internet locator file
	kLSAppInTrashErr              = -10660, //!< The app cannot be run when inside a Trash folder
	kLSExecutableIncorrectFormat  = -10661, //!< No compatible executable was found
	kLSAttributeNotFoundErr       = -10662, //!< An item attribute value could not be found with the specified name
	kLSAttributeNotSettableErr    = -10663, //!< The attribute is not settable
	kLSIncompatibleApplicationVersionErr = -10664, //!< The app is incompatible with the current OS
	kLSNoRosettaEnvironmentErr    = -10665, //!< PowerPC apps are no longer supported
	kLSGarbageCollectionUnsupportedErr = -10666, //!< Objective-C garbage collection is no longer supported
	// internal-error = -10667
	kLSUnknownErr                 = -10810, //!< Unexpected internal error
	kLSNotAnApplicationErr        = -10811, //!< Item needs to be an application, but is not
	kLSNotInitializedErr          = -10812, //!< Not used in 10.2 and later
	kLSDataUnavailableErr         = -10813, //!< E.g. no kind string
	kLSApplicationNotFoundErr     = -10814, //!< E.g. no application claims the file
	kLSUnknownTypeErr             = -10815, //!< Don't know anything about the type of the item
	kLSDataTooOldErr              = -10816, //!< Not used in 10.3 and later
	kLSDataErr                    = -10817, //!< Not used in 10.4 and later
	kLSLaunchInProgressErr        = -10818, //!< E.g. launching an already launching application
	kLSNotRegisteredErr           = -10819, //!< Not used in 10.3 and later
	kLSAppDoesNotClaimTypeErr     = -10820, //!< One or more documents are of types (and/or one or more URLs are of schemes) not supported by the target application (sandboxed callers only)
	kLSAppDoesNotSupportSchemeWarning = -10821, //!< Not used in 10.2 and later
	kLSServerCommunicationErr     = -10822, //!< The server process (registration and recent items) is not available
	kLSCannotSetInfoErr           = -10823, //!< The extension visibility on this item cannot be changed
	kLSNoRegistrationInfoErr      = -10824, //!< The item contains no registration info
	kLSIncompatibleSystemVersionErr = -10825, //!< The app cannot run on the current OS version
	kLSNoLaunchPermissionErr      = -10826, //!< User doesn't have permission to launch the app (managed networks)
	kLSNoExecutableErr            = -10827, //!< The executable is missing
	kLSNoClassicEnvironmentErr    = -10828, //!< The Classic environment was required but is not available
	kLSMultipleSessionsNotSupportedErr = -10829, //!< The app cannot run simultaneously in two different sessions
};

typedef CF_OPTIONS(OptionBits, LSRolesMask) {
	kLSRolesNone                  = 0x00000001, //!< no claim is made about support for this type/scheme
	kLSRolesViewer                = 0x00000002, //!< claim to view items of this type
	kLSRolesEditor                = 0x00000004, //!< claim to edit items of this type/scheme
	kLSRolesShell                 = 0x00000008, //!< claim to execute items of this type
	kLSRolesAll                   = (UInt32)0xFFFFFFFF //!< claim to do it all
};

CF_ENUM(OSType) {
	kLSUnknownType                = 0,
	kLSUnknownCreator             = 0
};

#endif // __LSCONSTANTS__
