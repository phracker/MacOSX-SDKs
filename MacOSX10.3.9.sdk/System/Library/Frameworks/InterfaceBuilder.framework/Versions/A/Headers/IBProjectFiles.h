// ================================================================================
//	**** PUBLIC HEADER ****
//
//	InterfaceBuilder.framework - IBProjectFiles.h 
//	Copyright (c) 1998-2000 Apple Computer, Inc.
//	All rights reserved.
//
// ================================================================================

#import <InterfaceBuilder/IBProjects.h>

/* The IBProjectFiles protocol provides all of the interesting information
 * IB requires about files which appear in a project. */

@protocol IBProjectFiles <NSObject>
- (id <IBProjects>)project;
- (NSString *)fileName;
- (NSString *)fileType;
- (NSString *)language;
- (NSString *)path;
- (BOOL)isLocalized;
@end
