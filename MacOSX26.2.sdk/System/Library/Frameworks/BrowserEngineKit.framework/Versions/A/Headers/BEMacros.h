//
//  BEMacros.h
//

#import <BrowserEngineCore/BEMacros.h>

#define BROWSERENGINEKIT_HAS_UIINTERACTION __has_include(<UIKit/UIInteraction.h>)
#define BROWSERENGINEKIT_HAS_UIVIEW __has_include(<UIKit/UIView.h>)
#define BROWSERENGINEKIT_HAS_UIKIT __has_include(<UIKit/UIKit.h>)

#define BROWSERENGINEKIT_HAS_LIBXPC TARGET_OS_IOS && !TARGET_OS_VISION
