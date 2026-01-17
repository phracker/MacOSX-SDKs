//
//  MFMailComposeControllerDeferredAction.h
//  MessageUI
//
//  Copyright © 2023 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

typedef NS_ENUM(NSInteger, MFMailComposeControllerDeferredAction) {
    MFMailComposeControllerDeferredActionNone,
    MFMailComposeControllerDeferredActionAdjustInsertionPoint,
    MFMailComposeControllerDeferredActionAddMissingRecipients,
};
