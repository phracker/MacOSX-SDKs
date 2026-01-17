/*	
    AutomatorErrors.h
    Copyright (C) 2006, 2014 Apple Inc. All rights reserved.
    
    Public header file.
*/

#import <Foundation/Foundation.h> // NS_ENUM, NSString, ...

API_UNAVAILABLE_BEGIN(ios)

// Domain for all Automator Errors
#define AMAutomatorErrorDomain @"com.apple.Automator"

// NSError keys in userInfo

// AMAction, returns a pointer to the action which caused the error
#define AMActionErrorKey @"AMActionErrorKey"

// NSError codes in AMAutomatorErrorDomain
typedef NS_ENUM(NSInteger, AMErrorCode)
{

	// Workflow errors
	AMWorkflowNewerVersionError = -100, // The workflow was saved with a newer version of Automator
	AMWorkflowPropertyListInvalidError = -101, // The workflow's property list is invalid
	AMWorkflowNewerActionVersionError = -111, // A newer version of the action is installed
	AMWorkflowOlderActionVersionError = -112, // An older version of the action is installed
	AMWorkflowActionsNotLoadedError = -113, // One of the actions of the workflow could not be loaded
	AMWorkflowNoEnabledActionsError = -114, // There are no enabled actions in thre Workflow

	// Workflow runtime errors
	AMUserCanceledError = -128, // Same as userCanceledErr in MacErrors.h

	// Action errors
	AMNoSuchActionError = -200, // The action could not be located.
	AMActionNotLoadableError = -201, // The action could not be loaded because its executable is not loadable.
	AMActionArchitectureMismatchError = -202, // The action does not contain a version for the current architecture.
	AMActionRuntimeMismatchError = -203, // The action is not compatible with the current application.
	AMActionLoadError = -204, // The action could not be loaded because it is damaged or missing necessary resources.
	AMActionLinkError = -205, // The action could not be loaded.
	AMActionApplicationResourceError = -206, // The action could not be loaded because the required application is missing
	AMActionApplicationVersionResourceError = -207, // The action could not be loaded because the required application is the wrong version
	AMActionFileResourceError = -208, // The action could not be loaded because the required file is missing or is the wrong version
	AMActionLicenseResourceError = -209, // The action could not be loaded because the required license is missing
	AMActionRequiredActionResourceError = -210, // The action could not be loaded because the required action is missing or has the wrong version
	AMActionInitializationError = -211, // The action could not be instantiated (reason unknown)
	AMActionExecutionError = -212, // The action received an error while executing (reason unknown)
	AMActionExceptionError = -213, // The action received an exception while executing
	AMActionPropertyListInvalidError = -214, // The action's property list is invalid
	AMActionInsufficientDataError = -215, // The action requires input data to run but none was supplied
	AMActionIsDeprecatedError = -216, // The action is deprecated
	AMActionFailedGatekeeperError = -217, // The action signature doesn't meet Gatekeeper policy
	AMActionSignatureCorruptError = -218, // The action signature is corrupt
	AMActionQuarantineError = -219, // The action is quarantined
	AMActionXProtectError = -220, // The action could not be analyzed by XProtect
	AMActionMalwareError = -221, // The action has been detected as malware by XProtect
	AMActionThirdPartyActionsNotAllowedError = -222, // The is a third party action, and loading it has not been allowed by the user. The user must enabled loading of third party actions inside Automator.
	AMActionXPCError = -223, // The remote process running the action has crashed.

	// Data conversion errors
	AMConversionNotPossibleError = -300, // Conversion not possible
	AMConversionNoDataError = -301, // Conversion returns no data
	AMConversionFailedError = -302 // Conversion failed (reason unknown)
};

API_UNAVAILABLE_END
