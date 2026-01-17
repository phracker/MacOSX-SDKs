//
//  ILClassificationActions.h
//  IdentityLookup
//
//  Copyright © 2018 Apple. All rights reserved.
//

NS_ASSUME_NONNULL_BEGIN

/// Describes various classification actions.
typedef NS_ENUM(NSInteger, ILClassificationAction) {
    /// Indicate that no action is requested.
    ILClassificationActionNone = 0,
    
    /// Report communication(s) as not junk.
    ILClassificationActionReportNotJunk = 1,
    
    /// Report communication(s) as junk.
    ILClassificationActionReportJunk = 2,
    
    /// Report communication(s) as junk and block the sender.
    ILClassificationActionReportJunkAndBlockSender = 3,
} API_AVAILABLE(ios(12.0), macCatalyst(13.0)) API_UNAVAILABLE( tvos) API_UNAVAILABLE(macos, watchos);

NS_ASSUME_NONNULL_END

