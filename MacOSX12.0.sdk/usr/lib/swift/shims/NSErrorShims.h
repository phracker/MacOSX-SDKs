//===--- NSErrorShims.h - Foundation declarations for NSError overlay -----===//
//
// This source file is part of the Swift.org open source project
//
// Copyright (c) 2014 - 2017 Apple Inc. and the Swift project authors
// Licensed under Apache License v2.0 with Runtime Library Exception
//
// See https://swift.org/LICENSE.txt for license information
// See https://swift.org/CONTRIBUTORS.txt for the list of Swift project authors
//
//===----------------------------------------------------------------------===//

#import "FoundationShimSupport.h"

NS_BEGIN_DECLS

NS_INLINE void __NSErrorPerformRecoverySelector(_Nullable id delegate, SEL selector, BOOL success, void *_Nullable contextInfo) {
    void (*msg)(_Nullable id, SEL, BOOL, void* _Nullable) =
        (void(*)(_Nullable id, SEL, BOOL, void* _Nullable))objc_msgSend;
    msg(delegate, selector, success, contextInfo);
}

NSError *_Nonnull _NSErrorWithFilePathAndErrno(NSInteger posixErrno, id _Nullable pathOrURL, BOOL reading);

NS_END_DECLS
