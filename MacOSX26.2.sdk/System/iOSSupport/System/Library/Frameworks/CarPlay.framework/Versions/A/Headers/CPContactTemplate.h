//
//  CPContactTemplate.h
//  CarPlay
//
//  Copyright © 2020 Apple Inc. All rights reserved.
//

#import <CarPlay/CPTemplate.h>
#import <CarPlay/CPContact.h>
#import <CarPlay/CPBarButtonProviding.h>

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(14.0)) API_UNAVAILABLE(tvos) API_UNAVAILABLE(macos, watchos)
CARPLAY_TEMPLATE_UI_ACTOR
@interface CPContactTemplate : CPTemplate <CPBarButtonProviding>

/**
 Initialize a @c CPContactTemplate by providing a @c CPContact.
*/
- (instancetype)initWithContact:(CPContact *)contact NS_DESIGNATED_INITIALIZER;

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

/**
 The contact currently displayed by this template. Assigning a new contact
 will update the template.
*/
@property (nonatomic, strong) CPContact *contact;

@end

NS_ASSUME_NONNULL_END
