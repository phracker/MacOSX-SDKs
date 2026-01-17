//
//  $Id: InstallerState.h,v 1.2 2004/12/19 00:50:57 pmb Exp $
//
//  Created by Christopher Ryan on 8/19/04.
//  Copyright 2004 Apple Computer. All rights reserved.
//

#import <Cocoa/Cocoa.h>

/*!
    @const 		InstallerState_Choice_Identifier
    @abstract   Key for accessing the choice identifier from the choiceDictionary.  The value for this key is an NSString.
    @discussion Use this key with dictionary retrieved from choiceDictionaries to access the identifier for a given choice.
 				This identifier is either the package identifier attached to the choice, or the choice identifier in a distribution
 				script.
*/
extern NSString* const InstallerState_Choice_Identifier;

/*!
    @const 		InstallerState_Choice_Installed
    @abstract   Key for accessing if a choice was chosen to be installed.  The value for this key is an NSNumber.
    @discussion Use this key with the dictionary retrieved from choiceDictionaries to determine if the given choice was installed
 				(or will be installed, if installStarted is false).
*/
extern NSString* const InstallerState_Choice_Installed;				

/*!
    @const 		InstallerState_Choice_CustomLocation
    @abstract   Key for accessing choice custom location.  The value for this key is a full path to the install location.
    @discussion Certain choices can be relocated to a different location then the target.  If this choice has been relocated, this
 				value for this key when used in a choicesDictionary will be the alternate location (selected by the user).
*/
extern NSString* const InstallerState_Choice_CustomLocation;

typedef struct InstallerState_Private InstallerState_Private;

@interface InstallerState : NSObject {
	@private
	InstallerState_Private   *_private;
}

//License Related
/*!
    @method     licenseAgreed
    @abstract   Specifies the user agreed to the license, if there is no license, this will return NO.
*/
- (BOOL)licenseAgreed;

/*!
    @method     licenseAgreedLanguage
    @abstract   Specifies the language the language was last viewed or agreed with.
*/
- (NSString *)licenseAgreedLanguage;


/*!
    @method     targetVolumePath
    @abstract   Specifies the mount point of the selected target
    @discussion Only Available after target has been selected.
*/
- (NSString *)targetVolumePath;

/*!
    @method     targetPath
    @abstract   Full target path selected.
    @discussion Specifies the full path selected by the user.  This path contains the targetVolumePath.
*/
- (NSString *)targetPath;

/*!
    @method     choiceDictionaries
    @abstract   Returns an array of choice dictionaries.
    @discussion Each choice dictionary contains the keys InstallerState_Choice_Identifier,InstallerState_Choice_Installed, and optionally
 				InstallerState_Choice_CustomLocation.  These keys specify a choice and whether they were installed or not.  This is only
 				available after choice selections have been made.
*/
- (NSArray *)choiceDictionaries;

/*!
    @method     choiceDictionaryForIdentifier:
    @abstract   Retrieves choice dictionaries by identifier.
    @discussion See choiceDictionaries for the values returned.
*/
- (NSDictionary *)choiceDictionaryForIdentifier:(NSString *)choiceIdentifier;

/*!
    @method     installStarted
    @abstract   Specifies if the install process has started or not.
    @discussion Will return YES after an install has been initiated.  If YES is returned, you can assume the install has taken
 				place.
*/
- (BOOL)installStarted;

/*!
    @method     installSucceeded
    @abstract   Specifies if the install was successfull or not.
    @discussion This value is only valid if installStarted returns True.
*/
- (BOOL)installSucceeded;
@end
