//
//  FPUIActionExtensionViewController.h
//  FileProviderUI
//
//  Copyright © 2016 Apple Inc. All rights reserved.
//

#import <FileProviderUI/FPUIBase.h>

#if TARGET_OS_OSX
#import <AppKit/AppKit.h>
#else
#import <UIKit/UIKit.h>
#endif

#if __has_include(<FileProvider/FileProvider.h>)
#import <FileProvider/FileProvider.h>
#else
typedef NSString *NSFileProviderItemIdentifier NS_EXTENSIBLE_STRING_ENUM;
#endif

#import <FileProviderUI/FPUIActionExtensionContext.h>

NS_ASSUME_NONNULL_BEGIN

FPUI_AVAILABLE(ios(11.0), macos(10.15))
API_UNAVAILABLE(macCatalyst)
#if TARGET_OS_OSX
@interface FPUIActionExtensionViewController : NSViewController
#else
@interface FPUIActionExtensionViewController : UIViewController
#endif

@property (nonatomic, readonly, strong) FPUIActionExtensionContext *extensionContext;

// To be overridden by the subclass
- (void)prepareForError:(NSError *)error NS_SWIFT_NAME( prepare(forError:) );

// To be overridden by the subclass
- (void)prepareForActionWithIdentifier:(NSString *)actionIdentifier itemIdentifiers:(NSArray <NSFileProviderItemIdentifier> *)itemIdentifiers NS_SWIFT_NAME( prepare(forAction:itemIdentifiers:) );
    
@end

NS_ASSUME_NONNULL_END
