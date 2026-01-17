//
//  Copyright (c) 2024 Apple Inc.  All rights reserved.
//
//  FSKitTaskOptions.h
//  FSKit
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/// A class that passes command options to a task, optionally providing security-scoped URLs.
FSKIT_API_AVAILABILITY_V1
@interface FSTaskOptions : NSObject

- (instancetype)init NS_UNAVAILABLE;

/// An array of strings that represent command-line options for the task.
///
/// This property is equivalent to the `argv` array of C strings passed to a command-line tool.
@property (readonly, copy)  NSArray <NSString *>    *taskOptions;

/// Retrieves a URL for a given option.
///
/// Some command-line options refer to paths that indicate a location in which the module needs access to a file outside of its container.
/// FSKit passes these paths as a URL tagged by the option name.
///
/// For example, `"-B" "./someFile"` returns the URL for `./someFile` when passed an option `"B"`.
/// To indicate that your module treats a given option as a path, include it in the `pathOptions` dictionary within a command options dictionary (`FSActivatOptionSyntax`, `FSCheckOptionSyntax`, or `FSFormatOptionSyntax`).
/// This dictionary uses the command option name as a key, and each entry has a value indicating what kind of entry to create.
///
/// - Parameter option: The option for which to retrieve the URL. This value doesn't include leading dashes.
- (NSURL * _Nullable)urlForOption:(NSString *)option;

@end

NS_ASSUME_NONNULL_END
