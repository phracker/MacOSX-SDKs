//
//  CNMutableGroup.h
//  Contacts
//
//  Copyright (c) 2015 Apple Inc. All rights reserved.
//

#import <Contacts/CNGroup.h>

NS_ASSUME_NONNULL_BEGIN


/*!
 * @abstract A mutable value object representing a group.
 *
 * @discussion CNMutableGroup is not thread safe.
 */
NS_CLASS_AVAILABLE(10_11, 9_0)
@interface CNMutableGroup : CNGroup

@property (copy, NS_NONATOMIC_IOSONLY) NSString *name;

@end

NS_ASSUME_NONNULL_END
