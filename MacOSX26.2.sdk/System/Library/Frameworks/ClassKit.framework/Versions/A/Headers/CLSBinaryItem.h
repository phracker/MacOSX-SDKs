//
//  CLSBinaryItem.h
//  ClassKit
//
//  Copyright © 2018-2023 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <ClassKit/CLSActivityItem.h>

NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(NSInteger, CLSBinaryValueType) {
    CLSBinaryValueTypeTrueFalse = 0,
    CLSBinaryValueTypePassFail,
    CLSBinaryValueTypeYesNo,
    CLSBinaryValueTypeCorrectIncorrect API_AVAILABLE(ios(12.2), macos(11.0), macCatalyst(14.0)) API_UNAVAILABLE(watchos, tvos),
} API_AVAILABLE(ios(11.3), macos(11.0), macCatalyst(14.0)) API_UNAVAILABLE(watchos, tvos);

/*!
 @abstract      CLSBinaryItem represents user generated information that is true or false, pass or fail, yes or no.
 */
API_AVAILABLE(ios(11.3), macos(11.0), macCatalyst(14.0)) API_UNAVAILABLE(watchos, tvos)
@interface CLSBinaryItem : CLSActivityItem

/*!
 @abstract      True or false value.
 */
@property (nonatomic, assign) BOOL value;

/*!
 @abstract      Value type of this CLSBinaryItem.
 @discussion    The type that best describes this CLSBinaryItem value.
 */
@property (nonatomic, assign, readonly) CLSBinaryValueType valueType;

/*!
 @abstract      Create an item that represents a binary value
 @param         title           Title of the CLSBinaryItem.
 @param         identifier      An identifier that is unique within its owning activity.
 @param         valueType       The type of binary value. Ex. pass or fail.
 */
- (instancetype)initWithIdentifier:(NSString *)identifier
                             title:(NSString *)title
                              type:(CLSBinaryValueType)valueType NS_DESIGNATED_INITIALIZER;

@end

NS_ASSUME_NONNULL_END
