//
//  CPGridTemplate.h
//  CarPlay
//
//  Copyright © 2018 Apple Inc. All rights reserved.
//

#import <CarPlay/CPBarButtonProviding.h>
#import <CarPlay/CPGridButton.h>
#import <CarPlay/CPTemplate.h>

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(12.0)) API_UNAVAILABLE(macos, watchos, tvos)
@interface CPGridTemplate : CPTemplate <CPBarButtonProviding>

/**
 Initialize a grid template with an array of @c CPGridButton and a title.
 @note A grid template will only display the first 8 buttons in the provided gridButtons array.
 A grid template presenting more than 4 buttons will balance the buttons between 2 rows.
 */
- (instancetype)initWithTitle:(nullable NSString *)title
                  gridButtons:(NSArray <CPGridButton *> *)gridButtons;

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

/**
 Array of grid buttons displayed on the template
 */
@property (nonatomic, readonly) NSArray <CPGridButton *> *gridButtons;

/**
 Title shown in template's navigation bar
 */
@property (nonatomic, readonly) NSString *title;

@end

NS_ASSUME_NONNULL_END
