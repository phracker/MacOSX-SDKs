//===----------------------------------------------------------------------===//
//
// This source file is part of the Swift.org open source project
//
// Copyright (c) 2019 Apple Inc. and the Swift project authors
// Licensed under Apache License v2.0 with Runtime Library Exception
//
// See https://swift.org/LICENSE.txt for license information
// See https://swift.org/CONTRIBUTORS.txt for the list of Swift project authors
//
//===----------------------------------------------------------------------===//

#import "FoundationShimSupport.h"

NS_BEGIN_DECLS

BOOL _NSFileHandleCanPerformWritingInSwiftOverlay(NSFileHandle *fileHandle) API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0), tvos(13.0));

NS_END_DECLS
