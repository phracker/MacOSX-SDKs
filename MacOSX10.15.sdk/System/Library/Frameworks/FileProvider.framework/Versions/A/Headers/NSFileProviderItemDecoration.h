//
//  NSFileProviderItemDecoration.h
//  FileProvider
//
//  Created by Johannes Fortmann on 1/16/19.
//  Copyright © 2019 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <FileProvider/NSFileProviderDefines.h>
#import <FileProvider/NSFileProviderItem.h>

typedef NSString *NSFileProviderItemDecorationIdentifier NS_TYPED_EXTENSIBLE_ENUM;

/**
 Decorations are defined in the extension's Info.plist by adding a
 NSFileProviderDecorations key with one or many entries to the NSExtension dictionary.

    <key>NSFileProviderDecorations</key>
    <array>
    	<dict>
    		<key>Identifier</key>
    		<string>$(PRODUCT_BUNDLE_IDENTIFIER).hasComments</string>
    		<key>BadgeImageType</key>
    		<string>com.someone.item.decoration.unreadCommentIcon</string>
    		<key>Category</key>
    		<string>Badge</string>
    		<key>LocalizedTitle</key>
    		<dict>
    			<key>NSStringFormat</key>
    			<string>%@ unread comments</string>
    			<key>NSStringFormatValues</key>
    			<array>
    				<string>item.userInfo.unreadCommentCount</string>
    			</array>
    		</dict>
    	</dict>
    </array>

 The keys for each entry are defined as follows:
 Key            | Property
 ---------------|----------
 Identifier     | The identifier used to refer to this decoration in the item definition (as type `NSFileProviderItemDecorationIdentifier`).
 BadgeImageType | The overlay UTI (see below)
 Label          | A localizable title, to be used in detail views, on mouse over and for voice over
 Category       | The position of the decoration: one of 'Badge', 'Sharing', 'FolderStatus' or 'FolderBadge'

 At rendering time, the icon for the UTI specified by 'BadgeImageType' will be looked up.
 The UTI must conform to 'com.apple.icon-decoration.badge'.

 Decorations from different categories are presented in different places in the UI:

 Category     | Location
 -------------|----------
 Badge        | On top of the icon; only the first badge is displayed.
 Sharing      | Below the icon. If multiple Sharing decorations are present, the first one that fits will be shown.
 FolderStatus | On open folders, below the folders items. All FolderStatus decorations will be shown, concatenated.
 FolderBadge  | Embossed on top of the folder icon. Only the first badge is displayed. Only valid for folders.


*/

@protocol NSFileProviderItemDecorating <NSFileProviderItem>
/**
 Returns an array of decorations for the item.

 To adopt this protocol, implement the -decorations method on your NSFileProviderItem to return valid decoration identifiers
 from your Info.plist.
 */
 @property (nonatomic, nullable, readonly, strong) NSArray <NSFileProviderItemDecorationIdentifier> *decorations API_UNAVAILABLE(watchos, tvos) API_UNAVAILABLE(ios, macos);
@end
