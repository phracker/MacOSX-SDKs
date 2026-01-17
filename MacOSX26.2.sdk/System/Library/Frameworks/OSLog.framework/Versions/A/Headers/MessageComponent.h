/*
 * Copyright (c) 2018 Apple Inc. All rights reserved.
 */

#ifndef __OSLOG_MESSAGE_COMPONENT_H__
#define __OSLOG_MESSAGE_COMPONENT_H__

#ifndef __INDIRECT_OSLOG_HEADER_USER__
#error "Please use <OSLog/OSLog.h> instead of directly using this file."
#endif

NS_ASSUME_NONNULL_BEGIN

/*!
 * @enum OSLogMessageComponentArgumentCategory
 *
 * @abstract
 * The kind of data corresponding to an argument in a message
 * payload, like the number associated with a "%d" placeholder.
 * This value can be undefined if the argument data cannot be
 * decoded; for example, it may be redacted.
 */
typedef NS_ENUM(NSInteger, OSLogMessageComponentArgumentCategory) {
    OSLogMessageComponentArgumentCategoryUndefined,
    OSLogMessageComponentArgumentCategoryData,
    OSLogMessageComponentArgumentCategoryDouble,
    OSLogMessageComponentArgumentCategoryInt64,
    OSLogMessageComponentArgumentCategoryString,
    OSLogMessageComponentArgumentCategoryUInt64,
}
API_AVAILABLE(macos(10.15), ios(15.0), tvos(15.0), watchos(8.0))
NS_SWIFT_NAME(OSLogMessageComponent.ArgumentCategory);

/*!
 * @class OSLogMessageComponent
 *
 * @abstract
 * The message arguments for a particular entry. There is one
 * component for each placeholder in the formatString plus one
 * component for any text after the last placeholder.
 */
API_AVAILABLE(macos(10.15), ios(15.0), tvos(15.0), watchos(8.0))
OS_EXPORT
@interface OSLogMessageComponent : NSObject <NSSecureCoding>

/*!
 * @property formatSubstring
 *
 * @abstract
 * The text immediately preceding a placeholder. This can be an
 * empty string if there is nothing between two placeholders, or
 * between the placeholder and the bounds of the string.
 */
@property (nonatomic, readonly) NSString *formatSubstring
API_AVAILABLE(macos(10.15), ios(15.0), tvos(15.0), watchos(8.0));

/*!
 * @property placeholder
 *
 * @abstract
 * The placeholder text. Is empty for is the last component.
 */
@property (nonatomic, readonly) NSString *placeholder
API_AVAILABLE(macos(10.15), ios(15.0), tvos(15.0), watchos(8.0));

/*!
 * @property argumentCategory
 *
 * @abstract
 * The type of argument corresponding to the placeholder; see
 * OSLogMessageComponentArgumentCategory.
 */
@property (nonatomic, readonly) OSLogMessageComponentArgumentCategory argumentCategory
API_AVAILABLE(macos(10.15), ios(15.0), tvos(15.0), watchos(8.0));

/*!
 * @property argumentDataValue
 *
 * @abstract
 * The argument as a sequence of bytes. Can be nil if the
 * argument cannot be decoded (for example, it could be
 * redacted), or if this is the last component.
 */
@property (nonatomic, readonly, nullable) NSData *argumentDataValue
API_AVAILABLE(macos(10.15), ios(15.0), tvos(15.0), watchos(8.0));

/*!
 * @property argumentDoubleValue
 *
 * @abstract
 * The argument as a double-precision floating point number; the
 * value is undefined if the argument cannot be decoded or if this
 * is the last component.
 */
@property (nonatomic, readonly) double argumentDoubleValue
API_AVAILABLE(macos(10.15), ios(15.0), tvos(15.0), watchos(8.0));

/*!
 * @property argumentInt64Value
 *
 * @abstract
 * The argument as a 64-bit signed integer; the value is undefined
 * if it cannot be decoded or if this is the last component.
 */
@property (nonatomic, readonly) int64_t argumentInt64Value
API_AVAILABLE(macos(10.15), ios(15.0), tvos(15.0), watchos(8.0));

/*!
 * @property argumentNumberValue
 *
 * @abstract
 * The argument as a number. Can be nil if the argument cannot
 * be decoded (for example, it could be redacted), or if this is
 * the last component.
 */
@property (nonatomic, readonly, nullable) NSNumber *argumentNumberValue
API_AVAILABLE(macos(10.15), ios(15.0), tvos(15.0), watchos(8.0));

/*!
 * @property argumentStringValue
 *
 * @abstract
 * The argument as a string. Can be nil if the argument cannot
 * be decoded (for example, it could be redacted), or if this is
 * the last component.
 */
@property (nonatomic, readonly, nullable) NSString *argumentStringValue
API_AVAILABLE(macos(10.15), ios(15.0), tvos(15.0), watchos(8.0));

/*!
 * @property argumentUInt64Value
 *
 * @abstract
 * The argument as a 64-bit unsigned integer; the value is
 * undefined if the argument cannot be decoded or if this is the
 * last component.
 */
@property (nonatomic, readonly) uint64_t argumentUInt64Value
API_AVAILABLE(macos(10.15), ios(15.0), tvos(15.0), watchos(8.0));

@end

NS_ASSUME_NONNULL_END

#endif /* __OSLOG_MESSAGE_COMPONENT_H__ */
