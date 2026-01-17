#if !__has_include(<PassKitCore/PKObject.h>) || PK_USE_PUBLIC_PASSKIT
//
//  PKObject.h
//    PassKit
//
//  Copyright (c) 2013 Apple, Inc. All rights reserved.
//

#ifndef __PKOBJECT_H
#define __PKOBJECT_H

#import <Foundation/Foundation.h>

@interface PKObject : NSObject

@end

#endif // __PKOBJECT_H

#else
#import <TargetConditionals.h>
#import <PassKitCore/PKObject.h>
#endif