//
//  FSFileName.h
//  FSKit
//
//

#import <FSKit/FSKitDefines.h>

NS_ASSUME_NONNULL_BEGIN

/// The name of a file, expressed as a data buffer.
///
/// `FSFileName` is the class that carries filenames from the kernel to `FSModule` instances, and carries names back to the kernel as part of directory enumeration.
///
/// A filename is usually a valid UTF-8 sequence, but can be an arbitrary byte sequence that doesn't conform to that format.
/// As a result, the ``data`` property always contains a value, but the ``string`` property may be empty.
/// An `FSModule` can receive an `FSFileName` that isn't valid UTF-8 in two cases:
/// 1. A program passes erroneous data to a system call. The `FSModule` treats this situation as an error.
/// 2. An `FSModule` lacks the character encoding used for a file name.
/// This situation occurs because some file system formats consider a filename to be an arbitrary "bag of bytes," and leave character encoding up to the operating system.
/// Without encoding information, the `FSModule` can only pass back the names it finds on disk.
/// In this case, the behavior of upper layers such as <doc://com.apple.documentation/documentation/Foundation/NSFileManager> is unspecified.
/// However, the `FSModule` must support looking up such names and using them as the source name of rename operations.
/// The `FSModule` must also be able to support filenames that are derivatives of filenames returned from directory enumeration.
/// Derivative filenames include Apple Double filenames (`"._Name"`), and editor backup filenames.
///
/// > Important: Don't subclass this class.
FSKIT_API_AVAILABILITY_V1
@interface FSFileName : NSObject <NSSecureCoding, NSCopying>

/// The byte sequence of the filename, as a data object.
///
/// This property always provides a value.
@property (readonly) NSData                 *data FSKIT_API_AVAILABILITY_V1;

/// The filename, represented as a Unicode string.
///
/// If the value of the filename's ``FSFileName/data`` is not a valid UTF-8 byte sequence, this property is empty.
@property (readonly, nullable) NSString     *string FSKIT_API_AVAILABILITY_V1;

/// The filename, represented as a potentially lossy conversion to a string.
///
/// The exact details of the string conversion may change in the future.
@property (readonly, copy)     NSString     *debugDescription FSKIT_API_AVAILABILITY_V1;

- (instancetype)init NS_UNAVAILABLE;

/// Initializes a filename from a null-terminated character sequence.
///
/// > Note: This initializer is unavailable in Swift. Use ``initWithData:`` or ``initWithString:`` instead.
///
/// - Parameter name: A pointer to a C string.
- (instancetype)initWithCString:(const char *)name FSKIT_API_AVAILABILITY_V1 NS_DESIGNATED_INITIALIZER NS_SWIFT_UNAVAILABLE("Use a data or string instead."); // NUL-terminated character sequence

/// Initializes a file name by copying a character sequence from a byte array.
///
/// > Note: This initializer is unavailable in Swift. Use ``initWithData:`` or ``initWithString:`` instead.
///
/// - Parameters:
///  - bytes: A pointer to the character data to copy, up to a maximum of `length`. The sequence terminates if a `NUL` character exists prior to `length`.
///  - length: The size of the `bytes` array.
- (instancetype)initWithBytes:(const char *)bytes
                       length:(NSUInteger)length FSKIT_API_AVAILABILITY_V1 NS_DESIGNATED_INITIALIZER NS_SWIFT_UNAVAILABLE("Use a data or string instead.");

/// Creates a filename by copying a character sequence data object.
///  
/// This initializer copies up to `name.length` characters of the sequence pointed to by `bytes`.
///  
/// - Parameter name: The data object containing the character sequence to use for the filename. The sequence terminates if a `NUL` character exists prior to `name.length`.
- (instancetype)initWithData:(NSData *)name FSKIT_API_AVAILABILITY_V1;

/// Creates a filename by copying a character sequence from a string instance.
///
/// This initializer copies the UTF-8 representation of the characters in `string`.
/// If `string` contains a `NUL` character, the sequence terminates.
///
/// - Parameter name: The string containing the character sequence to use for the filename.
- (instancetype)initWithString:(NSString *)name FSKIT_API_AVAILABILITY_V1;

/// Creates a filename from a null-terminated character sequence.
///
/// - Parameter name: A pointer to a C string.
+ (instancetype)nameWithCString:(const char *)name FSKIT_API_AVAILABILITY_V1 NS_SWIFT_UNAVAILABLE("Use a data or string instead."); // NUL-terminated character sequence

/// Creates a filename by copying a character sequence from a byte array.
///
/// - Parameters:
///  - bytes: A pointer to the character data to copy, up to a maximum of `length`. The sequence terminates if a `NUL` character exists prior to `length`.
///  - length: The size of the `bytes` array.
+ (instancetype)nameWithBytes:(const char *)bytes
                       length:(NSUInteger)length FSKIT_API_AVAILABILITY_V1 NS_SWIFT_UNAVAILABLE("Use a data or string instead.");

/// Creates a filename by copying a character sequence data object.
///
/// This initializer copies up to `name.length` characters of the sequence pointed to by `bytes`.
///
/// - Parameter name: The data object containing the character sequence to use for the filename. The sequence terminates if a `NUL` character exists prior to `name.length`.
+ (instancetype)nameWithData:(NSData *)name FSKIT_API_AVAILABILITY_V1;

/// Creates a filename by copying a character sequence from a string instance.
///
/// This initializer copies the UTF-8 representation of the characters in `string`.
/// If `string` contains a `NUL` character, the sequence terminates.
///
/// - Parameter name: The string containing the character sequence to use for the filename.
+ (instancetype)nameWithString:(NSString *)name FSKIT_API_AVAILABILITY_V1 ;

@end

NS_ASSUME_NONNULL_END
