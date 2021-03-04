//
//  PhotosUITypes.h
//  PhotosUI
//
//  Copyright © 2017 Apple. All rights reserved.
//

#import <Foundation/Foundation.h>

/**
 Extensible enumerator for PHProjectType. See PHProjectExtensionController.h for more information.
 */
typedef NSString * PHProjectType NS_EXTENSIBLE_STRING_ENUM;
extern PHProjectType const PHProjectTypeUndefined	API_AVAILABLE(macos(10.13));

/**
 Extensible enumerator for PHProjectCategory.
 Add a PHProjectCategory key to the NSExtensionAttributes dictionary of your project extension's Info.plist.
 The value for the key should be an array which can contain any of the PHProjectCategory values declared in this framework.
 
 Sample exerpt from an extension's Info.plist:
 <!-- […] -->
 <key>NSExtension</key>
 <dict>
     <key>NSExtensionAttributes</key>
     <dict>
         <key>PHProjectCategory</key>
         <array>
             <string>book</string>
             <string>card</string>
         </array>
     </dict>
 <!-- […] -->
 */
typedef NSString * PHProjectCategory NS_TYPED_ENUM;
extern PHProjectCategory const PHProjectCategoryBook API_AVAILABLE(macos(10.14)); // value: book
extern PHProjectCategory const PHProjectCategoryCalendar API_AVAILABLE(macos(10.14)); // value: calendar
extern PHProjectCategory const PHProjectCategoryCard API_AVAILABLE(macos(10.14)); // value: card
extern PHProjectCategory const PHProjectCategoryPrints API_AVAILABLE(macos(10.14)); // value: prints
extern PHProjectCategory const PHProjectCategorySlideshow API_AVAILABLE(macos(10.14)); // value: slideshow
extern PHProjectCategory const PHProjectCategoryWallDecor API_AVAILABLE(macos(10.14)); // value: walldecor
extern PHProjectCategory const PHProjectCategoryOther API_AVAILABLE(macos(10.14)); // value: other
/// PHProjectCategoryUndefined is used to indicate that -[PHProjectExtensionController typeDescriptionDataSourceForCategory:invalidator:]
/// should return the data source which provides all project types descriptions.
extern PHProjectCategory const PHProjectCategoryUndefined API_AVAILABLE(macos(10.14.2)); // value: undefined
