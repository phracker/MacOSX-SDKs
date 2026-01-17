//
//  Copyright (c) 2022-2023 Apple Inc. All rights reserved.
//
//  FSKit.h
//  FSKit
//

#ifndef FSKit_h
#define FSKit_h

#import <Foundation/Foundation.h>
#import <os/log.h>

#import <FSKit/FSKitDefines.h>
#import <FSKit/FSKitFunctions.h>
#import <FSKit/FSKitTypes.h>

//! Project version number for FSKit.
FOUNDATION_EXPORT double FSKitVersionNumber;

//! Project version string for FSKit.
FOUNDATION_EXPORT const unsigned char FSKitVersionString[];


// In this header, we import all the FSKit public headers
#import <FSKit/FSClient.h>
#import <FSKit/FSContainer.h>
#import <FSKit/FSEntityIdentifier.h>
#import <FSKit/FSMutableFileDataBuffer.h>
#import <FSKit/FSFileName.h>
#import <FSKit/FSItem.h>
#import <FSKit/FSKitError.h>
#import <FSKit/FSModuleIdentity.h>
#import <FSKit/FSResource.h>
#import <FSKit/FSTask.h>
#import <FSKit/FSTaskOptions.h>
#import <FSKit/FSVolume.h>
#import <FSKit/FSVolumeExtent.h>

// These are last as they depend on classes included above
#import <FSKit/FSFileSystemBase.h>
#import <FSKit/FSFileSystem.h>
#import <FSKit/FSUnaryFileSystem.h>

#endif /* FSKit_h */
