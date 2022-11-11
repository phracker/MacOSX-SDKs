//
//  CPActionSheetTemplate.h
//  CarPlay
//
//  Copyright © 2018 Apple Inc. All rights reserved.
//

#import <CarPlay/CPAlertAction.h>
#import <CarPlay/CPTemplate.h>

NS_ASSUME_NONNULL_BEGIN

/**
 @c CPActionSheetTemplate represents an action sheet that must be dismissed with a button press
 before the user may return to using the app.
 */
API_AVAILABLE(ios(12.0)) API_UNAVAILABLE(macos, watchos, tvos)
@interface CPActionSheetTemplate : CPTemplate

/**
 Initialize a @c CPActionSheetTemplate with a title and/or message, and at least one action.

 @param title The title of the action sheet.
 @param message Descriptive message that provides more detail about the reason for the action sheet.
 @param actions The actions for the action sheet.
 */
- (instancetype)initWithTitle:(nullable NSString *)title message:(nullable NSString *)message actions:(NSArray<CPAlertAction *> *)actions;

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@property (nonatomic, copy, readonly, nullable) NSString *title;
@property (nonatomic, copy, readonly, nullable) NSString *message;

@property (nonatomic, strong, readonly) NSArray<CPAlertAction *> *actions;

@end

NS_ASSUME_NONNULL_END
